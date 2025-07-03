#include "../header.h"

int listener(int new_socket, int server_fd, struct sockaddr_in address, socklen_t addrlen)
{
    while (1)
    {
        char buffer[1024] = {0};
        char *req = {0};
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                 &addrlen)) < 0)
        {
            perror("accept");
            return -1;
        }
        read(new_socket, buffer, 1024 - 1);
        if (strlen(buffer) > 0)
        {
            if (strncmp(buffer, "GET ", 4) == 0)
            {
                printf("GET\t");

                char *path = NULL;
                path = strtok(buffer, " "); // returns the string "GET"
                path = strtok(NULL, " ");   // returns the requested path
                handle_routes_get(path, new_socket);
            }
            else if (strncmp(buffer, "POST ", 5) == 0)
            {
                printf("POST\t");
                char * tmp = malloc(strlen(buffer));
                strcpy(tmp, buffer);
                char *path = NULL;
                path = strtok(tmp, " ");
                path = strtok(NULL, " ");
                handle_routes_post(path, new_socket, buffer);
            }
            else
            {
                req = "HTTP/1.1 405 Method Not Allowed\r\n";
                send(new_socket, req, sizeof req, 0);
            }
            close(new_socket);
        }
    }
}