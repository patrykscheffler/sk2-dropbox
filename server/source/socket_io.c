#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdint.h>
#include <netinet/in.h>
#include <ctype.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"

char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

char *preapare_path(char *directory, char *filename) {
    char *fullpath = NULL;
    struct stat st;

    char *dir = trimwhitespace(directory);
    char *filen = trimwhitespace(filename);

    char *tmpPath = NULL;
    asprintf(&tmpPath, "%s%s", "./files/", dir);
    if (stat(tmpPath, &st) == -1) {
        mkdir(tmpPath, 0700);
    }
    asprintf(&fullpath, "%s/%s", tmpPath, filen);
    return fullpath;
}

FILE *open_file(char *path, char *mode) {
    FILE *fp;
    if ((fp = fopen(path, mode)) == NULL) {
        perror("fopen on send file: ");
        exit(1);
    }
    return fp;
}

void close_file(FILE *fp) {
    if ((fclose(fp))) {
        perror("fclose: ");
        exit(1);
    }
}

int does_file_exist(char *fullpath) {
    struct stat st;
    return stat(fullpath, &st);
}

/*
 * Write file with name 'filename' in 'directory' to socket 'socketfd'
 */
void send_file(int sockfd, char *directory, char *filename) {
    char buffer[BUFFER_LEN];
    int bufsize = BUFFER_LEN;
    uint16_t message;
    int i;

    char *fullpath = preapare_path(directory, filename);
    printf("send_file path: %s", fullpath);

    if (does_file_exist(fullpath)) {
        message = htons(FAILURE);
        write(sockfd, &message, sizeof(uint16_t));
    } else {
        message = htons(ACCEPT);
        write(sockfd, &message, sizeof(uint16_t));

        FILE *fp = open_file(fullpath, "r");

        while ((i = fread(buffer, 1, bufsize, fp))) {
            if (ferror(fp)) {
                fprintf(stderr, "A read error occured.\n");
                Close(sockfd);
                exit(1);
            }

            write(sockfd, &buffer, i);
        }

        close_file(fp);
    }
}

/*
 * Write buffer to file
 * returns 1 on success and 0 on fail
 */
int buffer2file(FILE *fp, char *buffer, int length) {
    fwrite(buffer, length, 1, fp);

    if (ferror(fp)) {
        fprintf(stderr, "A write error occured.\n");
        return 0;
    }

    return 1;
}

/*
 * Save file from socket
 */
void get_file(int sockfd, char *directory, char *filename, int file_size) {
    int read_size, n;
    int read_count = 0;
    char buffer[BUFFER_LEN];
    char *fullpath = preapare_path(directory, filename);

    printf("get_file path: %s", fullpath);
    FILE *fp = open_file(fullpath, "w");

    while (read_count <= file_size) {
        if ((read_size = file_size - read_count) > BUFFER_LEN) {
            read_size = BUFFER_LEN;
        }

        if ((n = read(sockfd, buffer, read_size)) <= 0) {
            Close(sockfd);
            break;
        } else {
            buffer2file(fp, buffer, n);
            read_count += n;
        }
    }

    close_file(fp);
}

/*
 * Write file list in 'directory' to socket 'socketfd'
 */
void send_file_list(int sockfd, char *directory) {
    char *fullpath = preapare_path(directory, "");
    file_info_t fileInfo;
    struct dirent *ep;
    struct stat st;
    int size;
    DIR *dp;

    dp = opendir(fullpath);

    if (dp == NULL) {
        perror("Couldn't open the directory");
        exit(1);
    }

    while ((ep = readdir(dp))) {
        if (ep->d_name[0] != '.') {
            fullpath = preapare_path(directory, ep->d_name);
            stat(fullpath, &st);
            size = st.st_size;

            strcpy(fileInfo.name, ep->d_name);
            strcpy(fileInfo.user, directory);
            fileInfo.size = htonl(size);

            printf("List file: %s, %s, %d\n", fileInfo.user, fileInfo.name, st.st_size);
            write(sockfd, &fileInfo, sizeof(fileInfo));
        }
    }

    closedir(dp);

    strcpy(fileInfo.name, "");
    strcpy(fileInfo.user, "");
    fileInfo.size = htonl(0);

    // end list / no files
    write(sockfd, &fileInfo, sizeof(fileInfo));
}