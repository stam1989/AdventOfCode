install(FILES 
		"${PROJECT_BINARY_DIR}/../src/Day1_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day1_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day2_Part1.cpp"
		#"${PROJECT_BINARY_DIR}/../src/Day2_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day3_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day3_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day4_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day5.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day5_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day6.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day6_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day7_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day7_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day8_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day8_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day9_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day10_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day11_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day11_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day12_Part1.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day12_Part2.cpp"
		"${PROJECT_BINARY_DIR}/../src/Day13_Part1.cpp"
  DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src
  )

  add_library(ODC STATIC
    #>>> include/*.h
    Intcode.h
    #>>> src/*.cpp
    Intcode.cpp
    Day13_Part1.cpp
    )



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

install(TARGETS Day1_Part1
				Day1_Part2
				Day2_Part1
				Day3_Part1
				Day3_Part2
				Day4_Part1
				Day5
				Day5_Part2
				Day6
				Day6_Part2
				Day7_Part1
				Day7_Part2
				Day8_Part1
				Day8_Part2
				Day9_Part1
				Day10_Part1
				Day11_Part1
				Day11_Part2
				Day12_Part1
				Day12_Part2
				Day13_Part1
		RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/install/bin)

		
#set_target_properties(Day1_Part1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
