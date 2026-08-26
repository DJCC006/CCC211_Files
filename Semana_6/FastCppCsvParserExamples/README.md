# FastCppCsvParserExamples

Ejercicios de práctica de Estructura de Datos II usando la librería
header-only [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser).

## Estructura del proyecto

```
FastCppCsvParserExamples/
├── CMakeLists.txt          # Único script de build, detecta ejercicios automáticamente
├── .gitignore
├── README.md
├── build/                  # Generado por CMake (no se versiona)
└── data/
    ├── 01_basic_typed_read.cpp
    ├── 02_header_reordering.cpp
    ├── 03_quoted_fields.cpp
    ├── 04_csv_comments_summary.cpp
    ├── 05_invalid_input.cpp
    ├── products.csv
    ├── orders_quoted.csv
    ├── warehouse_stock.csv
    ├── transactions.tsv
    └── invalid_products_bad_price.csv
```

Cada `.cpp` dentro de `data/` se compila como un ejecutable independiente
con el mismo nombre (sin extensión). Para agregar un ejercicio nuevo basta con
dejar el `.cpp` en `data/`; no hay que tocar `CMakeLists.txt`.

## Cómo funciona el acceso a los archivos de datos

Los `.cpp` abren sus CSV/TSV usando la macro `EXAMPLE_DATA_DIR`, que CMake
define automáticamente con la ruta absoluta a `data/`:

```cpp
const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "products.csv";
```

Así, cada ejecutable encuentra sus archivos sin importar si se corre desde
`build/`, `build/Debug/` o cualquier otra carpeta.

## Requisitos

- CMake >= 3.14
- Compilador con soporte C++20 (GCC 10+, Clang 12+, MSVC 2019 16.11+ / VS 2022)
- Conexión a internet la primera vez que se configura el proyecto (CMake
  descarga `fast-cpp-csv-parser` vía `FetchContent`)

## Compilar y ejecutar

### Linux / macOS

```bash
cmake -B build
cmake --build build

# Ejecutar un ejemplo puntual
./build/01_basic_typed_read
```

### Windows (CLI de CMake, cualquier generador instalado)

```powershell
cmake -B build
cmake --build build

# Ejecutar un ejemplo puntual (generador multi-config, p. ej. Visual Studio)
.\build\Debug\01_basic_typed_read.exe
```

> Con generadores de un solo paso (Ninja, MinGW Makefiles) el binario queda
> directamente en `.\build\01_basic_typed_read.exe`, sin subcarpeta `Debug/`.

### Compilar en modo Release

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Reconfigurar tras agregar un ejercicio nuevo

Si `cmake --build build` no detecta el `.cpp` nuevo automáticamente, fuerza
una reconfiguración:

```bash
cmake -B build
cmake --build build
```
