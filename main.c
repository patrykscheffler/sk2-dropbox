//
// Created by jakub on 02.01.17.
//

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>

#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define buffLen 256

void *client_loop(void *arg) {
    char buffer[buffLen];
    int sck = *((int *) arg);
    int n = 0;

    /* If connection is established then start communicating */
    bzero(buffer, buffLen);
    n = read(sck, buffer, buffLen - 1);
    printf("Here is the message: %s\n", buffer);

    /* Write a response to the client */
    n = write(sck, "I got your message\n", 20);

    close(sck);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int sockfd, clientSockFd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t nTmp;

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    memset(&serv_addr, 0, sizeof(struct sockaddr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, QUEUE_SIZE);
    nTmp = sizeof(cli_addr);

    while (1) {
        /* Accept actual connection from the client */
        clientSockFd = accept(sockfd, (struct sockaddr *) &cli_addr, &nTmp);
        if (clientSockFd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        printf("%s: [connection from %s]\n", argv[0], inet_ntoa(cli_addr.sin_addr));

        pthread_t id;
        pthread_create(&id, NULL, client_loop, &clientSockFd);
    }

    close(sockfd);
    return 0;
}