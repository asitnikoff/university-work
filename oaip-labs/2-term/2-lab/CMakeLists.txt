cmake_minimum_required(VERSION 3.20)
project(2_lab)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        stack.cpp
        validation.cpp)

set(HEADER_FILES
        stack.h
        validation.h)

add_executable(2_lab ${SOURCE_FILES} ${HEADER_FILES})
