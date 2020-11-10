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
    ASCII intcode("../resources/Day17.txt");
    
    intcode.Operation();
    intcode.PrintOpcodes();

    std::cout << "View size: " << intcode.GetView().size();
    intcode.PrintView();


    return 0;
}