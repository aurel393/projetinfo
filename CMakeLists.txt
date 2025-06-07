cmake_minimum_required(VERSION 3.28)
project(projetinfo C)

set(CMAKE_C_STANDARD 99)

add_executable(projetinfo main.c
        menu.h
        menu.c
        board.c
        board.h
        compteur.c
        compteur.h
        conquete.c
        conquete.h
        sauvegarde.c
        sauvegarde.h)
