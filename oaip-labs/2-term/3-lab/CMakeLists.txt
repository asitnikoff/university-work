cmake_minimum_required(VERSION 3.20)
project(3_lab)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        double-linked-list.cpp
        validation.cpp)

set(HEADER_FILES
        double-linked-list.h
        validation.h)

add_executable(3_lab ${SOURCE_FILES} ${HEADER_FILES})
