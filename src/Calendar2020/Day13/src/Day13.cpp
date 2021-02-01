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
    // for(int i = 1; i < biwd.size(); i++)
    // {
    //     if (biwd[i].first - biwd[i - 1].first != biwd[i].second - biwd[i - 1].second)
    //     {
    //         return false;
    //     }
    // }

    // equivalent of the above, but more clear
    for(const auto& id : biwd)
    {
        if((biwd[0].first + id.second) % id.first != 0)
            return false; 
    }

    return true;
}


long Day13::GetResultWithOffset()
{
    auto v_biwd(m_schedule.busIDs_withDelay);
    while(!IsValid(v_biwd))
    {
        v_biwd[0].first += m_schedule.busIDs_withDelay[0].first;
        if(v_biwd[0].first % m_schedule.busIDs_withDelay[0].first != 0) continue;
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


int64_t Day13::ChineseRemainderTheorem()
{
    auto v_biwd(m_schedule.busIDs_withDelay);
    // int64_t div_muls = 1;
    // for(const auto& id : v_biwd)
    // {
    //     div_muls *= id.second;
    // }

    // calculate the divisors' multiple
    auto div_muls = std::accumulate(v_biwd.begin(), v_biwd.end(), 1, [](const auto a, const auto& id) { return a * id.first; });

    std::vector<int64_t> v_divMul, v_congruents;
    for(const auto& id : v_biwd)
    {
        // calculate each divisor's multiple
        auto dm = div_muls / id.first;
        v_divMul.emplace_back(dm);

        //calculate divMul's congrunent
        auto d = dm % id.first;
        int i = 1;
        while(true)
        {
            if((i * d) % id.first == 1)
            {
                v_congruents.emplace_back(i);
                break;
            }
            i++;
        }
    }

    // calculate the sum of the multiples between: divisors, congruents and divisor multiples
    int64_t res = 0;
    for(int i = 0; i < v_divMul.size(); i++)
    {
        res += v_biwd[i].second * v_divMul[i] * v_congruents[i];
    }

    return res;
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
            if ((x + biwd[j].second) % biwd[j].first != 0) 
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

    // d.PrintWithDelay();

    // Part2

    //
    // {
        // Timer t1;
        // std::cout << "x is " << d.findMinX() << "\n";
    // }

    // Same as above, but much more efficient
    {
        Timer t2;
        std::cout << "Part2 result is: " << d.ChineseRemainderTheorem() << "!\n";
    }
    return 0;
}