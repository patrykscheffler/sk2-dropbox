#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>

#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>
#include "server/header/socket_err_check.h"
#include "server/header/global_data.h"
#include "server/header/client.h"

int init();

int main(int argc, char *argv[]) {
    int sockfd, clientSockFd;
    struct sockaddr_in cli_addr;
    socklen_t nTmp = sizeof(cli_addr);

    server_info_t info = {
        .version = 1,
        .port = SERVER_PORT,
    };

    if (argc > 1) {
        char* port_str = argv[1];
        info.port = atoi(port_str);
    }

    sockfd = init(info.port);

    printf("Server running on port %d\n", info.port);

    while (1) {
        clientSockFd = Accept(sockfd, (struct sockaddr *) &cli_addr, &nTmp);

        printf("%s: [connection from %s]\n", argv[0], inet_ntoa(cli_addr.sin_addr));

        create_client_thread(&clientSockFd);
    }

    Close(sockfd);
    return 0;
}

int init(int32_t port) {
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(struct sockaddr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    Bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    Listen(sockfd, QUEUE_SIZE);

    return sockfd;
}