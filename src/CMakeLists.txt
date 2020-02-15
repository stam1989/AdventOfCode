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
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
