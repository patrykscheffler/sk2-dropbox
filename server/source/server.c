#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"
#include "../header/server.h"

void create_server_thread(int *socket) {
    pthread_t server_thread;

    if (pthread_create(&server_thread, NULL, server_loop, socket)) {
        fprintf(stderr, "Error creating server thread");
        exit(1);
    }
}

void* server_loop(void *arg) {
    int socket = *((int*) arg);
    uint16_t message;

    server_info_t serverInfo = {
        .version = 1,
        .port = 1234
    };

    read(socket, &message, sizeof(uint16_t));
    printf("Received message: %d\n", message);

    switch(message) {
        case FILE_READ:
            server_file_read(socket);
        case FILE_WRITE:
            server_file_write(socket);
    }

    // TODO: receive server info
    // TODO: check version, replicate files

    Close(socket);
    pthread_exit(NULL);
}

void server_file_read(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file(socket, fileInfo.user, fileInfo.name);
    // TODO: send FAILURE message, when file doesn't exist
}

void server_file_write(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    get_file(socket, fileInfo.user, fileInfo.name, fileInfo.size);
}