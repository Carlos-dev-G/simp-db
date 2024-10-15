# simp-db
Una simple base de datos (TCP) y JSON

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)![License](https://img.shields.io/badge/license-MIT-brightgreen.svg) ![URUGUAY](https://img.shields.io/badge/URUGUAY-red.svg)

- Nota: cuando se le pasa un JSON, limpia los espacios en blanco.
- Ej: `INSERTAR MI_TABLA {"CARLITOS":"12"}`

## Comandos Disponibles

```sql
# Crear una tabla JSON en la raíz local
CREAR TABLA <nombre_tabla>
-- Crea un archivo <nombre_tabla>.json en la raíz de la base de datos

# Crear un directorio
CREAR DIRECTORIO <nombre_directorio>
-- Crea un directorio llamado <nombre_directorio> dentro de la base de datos

# Crear una tabla dentro de un directorio
CREAR TABLA DENTRO <directorio> <nombre_tabla>
-- Crea un archivo <nombre_tabla>.json dentro del directorio especificado

# Borrar
BORRAR TABLA <nombre_tabla>
-- Borra el archivo <nombre_tabla>.json de la base de datos

BORRAR DIRECTORIO <nombre_directorio>
-- Borra el directorio especificado solo si está vacío

BORRAR DIRECTORIO T <nombre_directorio>
-- Borra el directorio especificado junto con todo su contenido

BORRAR TABLA DENTRO <directorio> <nombre_tabla>
-- Borra el archivo <nombre_tabla>.json dentro del directorio especificado

# Insertar
INSERTAR <nombre_tabla> <json>
-- Inserta un JSON en la tabla especificada (archivo <nombre_tabla>.json)

INSERTAR DENTRO <directorio> <nombre_tabla> <json>
-- Inserta un JSON en la tabla <nombre_tabla>.json dentro del directorio especificado

# Actualizar
ACTUALIZAR <nombre_tabla> <json>
-- Reemplaza el contenido de la tabla especificada (archivo <nombre_tabla>.json) con el nuevo JSON dado.
-- El último argumento debe ser el nuevo contenido en formato JSON.

ACTUALIZAR DENTRO <directorio> <nombre_tabla> <json>
-- Reemplaza el contenido de la tabla <nombre_tabla>.json dentro del directorio especificado con el nuevo JSON dado.
-- El último argumento debe ser el nuevo contenido en formato JSON.

# Obtener
OBTENER <nombre_tabla>
-- Obtiene todo el contenido de la tabla especificada (archivo <nombre_tabla>.json).

OBTENER DENTRO <directorio> <nombre_tabla>
-- Obtiene todo el contenido de la tabla <nombre_tabla>.json dentro del directorio especificado.

```

Aquí tienes una tabla con comandos que incluyen ejemplos de JSON más grandes y sin espacios en blanco.

### Ejemplo de Uso de Comandos con JSON Grandes

| Comando                                                        | Descripción                                                                                                      | Ejemplo                                                                                          |
|---------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|
| `CREAR TABLA MI_TABLA`                                       | Crea un archivo `MI_TABLA.json` en la raíz de la base de datos.                                               | `CREAR TABLA MI_TABLA`                                                                           |
| `CREAR DIRECTORIO MIS_DATOS`                                 | Crea un directorio llamado `MIS_DATOS` dentro de la base de datos.                                            | `CREAR DIRECTORIO MIS_DATOS`                                                                     |
| `CREAR TABLA DENTRO MIS_DATOS MI_TABLA`                     | Crea un archivo `MI_TABLA.json` dentro del directorio `MIS_DATOS`.                                            | `CREAR TABLA DENTRO MIS_DATOS MI_TABLA`                                                         |
| `INSERTAR MI_TABLA {"nombre":"Carlos","edad":30,"ciudad":"Madrid","intereses":["programación","música","deportes"]}` | Inserta un JSON en la tabla `MI_TABLA`.                                                                        | `INSERTAR MI_TABLA {"nombre":"Carlos","edad":30,"ciudad":"Madrid","intereses":["programación","música","deportes"]}` |
| `INSERTAR DENTRO MIS_DATOS MI_TABLA {"nombre":"Ana","edad":25,"ciudad":"Barcelona","intereses":["arte","cocina","viajes"]}` | Inserta un JSON en `MI_TABLA.json` dentro del directorio `MIS_DATOS`.                                         | `INSERTAR DENTRO MIS_DATOS MI_TABLA {"nombre":"Ana","edad":25,"ciudad":"Barcelona","intereses":["arte","cocina","viajes"]}` |
| `OBTENER MI_TABLA`                                           | Obtiene todo el contenido del archivo `MI_TABLA.json`.                                                          | `OBTENER MI_TABLA`                                                                                |
| `ACTUALIZAR MI_TABLA {"nombre":"Carlos","edad":31,"ciudad":"Madrid","intereses":["programación","música","correr"]}` | Reemplaza el contenido de `MI_TABLA.json` con el nuevo JSON dado.                                              | `ACTUALIZAR MI_TABLA {"nombre":"Carlos","edad":31,"ciudad":"Madrid","intereses":["programación","música","correr"]}` |
| `BORRAR TABLA MI_TABLA`                                      | Borra el archivo `MI_TABLA.json` de la base de datos.                                                          | `BORRAR TABLA MI_TABLA`                                                                           |
| `BORRAR DIRECTORIO MIS_DATOS`                                | Borra el directorio `MIS_DATOS` solo si está vacío.                                                            | `BORRAR DIRECTORIO MIS_DATOS`                                                                    |
| `BORRAR DIRECTORIO T MIS_DATOS`                              | Borra el directorio `MIS_DATOS` junto con todo su contenido.                                                  | `BORRAR DIRECTORIO T MIS_DATOS`                                                                  |

### Descripción de Ejemplo

1. **Crear Tabla**: Se crea una tabla llamada `MI_TABLA`.
2. **Crear Directorio**: Se crea un directorio llamado `MIS_DATOS`.
3. **Crear Tabla Dentro del Directorio**: Se crea `MI_TABLA` dentro de `MIS_DATOS`.
4. **Insertar Datos**: Se insertan registros JSON más complejos con datos variados.
5. **Obtener Datos**: Se obtienen los datos de `MI_TABLA`.
6. **Actualizar Datos**: Se actualiza el registro de `Carlos` con un nuevo interés.
7. **Borrar Tabla**: Finalmente, se eliminan la tabla y el directorio.