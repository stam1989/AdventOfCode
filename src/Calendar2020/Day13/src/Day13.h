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


using SeatLayout = std::vector<std::vector<char>>;

class Day13
{
public:
    Day13() { ReadFile(); }

    void Print();
    void PrintWithDelay();
    int64_t GetResult();
    int64_t ChineseRemainderTheorem();

    struct Schedule
    {
        int64_t timestamp;
        std::vector<int64_t> busIDs;               //Part 1
        std::vector<std::pair<uint64_t, int64_t>> busIDs_withDelay;     //Part 2
    };

private:
    Schedule m_schedule;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day13/resources/Day13.txt";

    void ReadFile();
    inline int64_t GetMinutesToWait(const int64_t id)
    {
        return ((((m_schedule.timestamp / id) + 1) *  id) - m_schedule.timestamp);
    }
};


#endif