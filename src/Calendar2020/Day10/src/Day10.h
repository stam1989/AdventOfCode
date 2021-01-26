//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY10_H
#define DAY10_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <unordered_map>

class Day10
{
public:
    Day10() { ReadFile(); }

    inline void PrintAdapters()
    {
        for (const auto adapter : m_adapters)
        {
            std::cout << adapter << "\n";
        }
    }


    int32_t GetDifferences();
    int64_t GetNumWays(int16_t pos);

private:
    std::vector<int16_t> m_adapters;
    std::unordered_map<int16_t, int64_t> m_checked;

    static constexpr char const *FILENAME = "../src/Calendar2020/Day10/resources/Day10.txt";
    static constexpr int8_t MAX_JOLT_DIFF = 3;

    void ReadFile();
};


#endif