//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day8.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Day8::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            std::istringstream ss(s_input);
            std::string opcode;
            int step;
            ss >> opcode;
            ss >> step;
            m_opcodes.emplace_back(opcode, step);
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

void Day8::PrintOpcodes()
{
    for (const auto& op : m_opcodes)
    {
        std::cout << op.first << ": " << op.second << "\n";
    }
}


int main()
{
    Day8 d;

    d.PrintOpcodes();

    return 0;
}