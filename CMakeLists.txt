cmake_minimum_required(VERSION 3.30)
project(circles_renderer)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(circles_renderer main.cpp
        Circle.h
        CircleUtils.cpp
        CircleUtils.h
        CircleSoA.h)
target_link_libraries(circles_renderer OpenMP::OpenMP_CXX)
