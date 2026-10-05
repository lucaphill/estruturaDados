cmake_minimum_required(VERSION 3.10)

project(lista5)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

add_executable(l5_run src/Main.c src/ListaDinamica.c)

target_include_directories(l5_run PRIVATE include)
