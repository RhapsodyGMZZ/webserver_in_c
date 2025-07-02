#include "../header.h"

void handle_routes(char* path, int socket_fd) {
    printf("%s\n", path);
    char* req = NULL;
    int should_free = 1;

    if (strcmp(path, "/home") == 0) {
        req = render("home.html");
        should_free = 0;
        // printf("req: %s", req);
    } else if (strcmp(path, "/about") == 0) {
    } else {
        req = "HTTP/1.1 404 Not Found\r\n";
    }
    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");
    
    if (should_free == 0)
        free(req);
}