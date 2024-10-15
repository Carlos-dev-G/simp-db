Claro, aquí tienes los pasos para configurar y compilar tu proyecto en Windows usando **MSYS2** con **C++**, **nlohmann/json**, y **OpenSSL** sin `vcpkg`.

### Requisitos Previos

1. **Instalar MSYS2**:
   - Descarga e instala MSYS2 desde [su sitio web oficial](https://www.msys2.org/).
   - Abre el terminal de MSYS2 (MSYS2 MSYS).

2. **Actualizar el sistema**:
   - Ejecuta el siguiente comando para actualizar los paquetes y el sistema:

     ```bash
     pacman -Syu
     ```

   - Si se te pide cerrar la terminal después de la actualización, hazlo y vuelve a abrir el terminal de MSYS2.

3. **Instalar dependencias**:
   - Instala **Ninja**, **CMake**, **OpenSSL**, **nlohmann-json**, y el compilador de C++:

     ```bash
     pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja mingw-w64-x86_64-openssl mingw-w64-x86_64-nlohmann-json
     ```

### Pasos para Compilar y Ejecutar tu Proyecto

1. **Configurar el Proyecto**:
   - Abre una terminal de **MSYS2 MinGW 64-bit**.
   - Navega al directorio de tu proyecto:

     ```bash
     cd /c/Users/baa4t/Desktop/simp-db
     ```

   - Crea un directorio de construcción (si no lo has hecho ya):

     ```bash
     mkdir build
     cd build
     ```

2. **Ejecutar CMake con Ninja**:
   - Ejecuta CMake para configurar tu proyecto:

     ```bash
     cmake .. -G "Ninja"
     ```
     o
     ```bash
     cmake .. -G "MinGW Makefiles"
     ```

3. **Compilar el Proyecto**:
   - Una vez que la configuración haya terminado, compila el proyecto con:

     ```bash
     ninja
     ```

4. **Ejecutar el Programa**:
   - Después de compilar con éxito, puedes ejecutar tu programa. Asumiendo que tu ejecutable se llama `simp-db`:

     ```bash
     ./simp-db.exe
     ```