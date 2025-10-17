#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct Dato
{
    int clave;
    char *valor;
    struct Dato *siguiente;
    struct Dato *anterior;
}Dato;

typedef struct Cache
{
    int tamanho_memoria;
    int memoria_ocupada;
    Dato *cabecera;
    Dato *cola;
}Cache;

#endif // ESTRUCTURAS_H