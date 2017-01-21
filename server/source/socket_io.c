#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"

char *preapare_path(char *directory, char *filename) {
    char *fullpath = (char *) malloc(BUFFER_LEN);

    strncpy(fullpath, "./files/", 8);
    strncat(fullpath, directory, BUFFER_LEN - 7);
    strncat(fullpath, "/", BUFFER_LEN - strlen(fullpath));
    strncat(fullpath, filename, BUFFER_LEN - strlen(fullpath));

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

/*
 * Write file with name 'filename' in 'directory' to socket 'socketfd'
 */
void send_file(int sockfd, char *directory, char *filename) {
    char buffer[BUFFER_LEN];
    int bufsize = BUFFER_LEN;
    int i;

    char *fullpath = preapare_path(directory, filename);

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
        perror ("Couldn't open the directory");
        exit(1);
    }

    while ((ep = readdir(dp))) {
        if (ep->d_name[0] != '.') {
            fullpath = preapare_path(directory, ep->d_name);
            stat(fullpath, &st);
            size = st.st_size;

            strcpy(fileInfo.name, ep->d_name);
            strcpy(fileInfo.user, directory);
            fileInfo.size = htons(size);

            write(sockfd, &fileInfo, sizeof(fileInfo));
        }
    }

    closedir (dp);

    strcpy(fileInfo.name, "");
    strcpy(fileInfo.user, "");
    fileInfo.size = htons(0);

    // end list / no files
    write(sockfd, &fileInfo, sizeof(fileInfo));

    // TODO: send file list
    // write(sockfd, &buffer, i);
}