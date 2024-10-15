# simp-db
Una simple base de datos (TCP) y JSON

(En desarrollo)

## Comandos Disponibles

```sql
# Crear una tabla JSON en la raíz local
CREAR TABLA <nombre_tabla> // Esto crea un archivo <nombre_tabla>.json

# Crear un directorio
CREAR DIRECTORIO <nombre_directorio> // Esto crea un directorio llamado <nombre_directorio>

# Crear una tabla dentro de un directorio
CREAR TABLA DENTRO <directorio> <nombre_tabla> // Esto crea un archivo <nombre_tabla>.json en <directorio>

# Borrar
BORRAR TABLA <nombre_tabla> // Borra el archivo <nombre_tabla>.json
BORRAR DIRECTORIO <nombre_directorio> // Solo lo borra si está vacío
BORRAR DIRECTORIO T <nombre_directorio> // Lo borra con todo su contenido dentro
```