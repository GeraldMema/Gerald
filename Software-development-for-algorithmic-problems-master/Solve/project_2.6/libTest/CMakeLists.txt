cmake_minimum_required(VERSION 3.2)
project(LibTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -lcppunit -llapacke -g3")

file(GLOB TestLibMatrix
    "*.h"
    "*.cpp"
)

file(GLOB TestLibCurves
    "*.h"
    "*.cpp"
)

file(GLOB TestLibSolver
    "*.h"
    "*.cpp"
)

add_executable(Function_Table ${SOURCE_FILES} ${TestLibMatrix} ${TestLibCurves} ${TestLibSolver} )