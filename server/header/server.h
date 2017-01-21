#ifndef SK2_DROPBOX_SERVER_H
#define SK2_DROPBOX_SERVER_H

void create_server_thread(int *socket);
void* server_loop(void *arg);
void server_file_read(int socket);
void server_file_write(int socket);
void add_server(int port);

#endif // SK2_DROPBOX_SERVER_H