#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"

static pthread_mutex_t lock;

const char FILE_READ = 0xF1;
const char FILE_WRITE = 0xF2;
const char LIST_FILES = 0xF3;

const char FAILURE = 0xFF;

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
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file(socket, fileInfo.user, fileInfo.name);
    // TODO: send FAILURE message, when file doesn't exist
}

void client_file_write(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    get_file(socket, fileInfo.user, fileInfo.name, fileInfo.size);

    pthread_mutex_init(&lock, NULL);
    // TODO: update server version, replicate file
    pthread_mutex_destroy(&lock);
}

void client_list_files(int socket) {
    char user[MAX_USER_NAME];
    read(socket, user, MAX_USER_NAME);

    send_file_list(socket, user);
}

int valid_file_request(char *request) {
    return 1;
}