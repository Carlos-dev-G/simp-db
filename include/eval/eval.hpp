#ifndef EVAL_HPP
#define EVAL_HPP
#include <string>
#include <vector>

class Eval
{
private:
    std::string CREAR(std::vector<std::string> Argumentos);      // Método privado
    std::string BORRAR(std::vector<std::string> Argumentos);     // Método privado
    std::string ACTUALIZAR(std::vector<std::string> Argumentos); // Método privado
    std::string OBTENER(std::vector<std::string> Argumentos);    // Método privado
    std::string INSERTAR(std::vector<std::string> Argumentos);   // Método privado

public:
    std::string evaluar_querry(std::string querry);
};

#endif // EVAL_HPP
