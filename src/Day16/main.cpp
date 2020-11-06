//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day16.h"

#include <iostream>

static constexpr int16_t PHASES = 100;

int main()
{
    std::vector<int16_t> temp_fft = FlawedFrequencyTransmission::ReadFile("../resources/Day16.txt");
    std::vector<int16_t> fft(temp_fft);

    {
        Timer t;


    /// PART 1

        std::vector<int16_t> pattern({0, 1, 0, -1});

        for (int16_t phase = 0; phase < PHASES; phase++)
        {
            FlawedFrequencyTransmission::FFT(fft, pattern);
        }

        std::cout << "\nPART 1: The first eight digits of the final output list after " << PHASES << " phases: ";
        for (int i = 0; i < 8; i++)
        {
            std::cout <<  fft[i] ;
        }
        std::cout << " !!\n";
    }


/// PART 2


    {
        Timer t;
        int64_t offset = 0;

        // take offset (first seven)
        for (int i = 0; i < 7; i++)
        {
            offset = (offset * 10) + temp_fft[i];
        }

        fft.clear();
        for(size_t i = 0; i < 10000; i++)
        {
            fft.insert(std::end(fft), std::begin(temp_fft), std::end(temp_fft));
        }

        for(int i = 0; i < 100; i++)
        {
            int val = 0;
            for(int j = fft.size() - 1; j >= offset; j--)
            {
                val += fft[j];
                fft[j] = abs(val) % 10;
            }
        }

        std::cout << "\n PART 2: The eight-digit message embedded in the final output list is ";
        for (int i = offset; i < offset + 8; i++)
        {
            std::cout << fft[i];
        }
        std::cout << " !!\n";
    }

    return 0;
}



/*
int main()
{
    Timer t;
    std::vector<int16_t> fft = FlawedFrequencyTransmission::ReadFile("../resources/Day16.txt");
    std::array<int16_t, 650> input;
    std::copy_n(fft.begin(), fft.size(), input.begin());


    std::array<int16_t, 4> pattern({0, 1, 0, -1});

    for (int16_t phase = 0; phase < PHASES; phase++)
    {
        FlawedFrequencyTransmission::FFT(input, pattern);
    }

    std::cout << "The first eight digits of the final output list after " << PHASES << " phases: ";
    for (int i = 0; i < 8; i++)
    {
        std::cout <<  input[i] ;
    }
    std::cout << "\n";

    

    return 0;
}

*/