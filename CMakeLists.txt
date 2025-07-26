cmake_minimum_required(VERSION 3.10)
project(circuit-ruiter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog
	src/main.cpp
)

target_include_directories(prog PRIVATE include src)


