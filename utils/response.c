#include "../header.h"

char *http_response(int status_code, char *content_type, char *body)
{
    char *status = malloc(100);

    switch (status_code)
    {
    case 200:
        strcpy(status, "HTTP/1.1 200 OK\r\n");
        break;
    case 400:
        strcpy(status, "HTTP/1.1 400 Bad Request\r\n");
        break;
    case 401:
        strcpy(status, "HTTP/1.1 401 Unauthorized\r\n");
        break;
    case 404:
        strcpy(status, "HTTP/1.1 404 Not Found\r\n");
        break;
    case 405:
        strcpy(status, "HTTP/1.1 405 Method Not Allowed\r\n");
        break;
    case 500:
        strcpy(status, "HTTP/1.1 500 Internal Server Error\r\n");
        break;

    default:
        break;
    }

    size_t total_size = strlen(status) + strlen(content_type) + strlen(body) + 100;
    char *req = malloc(total_size);

    sprintf(req, "%sContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s", status, content_type, strlen(body), body);

    free(status);
    return req;
}