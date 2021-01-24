//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day5.h"

#include <iostream>
#include <fstream>

void Day5::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            if (!s_input.empty())
            {
                m_seats.emplace_back(s_input);
            }
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day5::Print()
{
    for (const auto& seat : m_seats)
    {
        std::cout << seat << "\n";
    }
}


std::vector<int64_t> Day5::GetSeatIDs()
{
    std::vector<int64_t> seatIDs;
    for (const std::string& seat : m_seats)
    {
        std::string s_row;
        for (int i = 0; i < ROW_LENGTH; i++)
        {
            if (seat[i] == 'F')
            {
                s_row.append("0");
            }
            else if (seat[i] == 'B')
            {
                s_row.append("1");
            }
        }
        s_row.append("\0");

        std::string s_col;
        for (int i = ROW_LENGTH; i < seat.size(); i++)
        {
            if (seat[i] == 'L')
            {
                s_col.append("0");
            }
            else if (seat[i] == 'R')
            {
                s_col.append("1");
            }
        }

        seatIDs.emplace_back((stol(s_row, nullptr, 2) * 8) + stol(s_col, nullptr, 2));
    }

    return seatIDs;
}


int64_t Day5::FindMySeat(std::vector<int64_t> seatIDs)
{
    for(int16_t i = 0; i < seatIDs.size() - 1; i++)
    {
        if (seatIDs[i] + 1 != seatIDs[i + 1])
        {
            return seatIDs[i] + 1;
        }
    }
}




int main()
{

    Day5 d;

    std::vector<int64_t> seatIDs = d.GetSeatIDs();
    std::sort(seatIDs.begin(), seatIDs.end());
    std::cout << "The highest seat ID on a boarding pass is: " << seatIDs.back() << "\n";

    std::cout << "My seat is: " << d.FindMySeat(seatIDs) << "\n";

    return 0;
}