# Versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y especificar el lenguaje
project(simp-db LANGUAGES CXX)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)              # Cambiar a C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Requerir el estándar
set(CMAKE_CXX_EXTENSIONS OFF)           # Desactivar extensiones específicas del compilador

# Incluir directorios
include_directories(include)             # Incluir el directorio de encabezados

# Detectar sistema operativo
if(WIN32)
    # Configurar para Windows usando MSYS2
    add_definitions(-DPLATFORM_WINDOWS)
    target_link_libraries(simp-db ws2_32)  # Enlazar la biblioteca de sockets de Windows
elseif(UNIX)
    # Configurar para Linux usando vcpkg
    set(CMAKE_TOOLCHAIN_FILE /path/to/vcpkg/scripts/buildsystems/vcpkg.cmake)

    # Buscar OpenSSL
    find_package(OpenSSL REQUIRED)           # Buscar OpenSSL
    message(STATUS "OpenSSL Include Dir: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")

    # Buscar nlohmann-json
    find_package(nlohmann_json CONFIG REQUIRED)  # Buscar nlohmann-json
endif()

# Agregar las bibliotecas
add_library(help_menu src/help_menu.cpp)
add_library(init src/comp/init.cpp)
add_library(hash_tool src/hash/hash_tool.cpp)
add_library(server src/server/server.cpp)
add_library(eval src/eval/eval.cpp)

# Vincular OpenSSL a hash_tool
target_link_libraries(hash_tool OpenSSL::SSL OpenSSL::Crypto)

# Crear el ejecutable
add_executable(simp-db src/main.cpp)

# Vincular las bibliotecas y nlohmann-json al ejecutable
target_link_libraries(simp-db help_menu init hash_tool server eval nlohmann_json::nlohmann_json)

# Vincular pthread en Linux
if(UNIX)
    target_link_libraries(simp-db pthread)
endif()

# Otras opciones específicas
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()
