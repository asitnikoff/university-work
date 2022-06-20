cmake_minimum_required(VERSION 3.20)
project(5_lab)

set(CMAKE_CXX_STANDARD 20)


set(SOURCE_FILES
        main.cpp
        tree.cpp
        validation.cpp)

set(HEADER_FILES
        tree.h
        validation.h)


add_executable(5_lab ${SOURCE_FILES} ${HEADER_FILES})
