cmake_minimum_required(VERSION 3.12)

project(AdventOfCode VERSION 1.0.0)

set(CMAKE_INSTALL_PREFIX "~/workspace/AdventOfCode/build/install")
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(src)
