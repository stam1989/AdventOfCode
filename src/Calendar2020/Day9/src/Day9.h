//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY9_H
#define DAY9_H

#include <vector>
#include <cstdlib>
#include <iostream>

class Day9
{
public:
    Day9() { ReadFile(); }

    inline void PrintData() { for (const auto d : m_data) std::cout << d << "\n"; }
    int64_t FindFirstInvalid(int64_t preamble);
    int64_t FindEncryptionWeakness(int64_t firstInvalid);

private:
    std::vector<int64_t> m_data;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day9/resources/Day9.txt";

    void ReadFile();
};

#endif
