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
        std::vector<std::pair<uint64_t, int64_t>> busIDs_withDelay;
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


int64_t Day13::ChineseRemainderTheorem()
{
    auto v_biwd(m_schedule.busIDs_withDelay);
 
    // calculate the divisors' multiple
    std::int64_t div_muls = 1;
    for (auto& id : v_biwd)  div_muls *= id.first;

    std::vector<int64_t> v_divMul, v_congruents;
    for(const auto& id : v_biwd)
    {
        // calculate each divisor's multiple
        auto dm = div_muls / id.first;
        v_divMul.emplace_back(dm);

        //calculate divMul's congrunent
        auto d = dm % id.first;
        int64_t i = 1;
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
    for(int64_t i = 0; i < v_divMul.size(); i++)
    {
        res += (v_biwd[i].first - v_biwd[i].second) * v_divMul[i] * v_congruents[i];
    }

    return res % div_muls;
}


int main()
{
    Day13 d;
    // d.Print();

    // std::cout << "The ID of the earliest bus I can take to the airport multiplied by the number of minutes I'll need to wait for is: "
    //           << d.GetResult() << "!\n";

    // d.PrintWithDelay();

    // Uses original Chinese Remainder Theorem but is not exactly what we are looking for
    {
        Timer t2;
        std::cout << "Part2 result is: " << d.ChineseRemainderTheorem() << "!\n";
    }

    return 0;
}