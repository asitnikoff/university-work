cmake_minimum_required(VERSION 3.20)
project(9_lab)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        main.cpp
        validation.cpp
        book.cpp
        files-work.cpp
        sorts.cpp
        searches.cpp
        output-table.cpp)

set(HEADER_FILES
        book.h
        validation.h
        files-work.h
        sorts.h
        searches.h
        output-table.h)

add_executable(9_lab ${SOURCE_FILES} ${HEADER_FILES})
