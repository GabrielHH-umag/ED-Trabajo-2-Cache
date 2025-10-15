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
    printf("LruError: ");
    vprintf(mensaje, args);
    printf("\n");
    va_end(args);
}
void lru_say(const char *mensaje,...)
{
    va_list args;
    va_start(args, mensaje);
    printf("Lru: ");
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
    else
        *command = -1;
}
void char_to_int(char *str, int *num)
{
    *num = atoi(str);
    if (*num == 0 && strcmp(str, "0") != 0)
    {
        lru_err("El valor %s no es un numero valido", str);
        exit(EXIT_FAILURE);
    }
}
void init_cache(Cache *c)
{
    c->tamanho_memoria = 0;
    c->memoria_ocupada = 0;
    c->memoria = NULL;
}
// Guarda la cache en un archivo
void upload_cache_data(Cache *cache)
{
    FILE *cacheData = fopen("cache_data.txt", "w"); //Abre el archivo en modo escritura
    if (cacheData == NULL)
    {
        lru_err("No se pudo abrir el archivo para guardar la cache\n");
        return;
    }
    //Escribe la tamanho de la cache y la memoria ocupada
    fprintf(cacheData, "Tamanho de la cache: %d\n", cache->tamanho_memoria);
    fprintf(cacheData, "Memoria ocupada de la cache: %d\n", cache->memoria_ocupada);
    for (int i = 0; i < cache->memoria_ocupada; i++)
    {
        fprintf(cacheData,"Nombre: %s\n", cache->memoria[i].nombre);
        fprintf(cacheData,"Prioridad: %d\n", cache->memoria[i].prioridad);
    }
    fclose(cacheData);
    //lru_say("Cache guardada en archivo con tamanho %d y %d elementos", cache->tamanho_memoria, cache->memoria_ocupada);
}
//Carga la memoria de la cache desde un archivo
void load_cache_data(Cache *cache)
{
    FILE *cacheData = fopen("cache_data.txt", "r"); //Abre el archivo en modo lectura
    if (cacheData == NULL)
    {
        lru_err("No se pudo abrir el archivo para cargar la cache\n");
        return;
    }
    fscanf(cacheData, "Tamanho de la cache: %d\n", &cache->tamanho_memoria);
    fscanf(cacheData, "Memoria ocupada dla cache: %d\n", &cache->memoria_ocupada);
    cache->memoria = (Dato *)calloc(cache->tamanho_memoria, sizeof(Dato)); //Asigna memoria para la cache
    if (cache->memoria == NULL)
    {
        lru_err("No se pudo asignar memoria para la cache\n");
        fclose(cacheData);
        return;
    }
    for (int i = 0; i < cache->memoria_ocupada; i++)
    {
        cache->memoria[i].nombre = (char *)calloc(100, sizeof(char)); //Asigna memoria para el nombre del dato
        if (cache->memoria[i].nombre == NULL)
        {
            lru_err("No se pudo asignar memoria para el nombre del dato\n");
            fclose(cacheData);
            return;
        }
        fscanf(cacheData, "Nombre: %s\n", cache->memoria[i].nombre);
        fscanf(cacheData, "Prioridad: %d\n", &cache->memoria[i].prioridad);
    }
    fclose(cacheData);
    //lru_say("Cache cargada desde archivo con tamanho %d y %d elementos", cache->tamanho_memoria, cache->memoria_ocupada);
}

