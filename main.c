#include "comandos.h"

int main(void) {
    Cache cache;
    int command = -1;
    char command_str[256];
    int running = true;
    char *argumento_1 = NULL;
    char *argumento_2 = NULL;

    init_cache(&cache);

    while (running == true) {
        printf("lru ");

        if (fgets(command_str, sizeof(command_str), stdin) == NULL) {
            if (feof(stdin)) {           // fin de entrada: salir limpio
                putchar('\n');
                break;
            }
            if (ferror(stdin)) {         // error real de E/S
                lru_err("Error de entrada. Abortando.");
                break;
            }
            // Caso raro: ni EOF ni error (muy improbable)
            lru_err("Error al leer el comando, -h para ayuda");
            break;
        }
        command_str[strcspn(command_str, "\n")] = 0; //quitar '\n'
        argumento_1 = strtok(command_str, " ");
        argumento_2 = strtok(NULL, " ");
        if (!argumento_1) continue;

        get_command(argumento_1, &command);

        switch (command) {
            case HELP:   Help(); break;
            case CREATE: {
                if (!argumento_2) { lru_err("Falta el argumento <TAMANHO>, -h para ayuda"); break; }
                Create_cache(&cache, argumento_2);
                break;
            }
            case ADD: {
                if (!argumento_2) { lru_err("Falta el argumento <NOMBRE>, -h para ayuda"); break; }
                Add_data(&cache, argumento_2);
                break;
            }
            case ALL:    All_cache(&cache); break;
            case GET: {
                if (!argumento_2) { lru_err("Falta el argumento <NOMBRE>, -h para ayuda"); break; }
                Get_data(&cache, argumento_2);
                break;
            }
            case EXIT:   Exit_cache(&cache, &running); break;
            case SEARCH: {
                if (!argumento_2) { lru_err("Falta el argumento <NOMBRE>, -h para ayuda"); break; }
                Search_data(&cache, argumento_2);
                break;
            }
            case -1:
            default:
                lru_err("Comando no reconocido, use -h o --help para ver la ayuda");
                break;
        }
    }
    return 0;
}