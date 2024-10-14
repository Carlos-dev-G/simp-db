#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "comp/init.hpp"
#include "hash/hash_tool.hpp"
#include <fstream>

namespace fs = std::filesystem;
using json = nlohmann::json;

bool Iniciar()
{
#ifdef _WIN32
    system("cls"); // Limpia la consola en Windows
#elif defined(__linux__)
    system("clear"); // Limpia la consola en Linux
#endif

    // Ruta base
    fs::path baseDir = "simp-db";

    // Crear la estructura de carpetas
    std::cout << "Creando estructura de archivos" << std::endl;

    try
    {
        // Crear el directorio base
        if (!fs::exists(baseDir))
        {
            fs::create_directory(baseDir);
            std::cout << "Directorio base creado" << std::endl;
        }
        else
        {
            std::cout << "Directorio base ya existe" << std::endl;
        }

        // Crear el subdirectorio admin
        fs::path adminDir = baseDir / "admin";
        if (!fs::exists(adminDir))
        {
            fs::create_directory(adminDir);
            std::cout << "Directorio creado: " << adminDir << std::endl;
        }
        else
        {
            std::cout << "El directorio ya existe: " << adminDir << std::endl;
        }

        // Crear el subdirectorio data
        fs::path dataDir = baseDir / "data";
        if (!fs::exists(dataDir))
        {
            fs::create_directory(dataDir);
            std::cout << "Directorio creado: " << dataDir << std::endl;
        }
        else
        {
            std::cout << "El directorio ya existe: " << dataDir << std::endl;
        }

        // Crear el subdirectorio config
        fs::path configDir = baseDir / "config";
        if (!fs::exists(configDir))
        {
            fs::create_directory(configDir);
            std::cout << "Directorio creado: " << configDir << std::endl;
        }
        else
        {
            std::cout << "El directorio ya existe: " << configDir << std::endl;
        }

        // Crear el subdirectorio logs dentro de config
        fs::path logsDir = configDir / "logs";
        if (!fs::exists(logsDir))
        {
            fs::create_directory(logsDir);
            std::cout << "Directorio creado: " << logsDir << std::endl;
        }
        else
        {
            std::cout << "El directorio ya existe: " << logsDir << std::endl;
        }

        // Solicitar datos del usuario
        std::string Password;
        std::string Username;
        int PORT;

        std::cout << std::endl;
        std::cout << "A continuación ingrese el usuario (AD): ";
        std::getline(std::cin, Username);
        std::cout << std::endl;
        std::cout << "A continuación ingrese el password de (" << Username << "): ";
        std::getline(std::cin, Password);
        std::cout << std::endl;
        std::cout << "Ingrese el puerto por el que correrá el servidor: ";
        std::cin >> PORT;
        std::cout << std::endl;

        if (!Username.empty() && !Password.empty())
        {
            json Credenciales;

            // Crear la estructura de JSON con el hash del password
            Credenciales["Administradores"]["Usuarios"][Username]["Password_hash"] = hash_password(Password);

            // Guardar el JSON de credenciales
            fs::path ArchivoCredenciales = adminDir / "Credenciales.json";
            std::ofstream ArchivoSalida(ArchivoCredenciales);

            if (ArchivoSalida.is_open())
            {
                ArchivoSalida << Credenciales.dump(4); // Guardar el JSON con formato
                ArchivoSalida.close();
                std::cout << "Credenciales guardadas en " << ArchivoCredenciales << std::endl;
            }
            else
            {
                std::cerr << "Error al abrir el archivo de credenciales para escritura." << std::endl;
                return false;
            }

            // Guardar la configuración del puerto
            json Configuracion;
            Configuracion["Configuracion"]["PORT"] = PORT;

            // Guardar el JSON de configuración
            fs::path ArchivoConfiguracion = configDir / "config.json";
            std::ofstream ConfigArchivoSalida(ArchivoConfiguracion);

            if (ConfigArchivoSalida.is_open())
            {
                ConfigArchivoSalida << Configuracion.dump(4); // Guardar el JSON con formato
                ConfigArchivoSalida.close();
                std::cout << "Configuración guardada en " << ArchivoConfiguracion << std::endl;
            }
            else
            {
                std::cerr << "Error al abrir el archivo de configuración para escritura." << std::endl;
                return false;
            }

            std::cout << std::endl;
            std::cout << "Directorios y archivos creados exitosamente." << std::endl;
            std::cout << "Para iniciar la base de datos, usa: simp-db.exe run o simp-db.exe -r" << std::endl;
            return true;
        }
        else
        {
            std::cerr << "No se ingresó usuario o contraseña, o uno de ellos está vacío." << std::endl;
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ocurrió un error: " << e.what() << std::endl;
        return false;
    }
}