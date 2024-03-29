#ifndef SK2_DROPBOX_GLOBAL_DATA_H
#define SK2_DROPBOX_GLOBAL_DATA_H

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define BUFFER_LEN 256
#define MAX_FILE_NAME 64
#define MAX_USER_NAME 64
#define DEBUG 1

static const uint16_t CLIENT_CONN = 0x01;
static const uint16_t SERVER_CONN = 0x02;
static const uint16_t FILE_READ = 0xF1;
static const uint16_t FILE_WRITE = 0xF2;
static const uint16_t LIST_FILES = 0xF3;
static const uint16_t FILE_REMOVE = 0xF4;
static const uint16_t ACCEPT = 0x00;
static const uint16_t FAILURE = 0xFF;

typedef struct client_connection_info {
    int socket;
} client_conn_info_t;

typedef struct file_info {
    char user[MAX_USER_NAME];
    char name[MAX_FILE_NAME];
    int32_t size;
} file_info_t;

typedef struct socket_message {
    int32_t message_length;
    char *message;
} socket_message_t;

typedef struct server_info {
    int32_t version;
    int32_t port;
} server_info_t;

#endif // SK2_DROPBOX_GLOBAL_DATA_H