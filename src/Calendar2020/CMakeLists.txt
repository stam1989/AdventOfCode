add_library(2020_Color_lib Color/Color.h)
SET_TARGET_PROPERTIES(2020_Color_lib PROPERTIES LINKER_LANGUAGE CXX)

add_library(2020_Day1_lib Day1/src/Day1.h Day1/src/Day1.cpp)
add_executable(2020_Day1 Day1/src/Day1.cpp)
target_link_libraries(2020_Day1 PUBLIC 2020_Day1_lib)
# target_include_directories(2020_Day1_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Color)

add_library(2020_Day2_lib Day2/src/Day2.h Day2/src/Day2.cpp)
add_executable(2020_Day2 Day2/src/Day2.cpp)
target_link_libraries(2020_Day2 PUBLIC 2020_Day2_lib)

add_library(2020_Day3_lib Day3/src/Day3.h Day3/src/Day3.cpp)
add_executable(2020_Day3 Day3/src/Day3.cpp)
target_include_directories(2020_Day3_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Color)
target_link_libraries(2020_Day3 PUBLIC 2020_Day3_lib 2020_Color_lib)