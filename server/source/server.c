#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"
#include "../header/server.h"

void create_server_thread(int socket) {
    pthread_t server_thread;

    if (pthread_create(&server_thread, NULL, server_loop, &socket)) {
        fprintf(stderr, "Error creating server thread");
        exit(1);
    }
}

void* server_loop(void *arg) {
    int socket = *((int*) arg);
    char message[BUFFER_LEN];

    server_info_t serverInfo = {
        .ip_address = "127.0.0.1",
        .port = 1234
    };

    read(socket, message, BUFFER_LEN);
    printf("Received message: %s\n", message);

    // TODO: receive server info
    // read(socket, &serverInfo, sizeof(serverInfo));

    // TODO: check version, replicate files

    Close(socket);
    pthread_exit(NULL);
}