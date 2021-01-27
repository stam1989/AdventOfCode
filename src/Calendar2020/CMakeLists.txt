add_library(2020_Color_lib Color/Color.h)
SET_TARGET_PROPERTIES(2020_Color_lib PROPERTIES LINKER_LANGUAGE CXX)

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