//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day3.h"
#include "Color.h"

#include <iostream>
#include <fstream>
#include <algorithm>

void Day3::ReadFile()
{
	std::ifstream input(FILENAME);
	std::string line;
	try
	{
		if (input.is_open())
		{
			while (std::getline(input, line))
			{
                std::vector<char> p;
				for(auto& ch : line)
				{
                    if(ch == '.' || ch == '#')
                    {
                        p.emplace_back(ch);
                    }
				}
                m_column = p.size();
                m_pattern.emplace_back(p);
			}
            m_row = m_pattern.size();
			input.close();
		}
		else
		{
			std::string exception_string =  "Could not open input file";
			throw std::runtime_error(exception_string);
		}
	}
	catch(std::string& exception_string)
	{
		std::cout << exception_string << std::endl;
	}
}


void Day3::PrintPattern()
{
    for (const auto& pattern : m_pattern)
    {
        for (const auto& p : pattern)
        {
            if(p == '.')
            {
                std::cout << BLUE << p << RESET;
            }
            else if(p == '#')
            {
                std::cout << YELLOW << p << RESET;
            }
            else if(p == 'O')
            {
                std::cout << BOLDRED << p << RESET;
            }
            else if(p == 'X')
            {
                std::cout << BOLDMAGENTA << p << RESET;
            }
        }
        std::cout << "\n";
    }
}


void Day3::RepeatPattern()
{
    for (int64_t row = 0; row < m_row; row++)
    {
        m_pattern[row].reserve(2 * m_pattern[row].size());
        m_pattern[row].insert(m_pattern[row].end(), m_pattern[row].begin(), m_pattern[row].end());
    }

    m_column += m_column;
}


Pattern Day3::LocateTrees(int16_t right, int16_t down)
{
    Pattern newPattern(m_pattern);
    int64_t col = 0; 
    for (int row = 0; row < m_row; row += down)
    {   
        if (col == 0)
        {
            col += right;
            continue;
        }
        if (newPattern[row][col] == '.')
        {
            newPattern[row][col] = 'O';
        }
        if (newPattern[row][col] == '#')
        {
            newPattern[row][col] = 'X';
        }
        col += right;
    }

    return newPattern;
}


int64_t Day3::CountTrees(const Pattern& pattern)
{
    int64_t treeCount = 0;
    for (const auto& p : pattern)
    {
        treeCount += std::count_if(p.begin(), p.end(), [](const char c) { return c == 'X'; });
    }

    return treeCount;
}




int main()
{
    Day3 d;

    //  d.PrintPattern();
    for (int64_t i = 0; i < 7; i++)
    {
        d.RepeatPattern();
    }

    auto patternWithSlope3_1 = d.LocateTrees(3, 1);
    // d.PrintPattern();
    std::cout << "Number of trees with slope (3, 1) is : " << d.CountTrees(patternWithSlope3_1) << "\n";
    

    auto patternWithSlope1_1 = d.LocateTrees(1, 1);
    auto patternWithSlope5_1 = d.LocateTrees(5, 1);
    auto patternWithSlope7_1 = d.LocateTrees(7, 1);
    auto patternWithSlope1_2 = d.LocateTrees(1, 2);

    std::cout << "The result for Part2 is: " << 
        d.CountTrees(patternWithSlope3_1) * d.CountTrees(patternWithSlope1_1) * d.CountTrees(patternWithSlope5_1) * 
        d.CountTrees(patternWithSlope7_1) * d.CountTrees(patternWithSlope1_2) << "\n";

    return 0;
}