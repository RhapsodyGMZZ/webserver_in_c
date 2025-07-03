#include "../header.h"

void handle_routes_get(char *path, int socket_fd)
{
    printf("%s\n", path);
    char *req = NULL;
    int should_free = 0;

    // Handling GET path here
    if (strcmp(path, "/home") == 0)
    {
        req = render("home.html");
    }
    else if (strcmp(path, "/about") == 0)
    {
        should_free = 0;
    }
    else
    {
        req = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\n\r\nNot Found";
        should_free = 1;
    }
    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");

    if (should_free == 0)
        free(req);
}

void handle_routes_post(char *path, int socket_fd, char *buffer)
{
    char *req = NULL;
    int should_free = 1;
    char *body = strstr(buffer, "\r\n\r\n");

    // Handling POST path here
    if (strcmp(path, "/submit") == 0)
    {
        if (body && strlen(body) > 4)
        {
            body += 4; // skip the "\r\n\r\n"
            printf("BODY == '%s'", body);
            req = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 7\r\n\r\nSuccess";
            should_free = 0;
        }
        else
        {
            req = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nBad Request";
            should_free = 0;
        }
    }
    else
    {
        req = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 9\r\n\r\nNot Found";
        should_free = 0;
    }

    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");

    if (should_free == 1)
        free(req);
}