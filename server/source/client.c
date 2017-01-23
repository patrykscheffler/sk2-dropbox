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

void *client_loop(void *arg) {
    int socket = *((int *) arg);
    uint16_t message = 0;

    recv(socket, &message, sizeof(uint16_t), MSG_WAITALL);
    message = ntohs(message);
    printf("Received client message: %d\n", message);

    if (message == FILE_READ)
        client_file_read(socket);
    if (message == FILE_WRITE)
        client_file_write(socket);
    if (message == LIST_FILES)
        client_list_files(socket);
    if (message == FILE_REMOVE)
        client_remove_file(socket);

    Close(socket);
    pthread_exit(NULL);
}

void client_file_read(int socket) {
    printf("client read\n");
    file_info_t fileInfo;
    recv(socket, &fileInfo, sizeof(file_info_t), MSG_WAITALL);

    send_file(socket, fileInfo.user, fileInfo.name);
}

void client_file_write(int socket) {
    printf("client write\n");
    file_info_t fileInfo;
    recv(socket, &fileInfo, sizeof(file_info_t), MSG_WAITALL);

    printf("%s %s %d\n", fileInfo.user, fileInfo.name, fileInfo.size);

    if (strcmp(fileInfo.name, "")) {
        get_file(socket, fileInfo.user, fileInfo.name, fileInfo.size);
    }

    // TODO: update server version, replicate file
    replicate_file(fileInfo);
}

void client_list_files(int socket) {
    file_info_t fileInfo;
    recv(socket, &fileInfo, sizeof(file_info_t), MSG_WAITALL);

    send_file_list(socket, fileInfo.user);
}

void replicate_file(file_info_t fileInfo) {
    FILE *fp;
    struct sockaddr_in sck_addr;
    uint16_t message;
    int socket, port;
    char address[15];
    memset(address, ' ', 15);

    file_info_t fileInfoCopy;
    fileInfoCopy.size = fileInfo.size;
    strcpy(fileInfoCopy.user, fileInfo.user);
    strcpy(fileInfoCopy.name, fileInfo.name);


    fp = open_file("server_list.txt", "r");
    while (fscanf(fp, "%s %d", address, &port) != EOF) {
        printf("Replicate %s to %s:%d\n", fileInfo.name, address, port);
        memset(&sck_addr, 0, sizeof sck_addr);
        sck_addr.sin_family = AF_INET;
        inet_aton(address, &sck_addr.sin_addr);
        sck_addr.sin_port = htons(port);

        socket = Socket(AF_INET, SOCK_STREAM, 0);
        Connect(socket, (struct sockaddr*) &sck_addr, sizeof(sck_addr));

        message = htons(SERVER_CONN);
        write(socket, &message, sizeof(uint16_t));

        message = htons(FILE_WRITE);
        write(socket, &message, sizeof(uint16_t));

        write(socket, &fileInfoCopy, sizeof(fileInfoCopy));

        send_file(socket, fileInfoCopy.user, fileInfoCopy.name);

        Close(socket);
    }

    close_file(fp);
}

void client_remove_file(int socket) {
    file_info_t fileInfo;
    recv(socket, &fileInfo, sizeof(file_info_t), MSG_WAITALL);

    remove_file(socket, fileInfo.user, fileInfo.name);
}