#include "eval/eval.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

namespace fs = std::filesystem;
using json = nlohmann::json;

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
namespace fs = std::filesystem;
using json = nlohmann::json;

std::string Eval::CREAR(std::vector<std::string> Argumentos)
{
    json respuesta; // Declarar el objeto JSON al principio

    // Verificar que hay suficientes argumentos
    if (Argumentos.size() < 3)
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número insuficiente de argumentos.";
        return respuesta.dump();
    }

    if (Argumentos[1] == "DIRECTORIO")
    {
        fs::path folderPath = fs::path("simp-db") / "data" / Argumentos[2];

        if (!fs::exists(folderPath))
        {
            if (fs::create_directory(folderPath))
            {
                respuesta["status"] = "success";
                respuesta["message"] = "Directorio creado";
            }
            else
            {
                respuesta["status"] = "error";
                respuesta["message"] = "No se pudo crear el directorio";
            }
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "El directorio ya existe";
        }
    }
    else if (Argumentos[1] == "TABLA")
    {
        fs::path filePath;

        // Manejo de la creación de archivos en diferentes ubicaciones
        if (Argumentos[2] != "DENTRO")
        {
            filePath = fs::path("simp-db") / "data" / (Argumentos[2] + ".json");
        }
        else
        {
            if (Argumentos.size() < 5)
            { // Verifica que haya suficientes argumentos
                respuesta["status"] = "error";
                respuesta["message"] = "Número insuficiente de argumentos para crear en DENTRO.";
                return respuesta.dump();
            }
            filePath = fs::path("simp-db") / "data" / Argumentos[3] / (Argumentos[4] + ".json");
        }

        // Verifica si el archivo ya existe y lo crea si no
        if (!fs::exists(filePath))
        {
            std::ofstream outFile(filePath);
            if (outFile.is_open())
            {
                respuesta["status"] = "success";
                respuesta["message"] = "Archivo creado";
                outFile.close(); // Cierra el archivo
            }
            else
            {
                respuesta["status"] = "error";
                respuesta["message"] = "No se pudo crear el archivo";
            }
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "El archivo ya existe";
        }
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Tipo de creación no reconocido.";
    }

    return respuesta.dump();
}

std::string Eval::BORRAR()
{
    json respuesta;
    respuesta["status"] = "fallido";
    respuesta["message"] = "La funcion BORRAR no esta implementada.";
    return respuesta.dump();
}

std::string Eval::ACTUALIZAR()
{
    json respuesta;
    respuesta["status"] = "fallido";
    respuesta["message"] = "La función ACTUALIZAR no esta implementada.";
    return respuesta.dump();
}

std::string Eval::OBTENER()
{
    json respuesta;
    respuesta["status"] = "fallido";
    respuesta["message"] = "La funcion OBTENER no esta implementada.";
    return respuesta.dump();
}

std::string Eval::evaluar_querry(std::string querry)
{
    json respuesta;

    if (querry.empty())
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Consulta vacia";
        return respuesta.dump();
    }

    std::istringstream ISS(querry);
    std::string key;
    std::vector<std::string> inputs;

    while (ISS >> key)
    {
        inputs.push_back(key);
    }

    if (inputs.empty())
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "La querry vino fallida";
        return respuesta.dump();
    }

    if (inputs[0] == "CREAR")
    {
        if (inputs.size() > 3)
        {
            return CREAR(inputs);
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "Error al crear: Querry (CREAR Nombre)";
            return respuesta.dump();
        }
    }
    else if (inputs[0] == "BORRAR")
    {
        return BORRAR();
    }
    else if (inputs[0] == "ACTUALIZAR")
    {
        return ACTUALIZAR();
    }
    else if (inputs[0] == "OBTENER")
    {
        return OBTENER();
    }
    else
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Comando no válido.";
        return respuesta.dump();
    }
}
