add_library(2020_Color_lib Color/Color.h)
SET_TARGET_PROPERTIES(2020_Color_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(RecursiveParser_tinyexpr_lib RecursiveParser_tinyexpr/tinyexpr.h RecursiveParser_tinyexpr/tinyexpr.c)
SET_TARGET_PROPERTIES(RecursiveParser_tinyexpr_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(2020_Timer_lib Timer/Timer.h)
SET_TARGET_PROPERTIES(2020_Timer_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(2020_Day1_lib Day1/src/Day1.h Day1/src/Day1.cpp)
add_executable(2020_Day1 Day1/src/Day1.cpp)
target_link_libraries(2020_Day1 PUBLIC 2020_Day1_lib)

add_library(2020_Day2_lib Day2/src/Day2.h Day2/src/Day2.cpp)
add_executable(2020_Day2 Day2/src/Day2.cpp)
target_link_libraries(2020_Day2 PUBLIC 2020_Day2_lib)

add_library(2020_Day3_lib Day3/src/Day3.h Day3/src/Day3.cpp)
add_executable(2020_Day3 Day3/src/Day3.cpp)
target_include_directories(2020_Day3_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Color)
target_link_libraries(2020_Day3 PUBLIC 2020_Day3_lib 2020_Color_lib)

add_library(2020_Day4_lib Day4/src/Day4.h Day4/src/Day4.cpp)
add_executable(2020_Day4 Day4/src/Day4.cpp)
target_link_libraries(2020_Day4 PUBLIC 2020_Day4_lib)

add_library(2020_Day5_lib Day5/src/Day5.h Day5/src/Day5.cpp)
add_executable(2020_Day5 Day5/src/Day5.cpp)
target_link_libraries(2020_Day5 PUBLIC 2020_Day5_lib)

add_library(2020_Day6_lib Day6/src/Day6.h Day6/src/Day6.cpp)
add_executable(2020_Day6 Day6/src/Day6.cpp)
target_link_libraries(2020_Day6 PUBLIC 2020_Day6_lib)

add_library(2020_Day7_lib Day7/src/Day7.h Day7/src/Day7.cpp)
add_executable(2020_Day7 Day7/src/Day7.cpp)
target_link_libraries(2020_Day7 PUBLIC 2020_Day7_lib)

add_library(2020_Day8_lib Day8/src/Day8.h Day8/src/Day8.cpp)
add_executable(2020_Day8 Day8/src/Day8.cpp)
target_link_libraries(2020_Day8 PUBLIC 2020_Day8_lib)

add_library(2020_Day9_lib Day9/src/Day9.h Day9/src/Day9.cpp)
add_executable(2020_Day9 Day9/src/Day9.cpp)
target_link_libraries(2020_Day9 PUBLIC 2020_Day9_lib)

add_library(2020_Day10_lib Day10/src/Day10.h Day10/src/Day10.cpp)
add_executable(2020_Day10 Day10/src/Day10.cpp)
target_link_libraries(2020_Day10 PUBLIC 2020_Day10_lib)

add_library(2020_Day11_lib Day11/src/Day11.h Day11/src/Day11.cpp)
add_executable(2020_Day11 Day11/src/Day11.cpp)
target_include_directories(2020_Day11_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Color)
target_link_libraries(2020_Day11 PUBLIC 2020_Day11_lib 2020_Color_lib)

add_library(2020_Day12_lib Day12/src/Day12.h Day12/src/Day12.cpp)
add_executable(2020_Day12 Day12/src/Day12.cpp)
target_link_libraries(2020_Day12 PUBLIC 2020_Day12_lib)

add_library(2020_Day13_lib Day13/src/Day13.h Day13/src/Day13.cpp)
add_executable(2020_Day13 Day13/src/Day13.cpp)
target_link_libraries(2020_Day13 PUBLIC 2020_Day13_lib)

add_library(2020_Day14_lib Day14/src/Day14.h Day14/src/Day14.cpp)
add_executable(2020_Day14 Day14/src/Day14.cpp)
target_link_libraries(2020_Day14 PUBLIC 2020_Day14_lib)

add_library(2020_Day15_lib Day15/src/Day15.h Day15/src/Day15.cpp)
add_executable(2020_Day15 Day15/src/Day15.cpp)
target_include_directories(2020_Day15_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day15 PUBLIC 2020_Day15_lib 2020_Timer_lib)

add_library(2020_Day16_lib Day16/src/Day16.h Day16/src/Day16.cpp)
add_executable(2020_Day16 Day16/src/Day16.cpp)
target_include_directories(2020_Day16_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day16 PUBLIC 2020_Day16_lib 2020_Timer_lib)

add_library(2020_Day17_lib Day17/src/Day17.h Day17/src/Day17.cpp)
add_executable(2020_Day17 Day17/src/Day17.cpp)
target_include_directories(2020_Day17_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day17 PUBLIC 2020_Day17_lib 2020_Timer_lib)

add_library(2020_Day18_lib Day18/src/Day18.h Day18/src/Day18.cpp)
add_executable(2020_Day18 Day18/src/Day18.cpp)
target_include_directories(2020_Day18_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer ${CMAKE_CURRENT_LIST_DIR}/RecursiveParser_tinyexpr)
target_link_libraries(2020_Day18 PUBLIC 2020_Day18_lib 2020_Timer_lib RecursiveParser_tinyexpr_lib)

add_library(2020_Day19_lib Day19/src/Day19.h Day19/src/Day19.cpp)
add_executable(2020_Day19 Day19/src/Day19.cpp)
target_include_directories(2020_Day19_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day19 PUBLIC 2020_Day19_lib 2020_Timer_lib)

add_library(2020_Day20_lib Day20/src/Day20.h Day20/src/Day20.cpp)
add_executable(2020_Day20 Day20/src/Day20.cpp)
target_include_directories(2020_Day20_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day20 PUBLIC 2020_Day20_lib 2020_Timer_lib)

add_library(2020_Day20_Part2_lib Day20/src/Day20_Part2.h Day20/src/Day20_Part2.cpp)
add_executable(2020_Day20_Part2 Day20/src/Day20_Part2.cpp)
target_include_directories(2020_Day20_Part2_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day20_Part2 PUBLIC 2020_Day20_Part2_lib 2020_Timer_lib)

add_library(2020_Day21_lib Day21/src/Day21.h Day21/src/Day21.cpp)
add_executable(2020_Day21 Day21/src/Day21.cpp)
target_include_directories(2020_Day21_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day21 PUBLIC 2020_Day21_lib 2020_Timer_lib)

add_library(2020_Day22_lib Day22/src/Day22.h Day22/src/Day22.cpp)
add_executable(2020_Day22 Day22/src/Day22.cpp)
target_include_directories(2020_Day22_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day22 PUBLIC 2020_Day22_lib 2020_Timer_lib)

add_library(2020_Day23_lib Day23/src/Day23.h Day23/src/Day23.cpp)
add_executable(2020_Day23 Day23/src/Day23.cpp)
target_include_directories(2020_Day23_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day23 PUBLIC 2020_Day23_lib 2020_Timer_lib)

add_library(2020_Day23_Part2_lib Day23/src/Day23_Part2.h Day23/src/Day23_Part2.cpp)
add_executable(2020_Day23_Part2 Day23/src/Day23_Part2.cpp)
target_include_directories(2020_Day23_Part2_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day23_Part2 PUBLIC 2020_Day23_Part2_lib 2020_Timer_lib)

add_library(2020_Day24_lib Day24/src/Day24.h Day24/src/Day24.cpp)
add_executable(2020_Day24 Day24/src/Day24.cpp)
target_include_directories(2020_Day24_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer ${CMAKE_CURRENT_LIST_DIR}/Color)
target_link_libraries(2020_Day24 PUBLIC 2020_Day24_lib 2020_Timer_lib 2020_Color_lib)

add_library(2020_Day25_lib Day25/src/Day25.h Day25/src/Day25.cpp)
add_executable(2020_Day25 Day25/src/Day25.cpp)
target_include_directories(2020_Day25_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Timer)
target_link_libraries(2020_Day25 PUBLIC 2020_Day25_lib 2020_Timer_lib)