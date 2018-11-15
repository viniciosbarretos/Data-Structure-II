cmake_minimum_required(VERSION 3.12)
project(data_structure C)

set(CMAKE_C_STANDARD 11)

add_executable(data_structure main.c
        libs/storage.c libs/storage.h
               libs/pcb.c libs/pcb.h
               libs/shell.c libs/shell.h
               libs/rand.c libs/rand.h
               libs/render.h libs/render.c
               libs/schedule.h libs/schedule.c
               libs/memory.h libs/memory.c
        )