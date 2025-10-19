#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include "constantes.h"

typedef struct Dato {
    char *valor;              //una letra mayuscula como string terminado en '\0'
    struct Dato *siguiente;   //siguiente en la lista
    struct Dato *anterior;    //anterior en la lista
} Dato;

typedef struct Cache {
    int tamanho_memoria;      //capacidad (minimo 5)
    int memoria_ocupada;      //cantidad actual
    Dato *cabecera;           //MRU (mas recientemente usado)
    Dato *cola;               //LRU (menos recientemente usado)
} Cache;

#endif //ESTRUCTURAS_H


