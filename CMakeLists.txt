cmake_minimum_required(VERSION 3.19)
project(TP1 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP1 partition.c utils.c)
add_executable(TP2 boustrophedon.c utils.c)
add_executable(TP3 graphe.c utils.c)
