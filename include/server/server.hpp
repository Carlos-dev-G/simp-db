#ifndef SERVER_HPP
#define SERVER_HPP

// Función que maneja la comunicación con un cliente
void HandleCliente(int cliente_socket);

// Función que inicializa Winsock en Windows
#ifdef _WIN32
void WinsockStart();
#endif

// Función principal del servidor TCP
int Servidor();

#endif // SERVER_HPP
