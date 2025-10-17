#include "estructuras.h"
#include "funciones.h"

void Help()
{
    printf("Opciones:\n");
    printf("    -h, --help                  Muestra esta ayuda\n");
    printf("    -c, --create <TAMANHO>      Crea una cache de tamanho variable\n");
    printf("    -a, --add <NOMBRE>          Agrega un elemento con nombre al cache\n");
    printf("    -s  --search <NOMBRE>       Busca si existe el dato con el nombre indicado y muestra su posicion\n");
    printf("    -l, --all                   Muestra todos los elementos en la cache\n");
    printf("    -g, --get <NOMBRE>          Busca la dato en base a su nombre en la cache\n");
    printf("    -e, --exit                  Libera la memoria cache\n");
}
int Create_cache(Cache *cache, char *tamanho)
{
    //si ocurre un error al transformar el string a int, se vuelve al loop principal, char_to_int ya imprime el error
    if(char_to_int(tamanho, &cache->tamanho_memoria))//char_to_int le da el tamanho a la cache
        return 1;
    if (cache->tamanho_memoria <= 0 || cache->tamanho_memoria > MAX_CACHE_SIZE)//verificacion de tamanho valido
    {
        lru_err("El tamanho de la cache debe ser mayor a 0 y menor o igual a %d", MAX_CACHE_SIZE);
        return 1;
    }
    //todo ok, inicializamos la cache en el caso que se ejecute el comando mas de una vez
    cache->memoria_ocupada = 0;
    cache->cabecera = NULL;
    cache->cola = NULL;
    lru_say("Cache de tamanho %d creada, Todo OK", cache->tamanho_memoria);
    return 0;
}
int Add_data(Cache *cache, char *nombre)
{
    if(cache->tamanho_memoria == 0)//no se ha usado comando create
    {
        lru_err("La cache no ha sido creada, use -c o --create para crearla");
        return 1;
    }
    Dato *temp = cache->cabecera; //valor temporal para recorrer la lista y mas adelante para eliminar el ultimo elemento
    //Busqueda de si ya existe el mismo dato
    while (temp != NULL)
    {
        
        if (strcmp(temp->valor, nombre) == 0)
        {
            lru_err("El dato con nombre %s ya existe en la cache, porfavor utilize -g o --get si quiere asignarlo devuelta a la cabecera\n", nombre);
            return 1;
        }
        temp = temp->siguiente;
    }
    //Si la memoria esta llena, eliminamos el ultimo elemento (cola)
    if (cache->memoria_ocupada == cache->tamanho_memoria)
    {
        temp = cache->cola;
        cache->cola = cache->cola->anterior;
        if (cache->cola != NULL)
            cache->cola->siguiente = NULL;
        else
            cache->cabecera = NULL; //Si la cola es NULL, la cabecera tambien debe serlo
        free(temp->valor);
        free(temp);
        cache->memoria_ocupada--;
    }
    //Ahora si, creamos el nuevo dato y lo asignamos a la cabecera
    Dato *nuevo = (Dato *)malloc(sizeof(Dato));
    if (nuevo == NULL)
    {
        lru_err("Error al asignar memoria para el nuevo dato");
        return 1;
    }
    nuevo->valor = (char *)malloc(strlen(nombre) + 1);
    if (nuevo->valor == NULL)
    {
        lru_err("Error al asignar memoria para el nombre del nuevo dato");
        free(nuevo);
        return 1;
    }
    //Se asigna al inicio de la lista
    strcpy(nuevo->valor, nombre);
    nuevo->siguiente = cache->cabecera;
    nuevo->anterior = NULL;
    
    if (cache->cabecera != NULL)
    {
        cache->cabecera->anterior = nuevo;
    }
    //Verificacion de si la lista estaba vacia
    if (cache->cola == NULL)
    {
        cache->cola = nuevo;
    }
    cache->cabecera = nuevo;
    cache->memoria_ocupada++;
    lru_say("Dato con nombre %s agregado a la cache, Todo OK", nombre);
    return 0;
}
int All_cache(Cache *cache)
{
    if(cache->tamanho_memoria == 0)
    {
        lru_err("La cache no ha sido creada, use -c o --create para crearla");
        return 1;
    }
    if (cache->memoria_ocupada == 0)
    {
        lru_say("La cache esta vacia");
        return 0;
    }
    Dato *temp = cache->cabecera;
    lru_say("Elementos en la cache:\n");
    while (temp != NULL)
    {
        printf("    %s\n", temp->valor);
        temp = temp->siguiente;
    }
    return 0;
}
void Exit_cache(Cache *cache, int *running)
{
    while (cache->cabecera != NULL)
    {
        
        Dato *temp = cache->cabecera;
        cache->cabecera = cache->cabecera->siguiente;
        free(temp->valor);
        free(temp);
        
    }
    *running = false;
    lru_say("Saliendo del programa ...\n");
}