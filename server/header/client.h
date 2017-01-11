#ifndef SK2_DROPBOX_CLIENT_H
#define SK2_DROPBOX_CLIENT_H

int create_client_thread(int clientSocket);
void* client_loop(void *arg);
int valid_file_request(char* request);

#endif // SK2_DROPBOX_CLIENT_H