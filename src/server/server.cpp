#ifdef _WIN32
// Librerías necesarias para el uso de sockets en Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Enlaza la librería de sockets en Windows
#else
// Librerías necesarias para el uso de sockets en Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> // Para la función close()
#endif

// Librerías comunes
#include "server/server.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

// Función que manejará la comunicación con el cliente
void HandleCliente(int cliente_socket)
{
    using json = nlohmann::json;
    std::string mensaje;        // Variable para almacenar el mensaje recibido
    char buffer_temporal[1024]; // Buffer temporal para recibir datos
    int bytes_recibidos;        // Número de bytes recibidos

    // Bucle principal para recibir los datos del cliente
    while (true)
    {
        // Limpiar el buffer
        memset(buffer_temporal, 0, sizeof(buffer_temporal));

        // Recibir datos del cliente
        bytes_recibidos = recv(cliente_socket, buffer_temporal, sizeof(buffer_temporal) - 1, 0);

        if (bytes_recibidos <= 0)
        {
            // Si no se reciben datos o hay un error, salir del bucle
            std::cout << "Cliente desconectado o error en la recepción." << std::endl;
            break;
        }

        // Pasar el mensaje de char a std::string
        mensaje.assign(buffer_temporal, bytes_recibidos);
        std::cout << "Mensaje recibido: " << mensaje << std::endl;

        std::string respuesta = "1";
        send(cliente_socket, respuesta.c_str(), respuesta.size(), 0);
    }

    // Cerrar el socket del cliente al finalizar la comunicación
#ifdef _WIN32
    closesocket(cliente_socket);
#else
    close(cliente_socket);
#endif
}

// Esta función inicializa Winsock para Windows
#ifdef _WIN32
void WinsockStart()
{
    WSADATA WinsockData;
    if (WSAStartup(MAKEWORD(2, 2), &WinsockData) != 0)
    {
        std::cerr << "Error al inicializar Winsock" << std::endl;
        exit(1);
    }
}
#endif

int Servidor()
{
    int PORT;
    std::filesystem::path configuracion_path = std::filesystem::path("simp-db") / "config" / "config.json";

    if (!std::filesystem::exists(configuracion_path))
    {
        std::cout << "La configuracion no fue iniciada" << std::endl;
        std::cout << "Inicie: -i or init" << std::endl;
        return -1;
    }
    else
    {
        // Instancia para usar json
        using json = nlohmann::json;

        // Leer el archivo
        std::ifstream configuracion_json(configuracion_path);
        if (!configuracion_json.is_open())
        {
            std::cerr << "Error al abrir el archivo de configuracion" << std::endl;
            return 1;
        }

        json configuracion;
        configuracion_json >> configuracion;
        PORT = configuracion["Configuracion"]["PORT"];
    }

    // Si está en Windows, inicializar Winsock
#ifdef _WIN32
    WinsockStart();
#endif

    // Crear el socket que escuchará las conexiones
    int socket_de_escucha = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_de_escucha < 0)
    {
        std::cerr << "Error al crear el socket" << std::endl;
        return -1;
    }

    // Configurar la dirección del servidor
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // Aceptar conexiones en cualquier interfaz

    // Enlazar el socket a la dirección IP y el puerto
    if (bind(socket_de_escucha, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Error al enlazar el socket" << std::endl;
        return -1;
    }

    // Escuchar las conexiones
    if (listen(socket_de_escucha, SOMAXCONN) < 0)
    {
        std::cerr << "Error al escuchar en el socket" << std::endl;
        return -1;
    }

    std::cout << "Servidor escuchando en el puerto " << PORT << "..." << std::endl;

    while (true)
    {
        // Aceptar nuevas conexiones
        sockaddr_in cliente_addr;
        socklen_t cliente_size = sizeof(cliente_addr);
        int socket_cliente = accept(socket_de_escucha, (sockaddr *)&cliente_addr, &cliente_size);
        if (socket_cliente < 0)
        {
            std::cerr << "Error al aceptar la conexión" << std::endl;
            continue;
        }

        std::cout << "Nuevo cliente conectado." << std::endl;

        // Crear un nuevo hilo para el cliente
        std::thread(HandleCliente, socket_cliente).detach();
    }

#ifdef _WIN32
    closesocket(socket_de_escucha);
    WSACleanup(); // Limpiar Winsock
    return 0;
#else
    close(socket_de_escucha);
    return 0;
#endif
}
