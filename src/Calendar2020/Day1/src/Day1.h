//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY1_H
#define DAY1_H

#include <vector>
#include <cstdint>
#include <optional>
#include <tuple>
#include <iostream>

class Day1
{
public:
    Day1() { ReadFile(); }
    void ReadFile();


    inline void PrintInputs() { for (auto entry : v_entries) std::cout << entry << "\n"; }

    template <typename T>
    std::tuple<uint32_t, uint32_t> FindTwoNumbers(uint32_t expected_sum, T&& entries)
    {
        while (!entries.empty())
        {
            auto it_secondEntry = std::find_if(entries.begin() + 1, entries.end(), [entries, expected_sum](const int32_t entry) { return entries[0] + entry == expected_sum; }); 
            
            if (it_secondEntry != entries.end())
            {
                return {entries[0], (*it_secondEntry)};   
            }

            entries.erase(std::remove(entries.begin(), entries.end(), entries.front()));
        }
    }


    std::tuple<uint32_t, uint32_t, uint32_t> FindThreeNumbers(uint32_t expected_sum);

    inline std::vector<int32_t> GetEntries() { return v_entries; }


private:
    std::vector<int32_t> v_entries;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day1/resources/Day1.txt";
};



#endif