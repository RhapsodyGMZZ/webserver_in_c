#include "../header.h"

void handle_routes_get(char* path, int socket_fd) {
    printf("%s\n", path);
    char* req = NULL;
    int should_free = 0;

    // Handling GET path here
    if (strcmp(path, "/home") == 0) {
        req = render("home.html");
    } else if (strcmp(path, "/about") == 0) {
        should_free = 0;
    } else {
        req = "HTTP/1.1 404 Not Found\r\n";
        should_free = 1;
    }
    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");
    
    if (should_free == 0)
        free(req);
}

void handle_routes_post(char* path, int socket_fd, char* buffer) {
    printf("%s\n%s\n", path, buffer);
    char* req = NULL;
    int should_free = 0;
    char* body = strtok(buffer, "\r\n\r\n");
    body = strtok(NULL, "\r\n\r\n");
    printf("%s",body);
    // Handling POST path here
    if (strcmp(path, "/submit") == 0) {
        req = render("home.html");
    } else {
        req = "HTTP/1.1 404 Not Found\r\n";
        should_free = 1;
    }
    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");
    
    if (should_free == 0)
        free(req);
}