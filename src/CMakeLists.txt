add_executable(Day1_Part1 Day1_Part1.cpp)
add_executable(Day1_Part2 Day1_Part2.cpp)
add_executable(Day2_Part1 Day2_Part1.cpp)
#add_executable(Day2_Part2 Day2_Part2.cpp)
add_executable(Day3_Part1 Day3_Part1.cpp)
add_executable(Day3_Part2 Day3_Part2.cpp)
add_executable(Day4_Part1 Day4_Part1.cpp)
add_executable(Day5 Day5.cpp)
add_executable(Day5_Part2 Day5_Part2.cpp)
add_executable(Day6 Day6.cpp)
add_executable(Day6_Part2 Day6_Part2.cpp)
add_executable(Day7_Part1 Day7_Part1.cpp)
add_executable(Day7_Part2 Day7_Part2.cpp)
add_executable(Day8_Part1 Day8_Part1.cpp)
add_executable(Day8_Part2 Day8_Part2.cpp)
add_executable(Day9_Part1 Day9_Part1.cpp)
add_executable(Day10_Part1 Day10_Part1.cpp)
add_executable(Day11_Part1 Day11_Part1.cpp)
add_executable(Day11_Part2 Day11_Part2.cpp)
add_executable(Day12_Part1 Day12_Part1.cpp)
add_executable(Day12_Part2 Day12_Part2.cpp)
add_executable(Day13_Part1 Day13_Part1.cpp)
add_executable(Day13_Part2 Day13_Part2.cpp)
add_executable(Day14_Part1 Day14_Part1.cpp)
add_executable(Day14_Part2 Day14_Part2.cpp)


add_subdirectory(Intcode)

add_library(Day15_lib
    Day15/Day15.h
    Day15/Day15.cpp)

add_library(Day15_main
    Day15/main.cpp)

add_executable(Day15 Day15/main.cpp)
target_link_libraries(Day15 PUBLIC IntcodeLib Day15_lib)
target_include_directories(Day15_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Intcode)
target_include_directories(Day15_main PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Intcode)

add_library(Day16_lib Day16/Day16.h Day16/Day16.cpp)
add_executable(Day16 Day16/main.cpp)
target_link_libraries(Day16 PUBLIC Day16_lib)