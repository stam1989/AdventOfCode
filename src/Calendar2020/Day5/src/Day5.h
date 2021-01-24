//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY5_H
#define DAY5_H


#include <vector>
#include <string>
#include <cstdint>

using Seats = std::vector<std::string>;

class Day5
{
public:
    Day5() { ReadFile(); }

    enum class Section  // rows
    {
        F = 0,
        B
    };

    enum class SeatColumn   // columns
    {
        L = 0,
        R
    };

    void ReadFile();
    void Print();
    std::vector<int64_t> GetSeatIDs();
    int64_t FindMySeat(std::vector<int64_t> seatIDs);
    
private:
    Seats m_seats;

    static constexpr char const *FILENAME = "../src/Calendar2020/Day5/resources/Day5.txt";
    static constexpr int8_t ROW_LENGTH = 7;
};


#endif