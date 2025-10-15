#include "estructuras.h"
#include "funciones.h"

void Help()
{
    //printf("Uso: lru [OPCION] [ARGUMENTOS]\n");
    printf("Opciones:\n");
    printf("    -h, --help                  Muestra esta ayuda\n");
    printf("    -c, --create <TAMANHO>      Crea una cache de tamanho variable\n");
    printf("    -a, --add <NOMBRE>          Agrega un elemento con nombre al cache\n");
    printf("    -l, --all                   Muestra todos los elementos en la cache\n");
    printf("    -g, --get <NOMBRE>          Busca la dato en base a su nombre en la cache\n");
    printf("    -e, --exit                  Libera la memoria cache\n");
}
void Create_cache(Cache *cache, char *argumento)
{
    char_to_int(argumento, &cache->tamanho_memoria); //Transforma el argumento a int

    if (cache->tamanho_memoria <= 0 || cache->tamanho_memoria > MAX_CACHE_SIZE)
    {
        lru_err("El tamanho de la cache debe ser mayor a 0 y menor o igual a %d", MAX_CACHE_SIZE);
        exit(EXIT_FAILURE);
    }
    cache->memoria_ocupada = 0;
    cache->memoria = (Dato *)calloc(cache->tamanho_memoria, sizeof(Dato)); //Asigna memoria para la cache en estados nulos o 0
    if (cache->memoria == NULL)
    {
        lru_err("No se pudo asignar memoria para la cache");
        exit(EXIT_FAILURE);
    }
    
    //TODO: Que lanze un error si ya existe una cache creada

    upload_cache_data(cache); //Guarda la cache en un archivo
    lru_say("Cache de tamanho %d creada", cache->tamanho_memoria);
}