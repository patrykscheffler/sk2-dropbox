#ifndef SK2_DROPBOX_GLOBAL_DATA_H
#define SK2_DROPBOX_GLOBAL_DATA_H

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define MESSAGE_LEN 256
#define MAX_FILE_NAME 64
#define MAX_USER_NAME 64

#define DEBUG 1

typedef struct client_connection_info {
    int socket;
} client_conn_info_t;

typedef struct file_info {
    char name[MAX_FILE_NAME];
    char user[MAX_USER_NAME];
    int32_t size;
} file_info_t;

typedef struct socket_message {
    int32_t message_length;
    char *message;
} socket_message_t;

typedef struct server_info {
    int ip_address;
    int port;
} server_info_t;

#endif // SK2_DROPBOX_GLOBAL_DATA_H