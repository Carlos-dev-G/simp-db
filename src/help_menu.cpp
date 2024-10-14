#include <iostream>
#include "help_menu.hpp"

void HelpMenu()
{
    // Limpia la consola según el sistema operativo
#ifdef _WIN32            // Verifica si es Windows
    system("cls");       // Limpia la consola en Windows
#elif defined(__linux__) // Verifica si es Linux
    system("clear");     // Limpia la consola en Linux
#endif

    // Espacios para mejorar la legibilidad
    std::cout << std::endl;
    std::cout << " - - - - (simp-db) Menu - - - - " << std::endl;
    std::cout << std::endl;

    // Mostrar el menú de ayuda
    std::cout << "Ayuda: Uso del programa simp-db" << std::endl;
    std::cout << "  ( -h or help )          Muestra esta ayuda" << std::endl;
    std::cout << "  ( -i or init )          Crea la estructura de carpetas necesarias para el funcionamiento" << std::endl;

    // Puedes agregar más opciones aquí en el futuro
    // Ejemplo:
    // std::cout << "  -add <nombre>           Añade un nuevo elemento." << std::endl;
    // std::cout << "  -delete <nombre>        Elimina un elemento." << std::endl;

    // Espacios para mejorar la legibilidad al final
    std::cout << std::endl;
}
