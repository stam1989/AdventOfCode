#include "Day13.h"

#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    Day13 intcode("../resources/Day13.txt");

    // ----- Part 1 ------
    intcode.Operation();
    
    intcode.PrintPanel();
    std::cout << "Block items: " << intcode.CountBlocks() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // ----- Part 2 ------
    intcode.GetOpcodes()[0] = 2; // insert coin

    intcode.Operation();

    return 0;
}