#include "Day15_Part1.h"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        const char* filename("../resources/Day15.txt");
        Maze intcode_program(filename);

        intcode_program.Operation();

        int32_t curDistance = 0;
        int32_t minDistance = INT32_MAX;
        std::pair<int, int> dest = intcode_program.GetDestination();
        int cur_X = intcode_program.GetStartPoint().first;
        int cur_Y = intcode_program.GetStartPoint().second;
        intcode_program.FindShortestPath(cur_X, cur_Y, dest, curDistance, minDistance);
        
        std::cout << "The shortest path to Oxygen is: " << minDistance << " !!\n";

    }
    catch (std::string& exception_string)
    {
        std::cout << exception_string << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}