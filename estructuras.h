#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct 
{
    char *nombre;
    int prioridad;
} Dato;
typedef struct 
{
    int tamanho_memoria;
    int memoria_ocupada;
    Dato *memoria;
} Cache;
#endif // ESTRUCTURAS_H