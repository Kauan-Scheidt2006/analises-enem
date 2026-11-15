
cmake_minimum_required(VERSION 3.21)

project(AnalisesEnem VERSION 1.0.0 LANGUAGES CXX)

# ============================================================
# Configurações gerais
# ============================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# ============================================================
# Qt
# ============================================================

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

# ============================================================
# Função para habilitar avisos do compilador
# ============================================================

function(enem_habilitar_avisos alvo)
    if(MSVC)
        target_compile_options(${alvo} PRIVATE
            /W4
            /permissive-
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${alvo} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
        )
    endif()
endfunction()

# ============================================================
# Fontes dos componentes existentes
# ============================================================

set(ENEM_NUCLEO_FONTES

    # Registro
    src/Registro/Registro.h

    # Leitura
    src/Leitura/LeitorCSV.cpp
    src/Leitura/LeitorCSV.h

    # Cenários
    src/Cenarios/ConjuntoCenarios.cpp
    src/Cenarios/ConjuntoCenarios.h
    src/Cenarios/ServicoCenarios.cpp
    src/Cenarios/ServicoCenarios.h

    # Tipos do domínio
    src/Dominio/Tipos/TipoAlgoritmo.h
    src/Dominio/Tipos/DisposicaoInicial.h

    # Algoritmos
    src/Algoritmos/AlgoritmoOrdenacao.cpp
    src/Algoritmos/AlgoritmoOrdenacao.h

    src/Algoritmos/SelectionSort.cpp
    src/Algoritmos/SelectionSort.h

    src/Algoritmos/MergeSort.cpp
    src/Algoritmos/MergeSort.h

    src/Algoritmos/QuickSort.cpp
    src/Algoritmos/QuickSort.h

    # Catálogo de algoritmos
    src/Algoritmos/CatalogoAlgoritmos.cpp
    src/Algoritmos/CatalogoAlgoritmos.h
)

# ============================================================
# Experimentos, medições e resultados
# ============================================================
#
# Os arquivos são incluídos automaticamente porque seus
# componentes já estão em desenvolvimento e podem receber
# novos arquivos sem exigir alterações neste CMakeLists.
#
# CONFIGURE_DEPENDS solicita ao CMake uma nova configuração
# quando a relação de arquivos encontrados mudar.

file(GLOB_RECURSE ENEM_EXPERIMENTOS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Experimentos/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Experimentos/*.h"
)

file(GLOB_RECURSE ENEM_MEDICAO CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Medicao/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Medicao/*.h"
)

file(GLOB_RECURSE ENEM_RESULTADOS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Resultados/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Resultados/*.h"
)

list(APPEND ENEM_NUCLEO_FONTES
    ${ENEM_EXPERIMENTOS}
    ${ENEM_MEDICAO}
    ${ENEM_RESULTADOS}
)

# ============================================================
# Biblioteca principal
# ============================================================

add_library(enem_nucleo STATIC
    ${ENEM_NUCLEO_FONTES}
)

add_library(ENEM::Nucleo ALIAS enem_nucleo)

set_target_properties(enem_nucleo PROPERTIES
    AUTOMOC OFF
    AUTOUIC OFF
    AUTORCC OFF
)

target_include_directories(enem_nucleo PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Qt Core é necessário caso a implementação do LeitorCSV
# utilize funcionalidades do Qt.
target_link_libraries(enem_nucleo PRIVATE
    Qt6::Core
)

enem_habilitar_avisos(enem_nucleo)

# ============================================================
# Executável
# ============================================================

qt_add_executable(analises_enem
    src/main.cpp

    # Interface de terminal
    src/Terminal/AplicacaoTerminal.cpp
    src/Terminal/AplicacaoTerminal.h
)

target_link_libraries(analises_enem PRIVATE
    ENEM::Nucleo
    Qt6::Core
)

enem_habilitar_avisos(analises_enem)

# ============================================================
# Dataset
# ============================================================

set(ENEM_DATASET
    "${CMAKE_CURRENT_SOURCE_DIR}/dataset/banco.csv"
)

if(NOT EXISTS "${ENEM_DATASET}")
    message(FATAL_ERROR
        "Dataset não encontrado: ${ENEM_DATASET}"
    )
endif()

add_custom_command(TARGET analises_enem POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory
        "$<TARGET_FILE_DIR:analises_enem>/dataset"

    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "${ENEM_DATASET}"
        "$<TARGET_FILE_DIR:analises_enem>/dataset/banco.csv"

    COMMENT "Copiando o dataset para a pasta do executável..."
    VERBATIM
)
