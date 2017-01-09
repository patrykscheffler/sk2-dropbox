//
// Created by jakub on 03.01.17.
//

#ifndef SK2_DROPBOX_SOCKET_ERR_CHECK_H
#define SK2_DROPBOX_SOCKET_ERR_CHECK_H

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int queue_size);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Close(int sockfd);

#endif //SK2_DROPBOX_SOCKET_ERR_CHECK_H
