//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day17.h"
#include "Intcode.h"

#include <iostream>

int main()
{
    ASCII intcode("../src/Day17/resources/Day17.txt");

    // Part 1
    intcode.Operation();
    intcode.PrintViews();

    int64_t sum = intcode.LocateIntersections();
    intcode.PrintViews();
    std::cout << "The sum of the alignment parameters for the scaffold intersections is " << sum << "!!\n";


    // Part 2
    ASCII intcode_Part2("../src/Day17/resources/Day17.txt");
    intcode_Part2.GetOpcodes()[0] = 2;    // Force the vacuum robot to wake up
    // intcode.SetRobotsPosition();
    intcode_Part2.Operation();
    intcode_Part2.PrintViews();

    return 0;
}
