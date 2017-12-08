cmake_minimum_required(VERSION 3.8)
project(Project_4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        sorter.c
        sorter.h
        README.md
        client.c

        )

add_executable(Project_4 ${SOURCE_FILES})