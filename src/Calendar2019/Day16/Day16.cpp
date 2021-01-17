//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day16.h"

#include <iostream>
#include <exception>
#include <fstream>

std::vector<int16_t> FlawedFrequencyTransmission::ReadFile(const char* filename)
{
    std::cout << "ReadFile starts\n";

    std::ifstream input(filename);
    std::string token;
    std::vector<int16_t> fft;
    if (input.is_open())
    {
        while (std::getline(input, token, ','))
        {
            for (const char& c : token)
            {
                fft.emplace_back(static_cast<int16_t>(c) - 48); // convert from ascii to int since numbers start from 48
                // fft.emplace_back(c - '0');   // convert from ascii to int(since '0' has ascii code 48)

            }
        }
        input.close();
    }
    else
    {
        std::string exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
    return fft;
}


void FlawedFrequencyTransmission::FFT(std::vector<int16_t>& fft, std::vector<int16_t> pattern)
{
    for (int iterationIndex = 0; iterationIndex < fft.size(); iterationIndex++)
    {
       int patternIndex = 0;
       int repeat = iterationIndex;
       int val = 0;

        for (int inLstIndex = 0; inLstIndex < fft.size(); inLstIndex++)
        {
            repeat--;
            if(repeat < 0)
            {
               repeat = iterationIndex;
                patternIndex = (patternIndex + 1) % pattern.size();
            }
            val += fft[inLstIndex] * pattern[patternIndex];
        }
        fft[iterationIndex] = abs(val) % 10;
    }
}
