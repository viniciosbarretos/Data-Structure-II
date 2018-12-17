cmake_minimum_required(VERSION 3.12)
project(SGBD C)

set(CMAKE_C_STANDARD 11)

add_executable(SGBD main.c libs/customer.c libs/customer.h libs/render.c libs/render.h libs/hashing.c libs/hashing.h libs/file.c libs/file.h libs/math.h libs/math.c)