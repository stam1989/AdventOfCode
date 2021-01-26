//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day10.h"

#include <fstream>


void Day10::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            m_adapters.emplace_back(stol(s_input));
        }
        m_adapters.emplace_back(0);    // The charging outlet has an effective rating of 0 jolts
        // device's built-in joltage adapter is rated 3 higher than the highest-rated adapter.
        m_adapters.emplace_back(*std::max_element(m_adapters.begin(), m_adapters.end()) + 3);
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


int32_t Day10::GetDifferences()
{
    std::sort(m_adapters.begin(), m_adapters.end());
    int32_t oneJoltCounter = 0, threeJoltsCounter = 0;
    for(int i = 1; i < m_adapters.size(); i++)
    {
        if(m_adapters[i] - m_adapters[i - 1] == 1)
        {
            oneJoltCounter++;
        }
        else if(m_adapters[i] - m_adapters[i - 1] == 3)
        {
            threeJoltsCounter++;
        }
    }
    return oneJoltCounter * threeJoltsCounter;
}

int64_t Day10::GetNumWays(int16_t pos)
{
    if(pos == m_adapters.size() - 1)
    {
        return 1;
    }

    if(m_checked.find(pos) != m_checked.end())
    {
        return m_checked[pos];
    }

    int64_t total = 0;

    for(int16_t i = pos + 1; i < m_adapters.size(); i++)
    {
        if(m_adapters[i] - m_adapters[pos] <= 3)
        {
            total += GetNumWays(i);
        }
    }

    m_checked.insert({pos, total});

    return total;
}


int main()
{
    Day10 d;
    // d.PrintAdapters();

    std::cout << "The number of 1-jolt differences multiplied by the number of 3-jolt differences is: " << d.GetDifferences() << "!\n";
    std::cout << "The total number of distinct ways you can arrange the adapters to connect the charging outlet to my device is: " 
              << d.GetNumWays(0) << "!\n";
    return 0;
}