cmake_minimum_required(VERSION 3.27)
project(bomb_student C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(bomb_student
        bomb.c
        config.h
        driverlib.h
        phases.h
        support.c
        support.h)
