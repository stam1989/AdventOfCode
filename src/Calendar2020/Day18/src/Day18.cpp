//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day18.h"
#include "Timer.h"
#include "tinyexpr.h"

#include <fstream>
#include <string>
#include <sstream>


void Day18::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        m_sum = 0;
        while (std::getline(inputFile, s_input)) {
            m_sum += te_interp(s_input.c_str(), 0);
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
        std::cout << "The sum of the resulting values is " << d.GetSum() << "!\n";
    }

    {
        Timer t;

    }
    
    return 0;
}