#include "../header.h"

int listener(int new_socket, int server_fd, struct sockaddr_in address, socklen_t addrlen)
{
    while (1)
    {
        char buffer[1024] = {0};
        char *req = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"test\":\"awesome\"}";
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
        &addrlen)) < 0)
        {
            perror("accept");
            return -1;
        }
        read(new_socket, buffer, 1024 - 1);
        if (strlen(buffer) > 0)
        {
            printf("%s",buffer);
            if (strncmp(buffer, "GET ", 4) == 0)
            {
                printf("GET\t");
                
                char *path = NULL;
                path = strtok(buffer, " "); // returns the string "GET"
                path = strtok(NULL, " ");   // returns the requested path
                handle_routes(path, new_socket);
            } else if (strncmp(buffer, "POST ", 5) == 0) {
                printf("POST\t");
            } else {
                req = "HTTP/1.1 405 Method Not Allowed\r\n";
                send(new_socket, req, sizeof req, 0);
            }
            close(new_socket);
        }
    }
}