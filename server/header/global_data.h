//
// Created by jakub on 03.01.17.
//

#ifndef SK2_DROPBOX_GLOBAL_DATA_H
#define SK2_DROPBOX_GLOBAL_DATA_H

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define BUFFER_LEN 256
#define MAX_FILE_NAME 64

struct file_info {
    char name[MAX_FILE_NAME];
    int32_t size;
};

struct socket_message {

};

#endif //SK2_DROPBOX_GLOBAL_DATA_H
