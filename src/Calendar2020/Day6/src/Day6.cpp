//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day6.h"

#include <fstream>
#include <iostream>


void Day6::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        std::set<char> answers;
        while (std::getline(inputFile, s_input))
        {
            if (s_input.empty())
            {
                m_groups.emplace_back(answers);
                answers.clear();
                continue;
            }
            std::copy(s_input.begin(), s_input.end(), std::inserter<std::set<char> >(answers, answers.begin()));
        }
        m_groups.emplace_back(answers);
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day6::ReadFilePart2()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        std::set<char> answers;
        m_groups.clear();
        int line = 0;
        while (std::getline(inputFile, s_input))
        {
            if (s_input.empty())
            {
                if (!answers.empty())
                {
                    m_groups.emplace_back(answers);
                }
                answers.clear();
                line = 0;
                continue;
            }

            if(line == 0)
            {
                std::copy(s_input.begin(), s_input.end(), std::inserter<std::set<char> >(answers, answers.begin()));
                line++;
            }
            else
            {
                line++;
                std::set<char> temp_answers, temp_answers2(answers);
                answers.clear();
                std::copy(s_input.begin(), s_input.end(), std::inserter<std::set<char> >(temp_answers, temp_answers.begin()));

                std::set_intersection(temp_answers2.begin(), temp_answers2.end(),
                                      temp_answers.begin(), temp_answers.end(), 
                                      std::inserter<std::set<char> >(answers, answers.begin()));
            }
            

        }
        m_groups.emplace_back(answers);
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day6::PrintGroups()
{
    for (const auto& answers : m_groups)
    {
        for (const char c : answers)
        {
            std::cout << c;
        }
        std::cout << "\n";
    }
}


int32_t Day6::SumCounts()
{
    int32_t sum = 0;
    for (const auto& answers : m_groups)
    {
        sum += answers.size();
    }

    return sum;
}


int main()
{
    Day6 d;
    d.ReadFile();
    // d.PrintGroups();
    std::cout << "The sum of the counts is: " << d.SumCounts() << "\n";


    d.ReadFilePart2();
    // d.PrintGroups();
    std::cout << "The sum of the counts with second method is: " << d.SumCounts() << "\n";

    return 0;
}