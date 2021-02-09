//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day18.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>


void Day18::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, s_input)) {
            
        }
        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


int main() {
    Day18 d;

    int8_t sixCycleBootProcess = 6;
    {
        Timer t;
        
    }

    {
        Timer t;

    }
    
    return 0;
}