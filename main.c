#include "comandos.h"

int main(int argc, char *argv[])
{
    
    if(argc < 2) 
    {
        lru_err("Argumnetos insuficientes, intente <--help> o <-h> para mas informacion\n");
        return 1;
    }
    Cache cache;
    int command;
    init_cache(&cache);
    get_command(argv[1], &command);
    switch (command)
    {
        case HELP:
        {
            Help();
            break;
        }
        case CREATE:
        {
            if (argc < 3)
            {
                lru_err("Falta el tamanho de la cache\n");
                return 1;
            }
            Create_cache(&cache, argv[2]);
            break;
        }
        case ADD:
        {
            if (argc < 3)
            {
                lru_err("Falta el nombre del elemento a agregar\n");
                return 1;
            }
            break;
        }
        case ALL:
        {
            break;
        }
        case GET:
        {
            if (argc < 3)
            {
                lru_err("Falta el nombre del elemento a buscar\n");
                return 1;
            }
            break;
        }
        case EXIT:
        {
            break;
        }
    }
    return 0;
}