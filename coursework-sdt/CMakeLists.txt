cmake_minimum_required(VERSION 3.22)
project(coursework_sdt)

set(CMAKE_CXX_STANDARD 20)


set(PROJECT_SOURCES
        src/accounts.cpp
        src/fstream-utilities.cpp
        src/main.cpp
        src/modules.cpp
        src/other-functions.cpp
        src/sha256.cpp
        src/sorts.cpp
        src/system-access.cpp
        src/validation.cpp)


set(PROJECT_HEADERS
        src/accounts.h
        src/fstream-utilities.h
        src/modules.h
        src/other-functions.h
        src/sha256.h
        src/sorts.h
        src/system-access.h
        src/validation.h
        src/variables.h)


add_executable(coursework_sdt ${PROJECT_SOURCES} ${PROJECT_HEADERS})
