#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../header/socket_io.h"
#include "../header/socket_err_check.h"
#include "../header/global_data.h"
#include "../header/client.h"

int create_client_thread(int socket) {
    pthread_t client_thread;

    return pthread_create(&client_thread, NULL, client_loop, &socket);
}

void *client_loop(void *arg) {
    int socket = *((int*) arg);
    char message[MESSAGE_LEN];
    bzero(message, MESSAGE_LEN);

    read(socket, message, MESSAGE_LEN - 1);
    printf("Here is the message: %s\n", MESSAGE_LEN);

    write(socket, "I got your message\n", 20);

    Close(socket);
    pthread_exit(NULL);
}

int valid_file_request(char *request) {
    return 1;
}