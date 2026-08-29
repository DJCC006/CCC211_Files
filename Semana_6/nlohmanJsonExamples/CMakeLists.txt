cmake_minimum_required(VERSION 3.14)
project(nlohmanJsonExamples CXX)

# --- Estándar del lenguaje ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Dependencia externa: nlohmann/json (librería header-only) ---
# Se descarga en tiempo de configuración; no requiere instalación previa.
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

# --- Carpeta donde viven los .cpp de cada ejercicio y sus archivos de datos ---
set(EXAMPLE_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

# --- Carpeta de salida para los ejercicios que escriben JSON (no ensucia ./data) ---
set(EXAMPLE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/output")

# --- Detección automática de ejercicios: un .cpp = un ejecutable ---
# CONFIGURE_DEPENDS hace que CMake vuelva a escanear la carpeta al reconfigurar,
# para no tener que tocar este archivo cada vez que se agrega un ejercicio nuevo.
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "${EXAMPLE_DATA_DIR}/*.cpp")

foreach(source_file ${EXAMPLE_SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)

    add_executable(${exe_name} ${source_file})
    target_link_libraries(${exe_name} PRIVATE nlohmann_json::nlohmann_json)

    # Le da a cada programa, vía macro, la ruta absoluta a ./data,
    # así puede abrir sus JSON/NDJSON sin importar desde dónde se ejecute el binario.
    target_compile_definitions(${exe_name} PRIVATE
        EXAMPLE_DATA_DIR="${EXAMPLE_DATA_DIR}"
        EXAMPLE_OUTPUT_DIR="${EXAMPLE_OUTPUT_DIR}")
endforeach()
