#include "../header.h"

void handle_routes_get(char *path, int socket_fd)
{
    char *req = NULL;

    // Handling GET path here
    if (strcmp(path, "/home") == 0)
    {
        char* body = render("home.html");
        req = http_response(200, "text/html", body);
        free(body);
    }
    else
    {
        req = http_response(404, "text/plain", "This page does not exists"); 
    }
    send(socket_fd, req, strlen(req), 0);
    printf("\nsent !\n");
    
    free(req);
}

void handle_routes_post(char *path, int socket_fd, char *buffer)
{
    char *req = NULL;
    char *body = strstr(buffer, "\r\n\r\n");

    // Handling POST path here
    if (strcmp(path, "/submit") == 0)
    {
        if (body && strlen(body) > 4)
        {
            body += 4; // skip the "\r\n\r\n"
            test_form* form = parse_form(body);
            if (form) {
                printf("Name: %s\n", form->name ? form->name : "NULL");
                printf("Email: %s\n", form->email ? form->email : "NULL");
                printf("Message: %s\n", form->message ? form->message : "NULL");
                free_form(form);
            }
            req = http_response(200, "text/plain", "Success");
        }
        else
        {
            req =  http_response(400, "text/plain", "You need a body to send");
        }
    }
    else
    {
        req = http_response(404, "text/plain", "This URL does not exists");
    }

    send(socket_fd, req, strlen(req), 0);

    free(req);
}