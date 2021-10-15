project(HW2)
cmake_minimum_required(VERSION 3.19)

set (SRC main.cpp mat.cpp matmul.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SRC})