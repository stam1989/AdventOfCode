//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY11_H
#define DAY11_H

#include <vector>

using SeatLayout = std::vector<std::vector<char>>;

class Day11
{
public:
    Day11() { ReadFile(); }

    void PrintSeatLayout();
    bool ApplyRules();
    bool ApplyRulesSecond();
    int8_t GetNumOfOccupiedAdjacent(const SeatLayout& seats, const int32_t col, const int32_t row);
    int8_t GetNumOfOccupiedAll(const SeatLayout& seats, const int32_t col, const int32_t row);
    int32_t CountOccupied();

private:
    SeatLayout m_seats;
    int32_t m_col, m_row;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day11/resources/Day11.txt";

    void ReadFile();
};


#endif