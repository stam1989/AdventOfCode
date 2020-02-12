cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
project(AdventOfCode VERSION 1.0.0)

add_subdirectory(src)
