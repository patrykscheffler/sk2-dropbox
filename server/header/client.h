#ifndef SK2_DROPBOX_CLIENT_H
#define SK2_DROPBOX_CLIENT_H

void create_client_thread(int *socket);
void* client_loop(void *arg);
void client_file_read(int socket);
void client_file_write(int socket);
void client_list_files(int socket);
int valid_file_request(char* request);
void replicate_file(file_info_t fileInfo);

#endif // SK2_DROPBOX_CLIENT_H