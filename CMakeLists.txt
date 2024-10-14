# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y especificar el lenguaje
project(simp-db LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)              # Cambiar a C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Requerir el estándar
set(CMAKE_CXX_EXTENSIONS OFF)           # Desactivar extensiones específicas del compilador

# Incluir directorios
include_directories(include)            # Incluir el directorio de encabezados

# Buscar OpenSSL
find_package(OpenSSL REQUIRED)          # Buscar OpenSSL (REQUIRED significa que es obligatorio)

# Mostrar rutas de OpenSSL (para verificación)
message(STATUS "OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")

# Agregar las bibliotecas
add_library(help_menu src/help_menu.cpp)  # Crear la biblioteca help_menu
add_library(init src/comp/init.cpp)       # Crear la biblioteca init
add_library(hash_tool src/hash/hash_tool.cpp)  # Crear la biblioteca hash_tool

# Vincular OpenSSL a hash_tool
target_link_libraries(hash_tool OpenSSL::SSL OpenSSL::Crypto)

# Crear el ejecutable
add_executable(simp-db src/main.cpp)     # Crear el ejecutable con el nombre "simp-db"

# Vincular las bibliotecas al ejecutable
target_link_libraries(simp-db help_menu init hash_tool)

if(WIN32)
    # Opciones específicas para Windows
    add_definitions(-DPLATFORM_WINDOWS)
elseif(UNIX)
    # Opciones específicas para Linux
    add_definitions(-DPLATFORM_UNIX)
endif()

# Agregar rutas adicionales si es necesario para OpenSSL en Windows
if(WIN32)
    include_directories(${OPENSSL_INCLUDE_DIR})
    target_link_libraries(simp-db ${OPENSSL_LIBRARIES})
endif()

if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()
