//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day14.h"

#include <fstream>



void Day14::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open())
    {
        std::getline(inputFile, s_input);
        while (std::getline(inputFile, s_input))
        {
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day14::Print()
{

    std::cout << "\n";
}


int main()
{
    Day14 d;
    // d.Print();

    return 0;
}