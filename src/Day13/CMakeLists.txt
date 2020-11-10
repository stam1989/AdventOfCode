add_library(Day13_lib
    include/Day13.h
    src/Day13.cpp)

add_library(Day13_main src/main.cpp)

target_include_directories(Day13_lib PUBLIC include src)
target_include_directories(Day13_main PUBLIC include src)

