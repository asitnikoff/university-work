cmake_minimum_required(VERSION 3.20)
project(1_lab)

set(CMAKE_CXX_STANDARD 20)


set(PROJECT_HEADERS
        recursions.h)


set(PROJECT_SOURCES
        main.cpp
        recursions.cpp)


add_executable(1_lab ${PROJECT_HEADERS} ${PROJECT_SOURCES})
