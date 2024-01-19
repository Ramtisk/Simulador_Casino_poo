cmake_minimum_required(VERSION 3.26)
project(Projetos_Clion)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projetos_Clion main.cpp
        src/Casino.cpp
        Include/Casino.h
        src/Jogador.cpp
        Include/Jogador.h
        src/Maquina.cpp
        Include/Maquina.h)
