//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY14_H
#define DAY14_H

#include <vector>
#include <map>
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


class Day14
{
public:
    Day14() { ReadFile(); }

    struct AddressData {
        int64_t pos, value;
    };

    struct Program {
        Program() {}
        Program(std::string m, std::vector<AddressData> a) : mask(m), address(a) {}
        std::string mask;
        std::vector<AddressData> address;
    };

    void PrintInput();
    void PrintValues();
    void FillAddresses();
    int64_t GetSum();
    void DecodeVersion2();
    void ApplyMaskToAddressAndStore(std::string value, const AddressData& ad);

private:
    std::vector<Program> m_programInput;
    std::map<int64_t, int64_t> m_values;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day14/resources/Day14.txt";

    void ReadFile();
};


#endif