#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000

// Server functions
int listener(int new_socket, int server_fd, struct sockaddr_in address, socklen_t addrlen);
void handle_routes(char* path, int socket_fd);
char* render(char* filename);




