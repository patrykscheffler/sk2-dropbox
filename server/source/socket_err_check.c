//
// Created by jakub on 03.01.17.
//

#include "../header/socket_err_check.h"

int Socket(int domain, int type, int protocol) {
    int sockfd = socket(domain, type, protocol);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    return sockfd;
}

void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
    if (bind(sockfd, addr, addrlen) < 0) {
        perror("bind error");
        exit(1);
    }
}

void Listen(int sockfd, int queue_size) {
    if (listen(sockfd, queue_size) < 0) {
        perror("listen error");
        exit(1);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int n = accept(sockfd, addr, addrlen);
    if (n < 0) {
        perror("accept error");
        exit(1);
    }
    return n;
}

void Close(int sockfd) {
    if (close(sockfd) == -1) {
        perror("close error");
        exit(1);
    }
}
