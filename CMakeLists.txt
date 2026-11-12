cmake_minimum_required(VERSION 3.21)

project(AnalisesEnem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
qt_standard_project_setup()

function(enem_habilitar_avisos alvo)
    if(MSVC)
        target_compile_options(${alvo} PRIVATE /W4 /permissive-)
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

add_library(enem_nucleo STATIC
    src/Registro/Registro.h
    src/Leitura/LeitorCSV.cpp
    src/Leitura/LeitorCSV.h
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

enem_habilitar_avisos(enem_nucleo)

qt_add_executable(analises_enem
    src/main.cpp
)

target_link_libraries(analises_enem PRIVATE
    ENEM::Nucleo
    Qt6::Core
)

enem_habilitar_avisos(analises_enem)

set(ENEM_DATASET "${CMAKE_CURRENT_SOURCE_DIR}/dataset/banco.csv")
if(NOT EXISTS "${ENEM_DATASET}")
    message(FATAL_ERROR "Dataset não encontrado: ${ENEM_DATASET}")
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
