#ifndef COMANDOS_H
#define COMANDOS_H

#include "estructuras.h"
#include "funciones.h"

void Help(void);
int  Create_cache(Cache *cache, char *tamanho);
int  Add_data(Cache *cache, char *nombre);
int  All_cache(Cache *cache);
void Exit_cache(Cache *cache, int *running);
int  Get_data(Cache *cache, const char *nombre);
int  Search_data(Cache *cache, const char *nombre);

#endif //COMANDOS_H