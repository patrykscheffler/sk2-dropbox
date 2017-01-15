#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"

const char FILE_READ = 0xF1;
const char FILE_WRITE = 0xF2;
const char LIST_FILES = 0xF3;

void create_client_thread(int socket) {
    pthread_t client_thread;

    if (pthread_create(&client_thread, NULL, client_loop, &socket)) {
        fprintf(stderr, "Error creating client thread");
        exit(1);
    }
}

void* client_loop(void *arg) {
    int socket = *((int*) arg);
    char message[BUFFER_LEN];

    file_info_t fileInfo = {
        .user = "mike",
        .name = "test.txt",
        .size = 1231231231
    };

    read(socket, message, BUFFER_LEN);
    printf("Received message: %s\n", message);

    printf("Sending %s/%s, %d, %lu\n", fileInfo.user, fileInfo.name, fileInfo.size, sizeof(fileInfo));
    write(socket, &fileInfo, sizeof(fileInfo));

    // char message;
    // while(read(socket, message, 1) {
    //     switch(message) {
    //         case FILE_READ:
    //             client_file_read(socket);
    //         case FILE_WRITE:
    //             client_file_write(socket);
    //         case LIST_FILES:
    //             client_list_files(socket);
    //     }
    // }

    Close(socket);
    pthread_exit(NULL);
}

void client_file_read(int socket) {
    // TODO: receive file info
    // TODO: send file | send FAILURE message
}

void client_file_write(int socket) {
    // TODO: receive file info
    // TODO: receive file
    // TODO: save file
    // TODO: save file
}

void client_list_files(int socket) {
    // TODO: read user name
    DIR *dp;
    struct dirent *ep;
    dp = opendir ("./");

    if (dp != NULL) {
        while ((ep = readdir (dp)))
        puts (ep->d_name);

        // TODO: filter data (cross-platform), save to structure

        (void) closedir (dp);
    } else {
        perror ("Couldn't open the directory");
    }

    // TODO: send structre size
    // TODO: send file list
}

int valid_file_request(char *request) {
    return 1;
}