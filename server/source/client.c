#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>

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
    message = ntohs(message);
    printf("Received message: %d\n", message);

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
    // replicate_file(fileInfo);
}

void client_list_files(int socket) {
    file_info_t fileInfo;
    read(socket, &fileInfo, sizeof(fileInfo));

    send_file_list(socket, fileInfo.user);
}

void replicate_file(file_info_t fileInfo) {
    FILE *fp = open_file("./server_list.txt", "r");
    struct sockaddr_in sck_addr;
    uint16_t message = htons(SERVER_CONN);
    int socket, port;

    while(fscanf(fp, "%d", &port) != EOF) {
        memset (&sck_addr, 0, sizeof sck_addr);
    	sck_addr.sin_family = AF_INET;
    	inet_aton ("127.0.0.1", &sck_addr.sin_addr);
    	sck_addr.sin_port = htons(port);

        socket = Socket(AF_INET, SOCK_STREAM, 0);

        write(socket, &message, sizeof(uint16_t));
        send_file(socket, fileInfo.user, fileInfo.name);

        Close(socket);
    }

    close_file(fp);
}