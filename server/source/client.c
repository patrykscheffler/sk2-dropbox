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
    int n = 0;
    char message[MESSAGE_LEN];
    bzero(message, MESSAGE_LEN);

    struct file_info *fileInfo = (struct file_info*) malloc(sizeof(struct file_info));
    strcpy(fileInfo->name, "test");
    fileInfo->size = htonl(1231231231);

    read(socket, message, MESSAGE_LEN - 1);
    printf("sending %s, %d, %d\n", fileInfo->name, fileInfo->size, sizeof(struct file_info));
    n = write(sck, fileInfo, sizeof(struct file_info));

    Close(socket);
    pthread_exit(NULL);
}

int valid_file_request(char *request) {
    return 1;
}