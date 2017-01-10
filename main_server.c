#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>

#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>
#include "server/header/socket_err_check.h"
#include "server/header/global_data.h"

int init();

void *client_loop(void *arg);

int main(int argc, char *argv[]) {
    // server_info_t info = {
    //     .ip_addres = atoi(argv[1]),
    //     .port = atoi(argv[2]),
    // }

    int sockfd, clientSockFd;
    struct sockaddr_in cli_addr;
    socklen_t nTmp = sizeof(cli_addr);

    sockfd = init();

    while (1) {
        /* Accept actual connection from the client */
        clientSockFd = Accept(sockfd, (struct sockaddr *) &cli_addr, &nTmp);

        printf("%s: [connection from %s]\n", argv[0], inet_ntoa(cli_addr.sin_addr));

        pthread_t id;
        pthread_create(&id, NULL, client_loop, &clientSockFd);
    }

    Close(sockfd);
    return 0;
}

int init() {
    int sockfd;
    struct sockaddr_in serv_addr;

    /* Create a socket */
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    /* Initialize socket structure */
    memset(&serv_addr, 0, sizeof(struct sockaddr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    /* Now bind the host address using bind() call.*/
    Bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    Listen(sockfd, QUEUE_SIZE);

    return sockfd;
}

void *client_loop(void *arg) {
    char buffer[BUFFER_LEN];
    int sck = *((int *) arg);
    int n = 0;

    /* If connection is established then start communicating */
    bzero(buffer, BUFFER_LEN);
    n = read(sck, buffer, BUFFER_LEN - 1);
    printf("Here is the message: %s\n", buffer);

    /* Write a response to the client */
    n = write(sck, "I got your message\n", 20);

    Close(sck);
    pthread_exit(NULL);
}