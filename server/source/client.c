#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"

void create_client_thread(int socket) {
    pthread_t client_thread;

    if (pthread_create(&client_thread, NULL, client_loop, &socket)) {
        fprintf(stderr, "Error creating client thread");
        exit(1);
    }
}

void *client_loop(void *arg) {
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

    Close(socket);
    pthread_exit(NULL);
}

int valid_file_request(char *request) {
    return 1;
}