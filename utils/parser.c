#include "../header.h"

// Thanks to copilot for this func (nsm jamais je parse de l'URL encodé en C, la flemme)
void url_decode(char* str) {
    char* src = str;
    char* dst = str;
    
    while (*src) {
        if (*src == '%' && src[1] && src[2]) {
            // Convert hex to char
            int hex_val;
            sscanf(src + 1, "%2x", &hex_val);
            *dst++ = (char)hex_val;
            src += 3;
        } else if (*src == '+') {
            *dst++ = ' ';
            src++;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

test_form* parse_form(char* body) {
    printf("BODY == '%s'\n", body);
    
    char* body_copy = strdup(body);
    if (!body_copy) {
        return NULL;
    }
    
    test_form* form = malloc(sizeof(test_form));
    if (!form) {
        free(body_copy);
        return NULL;
    }
    
    form->name = NULL;
    form->email = NULL;
    form->message = NULL;
    
    char* token = strtok(body_copy, "&");
    while (token != NULL) {
        printf("TOKEN == '%s'\n", token);
        
        // Split key=value
        char* equals = strchr(token, '=');
        if (equals) {
            *equals = '\0';
            char* key = token;
            char* value = equals + 1;
            
            url_decode(value);
            
            if (strcmp(key, "name") == 0) {
                form->name = strdup(value);
            } else if (strcmp(key, "email") == 0) {
                form->email = strdup(value);
            } else if (strcmp(key, "message") == 0) {
                form->message = strdup(value);
            }
        }
        
        token = strtok(NULL, "&");
    }
    
    free(body_copy);
    return form;
}


void free_form(test_form* form) {
    if (form) {
        free(form->name);
        free(form->email);
        free(form->message);
        free(form);
    }
}