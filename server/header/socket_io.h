#ifndef SK2_DROPBOX_SOCKET_IO_H
#define SK2_DROPBOX_SOCKET_IO_H

void send_file_list(int sockfd, char *directory);

void send_file(int sockfd, char *directory, char *filename);

void get_file(int sockfd, char *directory, char *filename, int file_size);

int does_file_exist(char *fullpath);

#endif // SK2_DROPBOX_SOCKET_IO_H