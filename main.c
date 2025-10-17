#include "comandos.h"

int main()
{
    Cache cache;
    int command = -1;
    char command_str[20];
    int running = true;
    char *argumento_1= NULL;
    char *argumento_2= NULL;
    init_cache(&cache);
    while(running == true)
    {
        printf("lru ");
        
        if (fgets(command_str, sizeof(command_str), stdin) == NULL)//fgets lee hasta salto de linea, a comparacion de scanf que solo lee hasta espacio
        {
            lru_err("Error al leer el comando, evite el uso de caracteres especiales, -h para ayuda");
            continue;
        }
        command_str[strcspn(command_str, "\n")] = 0; //Para eliminar el salto de linea al final del string, asi podemos comparar bien con get_command
        //procedemos a separar el comando de sus argumentos, para que sea lo mas parecido a un cmd
        argumento_1 = strtok(command_str, " "); 
        argumento_2 = strtok(NULL, " ");
        get_command(argumento_1, &command);
        switch (command)
        {
            case HELP:
            {
                Help();
                break;
            }
            case CREATE:
            {
                if (argumento_2 == NULL)
                {
                    lru_err("Falta el argumento <TAMANHO>, -h para ayuda");
                    break;
                }
                Create_cache(&cache, argumento_2);
                break;
            }
            case ADD:
            {
                if (argumento_2 == NULL)
                {
                    lru_err("Falta el argumento <NOMBRE>, -h para ayuda");
                    break;
                }
                Add_data(&cache, argumento_2);
                break;
            }
            case ALL:
            {
                All_cache(&cache);
                break;
            }
            case GET:
            {
                //Get_data
                break;
            }
            case EXIT:
            {
                Exit_cache(&cache, &running);
                break;
            }
            case SEARCH:
            {
                //Search_data
                break;
            }
            case -1:
            {
                lru_err("Comando no reconocido, use -h o --help para ver la ayuda");
                break;
            }
        }
    }
    return 0;
}