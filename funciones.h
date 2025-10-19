#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estructuras.h"
#include <stdarg.h>

//Logging
void lru_err(const char *mensaje, ...);
void lru_say(const char *mensaje, ...);

//Utilidades
void get_command(char *str, int *command);
int  char_to_int(char *str, int *num);
int  init_cache(Cache *cache);

#endif //FUNCIONES_H


