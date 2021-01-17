//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY16_H
#define DAY16_H

#include <array>
#include <vector>
#include <cstdint>
#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;

        std::cout << "Duration: " << duration << "us (" << ms << "ms)\n";
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};


namespace FlawedFrequencyTransmission
{

    // inline void* operator new(size_t s)
    // {
    //     std::cout << "Allocating " << s << std::endl;
    //     return malloc(s);
    // }

    /// brief reads from a file and stores every element in a vector
    /// returns the input list
    std::vector<int16_t> ReadFile(const char* filename);

    void FFT(std::vector<int16_t>& fft, std::vector<int16_t> pattern);
}
#endif