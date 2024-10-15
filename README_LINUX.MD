Para instalar las dependencias necesarias (OpenSSL y nlohmann_json) en tu entorno de Codespaces usando vcpkg y asegurarte de que CMake las reconozca, sigue estos pasos:

### 1. Instalar vcpkg

Si no lo has hecho aún, primero debes clonar e instalar vcpkg:

```bash
# Clona el repositorio de vcpkg
git clone https://github.com/microsoft/vcpkg.git

# Navega al directorio de vcpkg
cd vcpkg

# Ejecuta el script de instalación
./bootstrap-vcpkg.sh
```

### 2. Instalar las Dependencias

Usa vcpkg para instalar OpenSSL y nlohmann_json. Asegúrate de estar en el directorio de vcpkg al ejecutar estos comandos:

```bash
# Instala OpenSSL
./vcpkg install openssl

# Instala nlohmann_json
./vcpkg install nlohmann-json
```

### 3. Integrar vcpkg con CMake

Después de instalar las dependencias, asegúrate de que CMake sepa usar vcpkg. Esto se puede hacer estableciendo el archivo de herramienta (toolchain) en tu `CMakeLists.txt`, como ya lo has hecho. Asegúrate de que la línea correspondiente esté presente en tu archivo:

```cmake
set(CMAKE_TOOLCHAIN_FILE /vcpkg/scripts/buildsystems/vcpkg.cmake)
```

### 4. Compilar Tu Proyecto

Luego de haber instalado las dependencias, regresa al directorio de tu proyecto y compila:

```bash
# Navega al directorio de construcción
cd /workspaces/codespaces-blank/simp-db/build

# Ejecuta CMake
cmake ..

# Compila el proyecto
make
```