#include "../header.h"

char* render(char* filename) {
    char dirname[FILENAME_MAX] = "./static/";

    FILE* file = fopen(strcat(dirname, filename), "r");
    
    if (fseek(file, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    long file_size = ftell(file);

    if (file_size == -1)
    {
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + TMP_MAX);

    if (buffer == NULL) {
        printf("failed to allocate memory\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    strcpy(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    size_t header_len = strlen(buffer);

    if (file != NULL) {
        fread(buffer + header_len, 1, file_size, file);
        buffer[header_len + file_size] = '\0';
        fclose(file);
    } else {
        printf("test");
    }
    return buffer;
}