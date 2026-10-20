cmake_minimum_required(VERSION 3.10.0)
project(prog VERSION 0.1.0 LANGUAGES CXX)

include_directories(.)

if (MSVC)
    add_compile_options(/W3)
    add_compile_options(/std:c++latest)
    add_compile_options(/EHsc)
    add_compile_options(/utf-8)
else()
    add_compile_options(-Wall)
    add_compile_options(-std=c++23)
    add_compile_options(-fexceptions)
endif()

add_executable(prog main.cpp)