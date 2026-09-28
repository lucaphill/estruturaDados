cmake_minimum_required(VERSION 3.10)

project(lista4)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

add_executable(l4_run src/texte.c)

target_include_directories(l4_run PRIVATE include)
