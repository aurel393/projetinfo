cmake_minimum_required(VERSION 3.28)
project(projetinfo C)

set(CMAKE_C_STANDARD 99)

add_executable(projetinfo main.c
        menu.h
        menu.c
        start.c
        start.h
        board.c
        board.h
        game.c
        game.h
        gametest.c
        gametest.h
        compteur.c
        compteur.h
        conquete.c
        conquete.h
        sauvegarde.c
        sauvegarde.h)
