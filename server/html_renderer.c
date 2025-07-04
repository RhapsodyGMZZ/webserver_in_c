#include "../header.h"

char* render(char* filename) {
    char dirname[FILENAME_MAX];
    strcpy(dirname, "./static/");
    strcat(dirname, filename);

    FILE* file = fopen(dirname, "r");

    if (file == NULL) {
        printf("failed to open %s\n", filename);
        return http_response(500, "text/plain", "An error has occurred.");
    }

    if (fseek(file, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        return http_response(500, "text/plain", "An error has occurred.");
    }

    long file_size = ftell(file);

    if (file_size == -1)
    {
        printf("failed to ftell %s\n", filename);
        return http_response(500, "text/plain", "An error has occurred.");
    }

    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + TMP_MAX);

    if (buffer == NULL) {
        printf("failed to allocate memory\n");
        fclose(file);
        return http_response(500, "text/plain", "An error has occurred.");
    }
    
    if (file != NULL) {
        fread(buffer, 1, file_size, file);
        buffer[file_size] = '\0';
        fclose(file);
    } else {
        printf("failed to fseek %s\n", filename);
        return http_response(500, "text/plain", "An error has occurred.");
    }
    return buffer;
}