cmake_minimum_required(VERSION 3.2)
project(Function_Table)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3")

set(SOURCE_FILES main.cpp Kappa.cpp )
add_executable(Function_Table ${SOURCE_FILES} Kappa.h)