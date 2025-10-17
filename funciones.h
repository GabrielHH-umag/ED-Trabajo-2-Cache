#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "estructuras.h"
#include <stdarg.h>
//funciones de lru
void lru_err(const char *mensaje,...)
{
    va_list args;
    va_start(args, mensaje);
    printf("\tLruError: ");
    vprintf(mensaje, args);
    printf("\n");
    va_end(args);
}
void lru_say(const char *mensaje,...)
{
    va_list args;
    va_start(args, mensaje);
    printf("\tLru: ");
    vprintf(mensaje, args);
    printf("\n");
    va_end(args);
}
void get_command(char *str, int *command)
{
    if (strcmp(str, "--help") == 0 || strcmp(str, "-h") == 0)
        *command = HELP;
    else if (strcmp(str, "--create") == 0 || strcmp(str, "-c") == 0)
        *command = CREATE;
    else if (strcmp(str, "--add") == 0 || strcmp(str, "-a") == 0)
        *command = ADD;
    else if (strcmp(str, "--all") == 0 || strcmp(str, "-l") == 0)
        *command = ALL;
    else if (strcmp(str, "--get") == 0 || strcmp(str, "-g") == 0)
        *command = GET;
    else if (strcmp(str, "--exit") == 0 || strcmp(str, "-e") == 0)
        *command = EXIT;
    else if (strcmp(str, "--search") == 0 || strcmp(str, "-s") == 0)
        *command = SEARCH;
    else
        *command = -1;
}
int char_to_int(char *str, int *num)
{
    *num = atoi(str);
    if (*num == 0 && strcmp(str, "0") != 0)
    {
        lru_err("El valor %s no es un numero valido", str);
        return 1;
    }
    return 0;
}
int init_cache(Cache *cache)
{
    cache->tamanho_memoria = 0;
    cache->memoria_ocupada = 0;
    cache->cabecera = NULL;
    cache->cola = NULL;
    return 0;
}


