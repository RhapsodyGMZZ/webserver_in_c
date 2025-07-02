#include "header.h"

int main()
{
    // prevents output buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    int server_fd, new_socket = 0;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if ((setsockopt(server_fd, SOL_SOCKET,
                    SO_REUSEADDR, &opt,
                    sizeof(opt))) != 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        close(server_fd);
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if (listener(new_socket, server_fd, address, addrlen) != 0) {
        perror("couldn't listen");
        exit(EXIT_FAILURE);
    };
    
    close(server_fd);
    return 0;
}

/*
HTTP/1.1 201 Created
Content-Type: application/json
Location: http://example.com/users/123

{
  "message": "New user created",
  "user": {
    "id": 123,
    "firstName": "Example",
    "lastName": "Person",
    "email": "bsmth@example.com"
  }
}
*/