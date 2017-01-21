#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <netinet/in.h>

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

void *server_loop(void *arg) {
    int socket = *((int *) arg);
    uint16_t message;

    server_info_t serverInfo = {
            .version = 1,
            .port = 1234
    };

    read(socket, &message, sizeof(uint16_t));
    message = ntohs(message);
    printf("Received server message: %d\n", message);

    if (message == FILE_READ)
        server_file_read(socket);
    if (message == FILE_WRITE)
        server_file_write(socket);

    // TODO: receive server info
    // TODO: check version, replicate files

    Close(socket);
    pthread_exit(NULL);
}

void server_file_read(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file(socket, fileInfo.user, fileInfo.name);
}

void server_file_write(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    get_file(socket, fileInfo.user, fileInfo.name, fileInfo.size);
}

void add_server(int port) {
    FILE *fp = open_file("./server_list.txt", "a");

    fprintf(fp, "%d\n", port);

    close_file(fp);
}