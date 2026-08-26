cmake_minimum_required(VERSION 3.14)
project(FastCppCsvParserExamples CXX)

# --- Estándar del lenguaje ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Dependencia externa: fast-cpp-csv-parser (librería header-only) ---
# Se descarga en tiempo de configuración; no requiere instalación previa.
include(FetchContent)
FetchContent_Declare(
    fastcsv
    GIT_REPOSITORY https://github.com/ben-strasser/fast-cpp-csv-parser.git
    GIT_TAG master
)
FetchContent_MakeAvailable(fastcsv)

add_library(fast_csv_parser INTERFACE)
target_include_directories(fast_csv_parser INTERFACE ${fastcsv_SOURCE_DIR})

# --- Carpeta donde viven los .cpp de cada ejercicio y sus archivos de datos ---
set(EXAMPLE_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

# --- Detección automática de ejercicios: un .cpp = un ejecutable ---
# CONFIGURE_DEPENDS hace que CMake vuelva a escanear la carpeta al reconfigurar,
# para no tener que tocar este archivo cada vez que se agrega un ejercicio nuevo.
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "${EXAMPLE_DATA_DIR}/*.cpp")

foreach(source_file ${EXAMPLE_SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)

    add_executable(${exe_name} ${source_file})
    target_link_libraries(${exe_name} PRIVATE fast_csv_parser)

    # Le da a cada programa, vía macro, la ruta absoluta a ./data,
    # así puede abrir sus CSV/TSV sin importar desde dónde se ejecute el binario.
    target_compile_definitions(${exe_name} PRIVATE EXAMPLE_DATA_DIR="${EXAMPLE_DATA_DIR}")
endforeach()
