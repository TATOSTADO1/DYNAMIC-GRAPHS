cmake_minimum_required(VERSION 3.29.6)
project(LISTA_ESTATICA)

set(CMAKE_CXX_STANDARD 20)

add_executable(LISTA_ESTATICA main.cpp
        Menu.cpp
        Menu.h
        Adyacentes.cpp
        Adyacentes.h
        Grafo.cpp
        Grafo.h
        Aristas.cpp
        Aristas.h
)
