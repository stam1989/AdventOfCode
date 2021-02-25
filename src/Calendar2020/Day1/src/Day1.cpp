//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include "Day1.h"

#include <fstream>
#include <algorithm>


void Day1::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream input(FILENAME);
	std::string entry;
    if (input.is_open())
    {
        while (std::getline(input, entry))
        {
            if (!entry.empty()) {
                v_entries.emplace_back(std::stol(entry));
            }
        }
        input.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


std::tuple<uint32_t, uint32_t, uint32_t> Day1::FindThreeNumbers(uint32_t expected_sum)
{
    while(!v_entries.empty())
    {
        bool found = false;
        for(int i = 1;  i < v_entries.size(); i++)
        {
            auto it_secondEntry = std::find_if(v_entries.begin(), v_entries.end(), 
                                            [this, i, expected_sum](const int32_t entry)
                                            {
                                                if (entry == v_entries[0] || entry == v_entries[i])
                                                    return false;
                                                else return v_entries[0] + v_entries[i] + entry == expected_sum; 
                                            }
                                        ); 
                                        
            if (it_secondEntry != v_entries.end())
            {
                return { v_entries[0], v_entries[i], (*it_secondEntry) };   
            }
        }

        v_entries.erase(std::remove(v_entries.begin(), v_entries.end(), v_entries.front()));
    }
}


int main()
{
    Day1 d;
    uint32_t expected_sum = 2020;
    auto v = d.GetEntries();

    auto[entry1, entry2] = d.FindTwoNumbers<>(expected_sum, v);
    std::cout << "The two entries that sum to 2020 are: " << entry1 << ", " << entry2 << ", with product: " << entry1 * entry2 << "\n";

    auto[num1, num2, num3] = d.FindThreeNumbers(expected_sum);
    std::cout << "The three entries that sum to 2020 are: " << num1 << ", " << num2 << ", " << num3 << ", with product: " << num1 * num2 * num3 << "\n";

    return 0;
}