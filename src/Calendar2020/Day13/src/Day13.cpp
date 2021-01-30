//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day13.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>


void Day13::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open())
    {
        std::getline(inputFile, s_input);
        m_schedule.timestamp = stol(s_input);
        std::vector<long> busIDs;
        std::vector<std::pair<long, int>> busIDs_withDelay;
        long delay = 0;
        while (std::getline(inputFile, s_input))
        {
            std::istringstream ss(s_input);
            std::string id;
            char comma_del(',');
            while(std::getline(ss, id, comma_del))
            {
                if(id != "x")
                {
                    busIDs.emplace_back(stol(id));
                    busIDs_withDelay.emplace_back(std::make_pair(stol(id), delay));
                }
                delay++;
            }
        }
        m_schedule.busIDs = busIDs;
        m_schedule.busIDs_withDelay = busIDs_withDelay;
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day13::Print()
{
    std::cout << m_schedule.timestamp << "\n";
    for(const long id : m_schedule.busIDs)
    {
        std::cout << id << ", ";
    }
    std::cout << "\n";
}


void Day13::PrintWithDelay()
{
    for(const auto& id : m_schedule.busIDs_withDelay)
    {
        std::cout << id.first << "(mod" << id.second << "), ";
    }
    std::cout << "\n";
}


long Day13::GetResult()
{
    long earliestBusId = m_schedule.busIDs[0];
    long minutesToWait = GetMinutesToWait(m_schedule.busIDs[0]);
    for(const long id : m_schedule.busIDs)
    {
        long temp_minutes = GetMinutesToWait(id);
        if(temp_minutes < minutesToWait)
        {
            minutesToWait = temp_minutes;
            earliestBusId = id;
        }
    }

    return minutesToWait * earliestBusId;
}


bool Day13::IsValid(const std::vector<std::pair<long, int>>& biwd)
{
    for(int i = 1; i < biwd.size(); i++)
    {
        if (biwd[i].first - biwd[i - 1].first != biwd[i].second - biwd[i - 1].second)
        {
            return false;
        }
    }

    return true;
}


long Day13::GetResultWithOffset()
{
    auto v_biwd(m_schedule.busIDs_withDelay);
    while(!IsValid(v_biwd))
    {
        v_biwd[0].first += m_schedule.busIDs_withDelay[0].first;
        for(int i = 1; i < v_biwd.size(); i++)
        {
            if(v_biwd[i].first < v_biwd[i - 1].first)
            {
                v_biwd[i].first = ((v_biwd[i - 1].first / m_schedule.busIDs_withDelay[i].first) + 1) * m_schedule.busIDs_withDelay[i].first;
            }
        }
    }

    return v_biwd[0].first;
}

// chinese remainder theorem
int64_t Day13::findMinX() 
{ 
    std::vector<std::pair<long, int>> biwd(m_schedule.busIDs_withDelay);
    long x = 1; // Initialize result 
  
    // As per the Chinese remainder theorem, 
    // this loop will always break. 
    while (true) 
    { 
        // Check if remainder of x % num[j] is  
        // rem[j] or not (for all j from 0 to k-1) 
        int j; 
        for (j=0; j<biwd.size(); j++ ) 
            if (x%biwd[j].first != biwd[j].second) 
               break; 
  
        // If all remainders matched, we found x 
        if (j == biwd.size()) 
            return x; 
  
        // Else try next numner 
        x++; 
    } 
  
    return x; 
} 



int main()
{
    Day13 d;
    // d.Print();

    // std::cout << "The ID of the earliest bus I can take to the airport multiplied by the number of minutes I'll need to wait for is: "
    //           << d.GetResult() << "!\n";

    d.PrintWithDelay();
    std::cout << "x is " << d.findMinX() << "\n";
    std::cout << "Part2 result is: " << d.GetResultWithOffset() << "!\n";
   
    return 0;
}