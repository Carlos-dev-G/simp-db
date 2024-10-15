#ifndef EVAL_HPP
#define EVAL_HPP
#include <string>
#include <vector>

class Eval
{
private:
    std::string CREAR(std::vector<std::string> Argumentos);      // Método privado
    std::string BORRAR(std::vector<std::string> Argumentos);     // Método privado
    std::string ACTUALIZAR(); // Método privado
    std::string OBTENER();    // Método privado

public:
    std::string evaluar_querry(std::string querry);
};

#endif // EVAL_HPP
