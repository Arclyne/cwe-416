#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

struct auth {
    char name[32];
    int auth;
};

struct auth *auth;
char *service;

int main(int argc, char **argv) {
    char line[128];
    printf("Ingresa [auth admin] o reset o [service ftp] o login.\n");
    while (1) 
    {
        printf("[ auth = %p, service = %p ]\n", auth, service);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;
        
        if (strncmp(line, "auth ", 5) == 0)
        {
            auth = malloc(sizeof(auth));
            memset(auth, 0, sizeof(auth));
            if (strlen(line + 5) < 31)
            {
                strcpy(auth -> name, line + 5);
            }
        }
        if (strncmp(line, "reset", 5) == 0)
        {
            free(auth);
        }
        if (strncmp(line, "service", 7) == 0)
        {
            service = strdup(line + 7);
        }
        if (strncmp(line, "login", 5) == 0)
        {
            if (auth -> auth)
            {
                printf("Bienvenido. lo lograste!\n");
            }
            else
            {
                printf("por favor, ingrese su nombre en la opcion auth\n");
            }
        }
    }
}