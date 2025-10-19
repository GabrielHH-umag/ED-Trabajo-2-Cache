#include "funciones.h"
#include <limits.h>
#include <errno.h>

//---- Logging ----
void lru_err(const char *mensaje, ...) {
    va_list args;
    va_start(args, mensaje);
    printf("\tLruError: ");
    vprintf(mensaje, args);
    printf("\n");
    va_end(args);
}
void lru_say(const char *mensaje, ...) {
    va_list args;
    va_start(args, mensaje);
    printf("\tLru: ");
    vprintf(mensaje, args);
    printf("\n");
    va_end(args);
}

//---- Comandos ----
void get_command(char *str, int *command) {
    if (strcmp(str, "--help")   == 0 || strcmp(str, "-h") == 0) *command = HELP;
    else if (strcmp(str, "--create") == 0 || strcmp(str, "-c") == 0) *command = CREATE;
    else if (strcmp(str, "--add")    == 0 || strcmp(str, "-a") == 0) *command = ADD;
    else if (strcmp(str, "--all")    == 0 || strcmp(str, "-l") == 0) *command = ALL;
    else if (strcmp(str, "--get")    == 0 || strcmp(str, "-g") == 0) *command = GET;
    else if (strcmp(str, "--exit")   == 0 || strcmp(str, "-e") == 0) *command = EXIT;
    else if (strcmp(str, "--search") == 0 || strcmp(str, "-s") == 0) *command = SEARCH;
    else *command = -1;
}

//---- Conversion segura a int ----
int char_to_int(char *str, int *num) {
    char *end = NULL;
    errno = 0;
    long v = strtol(str, &end, 10);

    if (end == str || *end != '\0') {
        lru_err("El valor %s no es un numero valido", str);
        return 1;
    }
    if (errno == ERANGE) {
        lru_err("El valor %s esta fuera de rango", str);
        return 1;
    }
    if (v > INT_MAX || v < INT_MIN) {
        lru_err("El valor %s no cabe en un int", str);
        return 1;
    }
    *num = (int)v;
    return 0;
}

//---- Inicializar cache ----
int init_cache(Cache *cache) {
    cache->tamanho_memoria = 0;
    cache->memoria_ocupada = 0;
    cache->cabecera = NULL;
    cache->cola = NULL;
    return 0;
}
