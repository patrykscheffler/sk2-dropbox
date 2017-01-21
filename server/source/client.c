#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"

void create_client_thread(int *socket) {
    pthread_t client_thread;
    if (pthread_create(&client_thread, NULL, client_loop, socket)) {
        fprintf(stderr, "Error creating client thread");
        exit(1);
    }
}

void* client_loop(void *arg) {
    int socket = *((int*) arg);
    uint16_t message;

    read(socket, &message, sizeof(uint16_t));
    printf("Received message: %d\n", ntohs(message));

    switch(message) {
        case FILE_READ:
            client_file_read(socket);
        case FILE_WRITE:
            client_file_write(socket);
        case LIST_FILES:
            client_list_files(socket);
    }

    Close(socket);
    pthread_exit(NULL);
}

void client_file_read(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file(socket, fileInfo.user, fileInfo.name);
}

void client_file_write(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    get_file(socket, fileInfo.user, fileInfo.name, fileInfo.size);

    // TODO: update server version, replicate file
}

void client_list_files(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file_list(socket, fileInfo.user);
}

int valid_file_request(char *request) {
    return 1;
}