#include "Day15.h"

#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        const char* filename("../resources/Day15.txt");
        Maze intcode_program(filename);

        // DFS
        intcode_program.Operation();
        intcode_program.PrintPanel();

        // Calculate Shortest Path to oxygen (Part 1)
        int32_t curDistance = 0;
        int32_t minDistance = INT32_MAX;
        std::pair<int, int> dest = intcode_program.GetOxygenPosition();
        int cur_X = intcode_program.GetStartPoint().first;
        int cur_Y = intcode_program.GetStartPoint().second;
        intcode_program.FindShortestPath(cur_X, cur_Y, dest, curDistance, minDistance);
        
        std::cout << "The shortest path to Oxygen is: " << minDistance << " steps!!\n";

        // Calculate time to fill whole maze with oxygen (Part 2)
        uint16_t timeElapsed = 0;
        intcode_program.CaluclateTimeToFillOxygen(timeElapsed);

        intcode_program.PrintPanel();
        std::cout << "It takes " << timeElapsed << " minutes to fill with oxygen...\n";
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