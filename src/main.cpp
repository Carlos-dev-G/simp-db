#include <iostream>
#include <cstring>
#include "help_menu.cpp"
#include "comp/init.cpp"
#include "server/server.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        // Verificar los argumentos
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0) // Comparar usando strcmp
        {
            HelpMenu();
        }
        else if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "init") == 0)
        {
            Iniciar();
        }
        else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "start") == 0)
        {
            Servidor();
        }
        else
        {
            std::cout << "(simp-db) Argumento invalido [Ayuda -h]" << std::endl;
        }
    }
    else
    {
        std::cout << "(simp-db) Sin argumentos de entrada [Ayuda -h]" << std::endl;
    }

    // Buenas prácticas
    return 0;
}
