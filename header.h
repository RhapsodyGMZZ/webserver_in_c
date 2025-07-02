#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000

typedef struct {
    char* name;
    char* email;
    char* message;
} test_form;



// Server functions
int listener(int new_socket, int server_fd, struct sockaddr_in address, socklen_t addrlen);
void handle_routes_get(char* path, int socket_fd);
void handle_routes_post(char* path, int socket_fd, char* buffer);
char* render(char* filename);




