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

std::string Eval::CREAR(std::vector<std::string> Argumentos)
{
    json respuesta;

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
                respuesta["message"] = "Directorio creado.";
            }
            else
            {
                respuesta["status"] = "error";
                respuesta["message"] = "No se pudo crear el directorio.";
            }
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "El directorio ya existe.";
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
            {
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
                respuesta["message"] = "Archivo creado.";
                outFile.close();
            }
            else
            {
                respuesta["status"] = "error";
                respuesta["message"] = "No se pudo crear el archivo.";
            }
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "El archivo ya existe.";
        }
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Tipo de creación no reconocido.";
    }

    return respuesta.dump();
}

std::string Eval::BORRAR(std::vector<std::string> Argumentos)
{
    json respuesta;

    // Verificar que haya suficientes argumentos
    if (Argumentos.size() < 3)
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Argumentos insuficientes.";
        return respuesta.dump();
    }

    fs::path archivoPath;
    fs::path dirPath;

    // Determinar el tipo de eliminación (TABLA o DIRECTORIO)
    if (Argumentos[1] == "TABLA")
    {
        if (Argumentos[2] == "DENTRO" && Argumentos.size() > 4)
        {
            archivoPath = fs::path("simp-db") / "data" / Argumentos[3] / (Argumentos[4] + ".json");
        }
        else
        {
            archivoPath = fs::path("simp-db") / "data" / (Argumentos[2] + ".json");
        }

        try
        {
            if (fs::remove(archivoPath))
            {
                respuesta["status"] = "success";
                respuesta["message"] = "TABLA borrada.";
            }
            else
            {
                respuesta["status"] = "fallido";
                respuesta["message"] = "La TABLA no existe.";
            }
        }
        catch (const std::exception &e)
        {
            respuesta["status"] = "fallido";
            respuesta["message"] = "Error al borrar la TABLA: " + std::string(e.what());
        }
    }
    else if (Argumentos[1] == "DIRECTORIO")
    {
        dirPath = fs::path("simp-db") / "data" / Argumentos[2];

        try
        {
            if (Argumentos.size() > 3 && Argumentos[3] == "T")
            {
                fs::remove_all(dirPath);
                respuesta["status"] = "success";
                respuesta["message"] = "DIRECTORIO y su contenido borrados.";
            }
            else
            {
                if (fs::remove(dirPath))
                {
                    respuesta["status"] = "success";
                    respuesta["message"] = "DIRECTORIO borrado.";
                }
                else
                {
                    respuesta["status"] = "fallido";
                    respuesta["message"] = "El DIRECTORIO no existe o no está vacío.";
                }
            }
        }
        catch (const std::exception &e)
        {
            respuesta["status"] = "fallido";
            respuesta["message"] = "Error al borrar el DIRECTORIO: " + std::string(e.what());
        }
    }
    else
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Comando no reconocido.";
    }

    return respuesta.dump();
}

std::string Eval::INSERTAR(std::vector<std::string> Argumentos)
{
    nlohmann::json respuesta;
    fs::path file_path;
    nlohmann::json datos;

    // Verificar que hay suficientes argumentos
    if (Argumentos.size() < 3)
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número insuficiente de argumentos.";
        return respuesta.dump();
    }

    // Determinar la ruta dependiendo de si el archivo está en un directorio o en la raíz
    if (Argumentos.size() == 3) // Archivo en la raíz
    {
        file_path = fs::path("simp-db") / "data" / (Argumentos[2] + ".json");
    }
    else if (Argumentos.size() == 4) // Archivo dentro de un directorio
    {
        file_path = fs::path("simp-db") / "data" / Argumentos[3] / (Argumentos[4] + ".json");
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número inválido de argumentos.";
        return respuesta.dump();
    }

    if (fs::exists(file_path))
    {
        respuesta["status"] = "error";
        respuesta["message"] = "La tabla no existe.";
    }
    else
    {
    }

    return respuesta.dump();
}

