cmake_minimum_required(VERSION 3.12)
project(sgbd_arvore_b_mais C)

set(CMAKE_C_STANDARD 11)

add_executable(sgbd_arvore_b_mais main.c libs/render.c libs/render.h libs/bplustree.c libs/bplustree.h libs/file.c libs/file.h libs/student.c libs/student.h libs/utils.c libs/utils.h)