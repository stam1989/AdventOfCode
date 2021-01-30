//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY13_H
#define DAY13_H

#include <vector>
#include <cstdlib>

using SeatLayout = std::vector<std::vector<char>>;

class Day13
{
public:
    Day13() { ReadFile(); }

    void Print();
    void PrintWithDelay();
    long GetResult();
    bool IsValid(const std::vector<std::pair<long, int>>& biwd);
    long GetResultWithOffset();
    int64_t findMinX();

    struct Schedule
    {
        long timestamp;
        std::vector<long> busIDs;               //Part 1
        std::vector<std::pair<long, int>> busIDs_withDelay;     //Part 2
    };

private:
    Schedule m_schedule;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day13/resources/Day13.txt";

    void ReadFile();
    inline long GetMinutesToWait(const long id)
    {
        return ((((m_schedule.timestamp / id) + 1) *  id) - m_schedule.timestamp);
    }
};


#endif