cmake_minimum_required(VERSION 3.17)
project(numeric_integration)

add_compile_definitions(INPUT_PATH="build/input.bin")

add_executable(numeric_integration main.c)