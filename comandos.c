#include "comandos.h"

//---- Helpers privados ----
static int validar_nombre(const char *nombre) {
    return nombre && nombre[0] >= 'A' && nombre[0] <= 'Z' && nombre[1] == '\0';
}
static void mover_a_cabecera(Cache *cache, Dato *n) {
    if (!n || n == cache->cabecera) return;

    //desacoplar
    if (n->anterior) n->anterior->siguiente = n->siguiente;
    if (n->siguiente) n->siguiente->anterior = n->anterior;
    if (cache->cola == n) cache->cola = n->anterior;

    //insertar al inicio
    n->anterior = NULL;
    n->siguiente = cache->cabecera;
    if (cache->cabecera) cache->cabecera->anterior = n;
    cache->cabecera = n;
    if (!cache->cola) cache->cola = n;
}

//---- Implementaciones publicas ----
void Help() {
    printf("Opciones:\n");
    printf("    -h, --help                  Muestra esta ayuda\n");
    printf("    -c, --create <TAMANHO>      Crea una cache (min 5, max %d)\n", MAX_CACHE_SIZE);
    printf("    -a, --add <NOMBRE>          Agrega/usa un dato (UNA letra A-Z)\n");
    printf("    -s, --search <NOMBRE>       Muestra posicion (1..N) o -1 si no esta\n");
    printf("    -l, --all                   Muestra todos los elementos en la cache (MRU->LRU)\n");
    printf("    -g, --get <NOMBRE>          Usa el dato (lo sube a cabecera)\n");
    printf("    -e, --exit                  Libera la memoria cache y sale\n");
}

int Create_cache(Cache *cache, char *tamanho) {
    //Si ya existe, limpiar
    if (cache->cabecera) {
        lru_say("Reiniciando cache existente (contenia %d elemento(s))", cache->memoria_ocupada);
        Exit_cache(cache, NULL); //NULL para no tocar el loop
    }
    if (char_to_int(tamanho, &cache->tamanho_memoria))
        return 1;

    if (cache->tamanho_memoria < 5 || cache->tamanho_memoria > MAX_CACHE_SIZE) {
        lru_err("El tamanho debe ser entre 5 y %d", MAX_CACHE_SIZE);
        cache->tamanho_memoria = 0;
        return 1;
    }
    cache->memoria_ocupada = 0;
    cache->cabecera = NULL;
    cache->cola = NULL;
    lru_say("Cache de tamanho %d creada, Todo OK", cache->tamanho_memoria);
    return 0;
}

int Add_data(Cache *cache, char *nombre) {
    if (cache->tamanho_memoria == 0) {
        lru_err("La cache no ha sido creada, use -c o --create para crearla");
        return 1;
    }
    if (!validar_nombre(nombre)) {
        lru_err("El nombre debe ser UNA letra mayuscula (A-Z)");
        return 1;
    }
    //ya existe? => usarlo (mover a cabecera)
    for (Dato *t = cache->cabecera; t; t = t->siguiente) {
        if (strcmp(t->valor, nombre) == 0) {
            mover_a_cabecera(cache, t);
            lru_say("Dato %s utilizado (prioridad actualizada)", nombre);
            return 0;
        }
    }
    //lleno => expulsar LRU (cola)
    if (cache->memoria_ocupada == cache->tamanho_memoria) {
        Dato *old = cache->cola;
        cache->cola = old->anterior;
        if (cache->cola) cache->cola->siguiente = NULL;
        else cache->cabecera = NULL;

        // Seguridad: anular enlaces antes de liberar
        old->anterior = NULL;
        old->siguiente = NULL;

        free(old->valor);
        free(old);
        cache->memoria_ocupada--;
    }
    //crear nuevo MRU
    Dato *nuevo = (Dato *)malloc(sizeof *nuevo);
    if (!nuevo) { lru_err("Sin memoria"); return 1; }
    nuevo->valor = (char *)malloc(2);
    if (!nuevo->valor) { free(nuevo); lru_err("Sin memoria"); return 1; }
    nuevo->valor[0] = nombre[0];
    nuevo->valor[1] = '\0';

    nuevo->anterior = NULL;
    nuevo->siguiente = cache->cabecera;
    if (cache->cabecera) cache->cabecera->anterior = nuevo;
    cache->cabecera = nuevo;
    if (!cache->cola) cache->cola = nuevo;

    cache->memoria_ocupada++;
    lru_say("Dato %s agregado a la cache, Todo OK", nombre);
    return 0;
}

int All_cache(Cache *cache) {
    if (cache->tamanho_memoria == 0) {
        lru_err("La cache no ha sido creada, use -c o --create para crearla");
        return 1;
    }
    if (cache->memoria_ocupada == 0) {
        lru_say("La cache esta vacia");
        return 0;
    }
    lru_say("Elementos en la cache (MRU -> LRU):");
    for (Dato *t = cache->cabecera; t; t = t->siguiente) {
        printf("    %s\n", t->valor);
    }
    return 0;
}

void Exit_cache(Cache *cache, int *running) {
    while (cache->cabecera) {
        Dato *temp = cache->cabecera;
        cache->cabecera = temp->siguiente;
        free(temp->valor);
        free(temp);
    }
    cache->cola = NULL;
    cache->memoria_ocupada = 0;
    //No resetear tamanho_memoria para que el usuario sepa el último valor configurado
    if (running) *running = false;
    lru_say("Saliendo del programa ...");
}

int Get_data(Cache *cache, const char *nombre) {
    if (cache->tamanho_memoria == 0) { lru_err("Cree la cache primero"); return 1; }
    if (!validar_nombre(nombre))     { lru_err("Nombre invalido");      return 1; }
    for (Dato *t = cache->cabecera; t; t = t->siguiente) {
        if (strcmp(t->valor, nombre) == 0) {
            mover_a_cabecera(cache, t);
            lru_say("Dato %s utilizado", nombre);
            return 0;
        }
    }
    lru_err("Dato %s no esta en cache", nombre);
    return 1;
}

int Search_data(Cache *cache, const char *nombre) {
    if (cache->tamanho_memoria == 0) { lru_err("Cree la cache primero"); return -1; }
    if (!validar_nombre(nombre))     { lru_err("Nombre invalido");       return -1; }
    int pos = 1;
    for (Dato *t = cache->cabecera; t; t = t->siguiente, ++pos) {
        if (strcmp(t->valor, nombre) == 0) {
            printf("%d\n", pos);
            return pos;
        }
    }
    printf("-1\n");
    return -1;
}