std::string Eval::ACTUALIZAR(std::vector<std::string> Argumentos)
{
    json respuesta;
    fs::path file_path;

    // Verificar que hay suficientes argumentos
    if (Argumentos.size() < 3)
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número insuficiente de argumentos.";
        return respuesta.dump();
    }

    // Determinar la ruta dependiendo de si el archivo está en un directorio o en la raíz
    if (Argumentos.size() == 3) // Archivo en la raíz
    {
        file_path = fs::path("simp-db") / "data" / (Argumentos[2] + ".json");
    }
    else if (Argumentos.size() == 4) // Archivo dentro de un directorio
    {
        file_path = fs::path("simp-db") / "data" / Argumentos[3] / (Argumentos[4] + ".json");
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número inválido de argumentos.";
        return respuesta.dump();
    }

    // Verificar si el archivo existe
    if (!fs::exists(file_path))
    {
        respuesta["status"] = "error";
        respuesta["message"] = "La tabla no existe.";
        return respuesta.dump();
    }

    // Actualizar el contenido del archivo
    std::ofstream outFile(file_path);
    if (outFile.is_open())
    {
        // Supongamos que Argumentos[2] contiene el nuevo JSON en forma de string
        json nuevoContenido = json::parse(Argumentos.back()); // El último argumento es el nuevo contenido en JSON
        outFile << nuevoContenido.dump(4);                    // Escribir el nuevo contenido formateado
        outFile.close();

        respuesta["status"] = "success";
        respuesta["message"] = "Tabla actualizada con éxito.";
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "No se pudo abrir el archivo para actualizar.";
    }

    return respuesta.dump();
}

std::string Eval::OBTENER(std::vector<std::string> Argumentos)
{
    json respuesta;
    fs::path file_path;

    // Verificar que hay suficientes argumentos
    if (Argumentos.size() < 3)
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número insuficiente de argumentos.";
        return respuesta.dump();
    }

    // Determinar la ruta dependiendo de si el archivo está en un directorio o en la raíz
    if (Argumentos.size() == 3) // Archivo en la raíz
    {
        file_path = fs::path("simp-db") / "data" / (Argumentos[2] + ".json");
    }
    else if (Argumentos.size() == 4) // Archivo dentro de un directorio
    {
        file_path = fs::path("simp-db") / "data" / Argumentos[3] / (Argumentos[4] + ".json");
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "Número inválido de argumentos.";
        return respuesta.dump();
    }

    // Verificar si el archivo existe
    if (!fs::exists(file_path))
    {
        respuesta["status"] = "error";
        respuesta["message"] = "La tabla no existe.";
        return respuesta.dump();
    }

    // Leer el contenido del archivo
    std::ifstream inFile(file_path);
    if (inFile.is_open())
    {
        json contenido;
        inFile >> contenido; // Cargar el contenido JSON
        inFile.close();

        respuesta["status"] = "success";
        respuesta["data"] = contenido; // Incluir los datos obtenidos en la respuesta
    }
    else
    {
        respuesta["status"] = "error";
        respuesta["message"] = "No se pudo abrir el archivo para leer.";
    }

    return respuesta.dump();
}

std::string Eval::evaluar_querry(std::string querry)
{
    json respuesta;

    if (querry.empty())
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Consulta vacía.";
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
        respuesta["message"] = "La querry vino fallida.";
        return respuesta.dump();
    }

    if (inputs[0] == "CREAR")
    {
        if (inputs.size() >= 3)
        {
            return CREAR(inputs);
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "Error al crear: Querry (Consultar Querry).";
            return respuesta.dump();
        }
    }
    else if (inputs[0] == "BORRAR")
    {
        if (inputs.size() >= 2)
        {
            return BORRAR(inputs);
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "Error al borrar: Querry (Consultar Querry).";
            return respuesta.dump();
        }
    }
    else if (inputs[0] == "ACTUALIZAR")
    {
        return ACTUALIZAR(inputs);
    }
    else if (inputs[0] == "OBTENER")
    {
        return OBTENER(inputs);
    }
    else if (inputs[0] == "INSERTAR")
    {
        if (inputs.size() >= 3)
        {
            return INSERTAR(inputs);
        }
        else
        {
            respuesta["status"] = "error";
            respuesta["message"] = "Error al crear: Querry (Consultar Querry).";
            return respuesta.dump();
        }
    }
    else
    {
        respuesta["status"] = "fallido";
        respuesta["message"] = "Comando no válido.";
        return respuesta.dump();
    }
}
