cmake_minimum_required(VERSION 3.12)
project(data_structure C)

set(CMAKE_C_STANDARD 11)

add_executable(gerenciador_disco_fat main.c libs/render.c libs/render.h libs/storage.c libs/storage.h libs/boardRender.c libs/boardRender.h libs/persist.c libs/persist.c libs/persist.h)