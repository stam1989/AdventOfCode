//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day17.h"
#include "Color.h"

#include <iostream>


void ASCII::PrintViews()
{
    std::cout << "Print View:\n";
    int column = GetColumns();
    int row = m_Views.size();
    for (int r = 0; r < row - 1; r++)
    {
        for (int c = 0; c < column; c++)
        {
            if(m_Views[r][c] == '#') { std::cout << YELLOW << m_Views[r][c] << RESET; }
            else if(m_Views[r][c] == '.') { std::cout << GREEN << m_Views[r][c] << RESET; }
            else if(m_Views[r][c] == 'O') { std::cout << BOLDMAGENTA << m_Views[r][c] << RESET; }
            else { std::cout << BOLDRED << m_Views[r][c] << RESET; }
        }
        std::cout << "\n";
    }


        
}


int ASCII::GetColumns()
{
    int col = 0;
    for (const auto& view : m_Views)
    {
        for (const auto& v : view)
        {
            col++;
        }
        return col;
    }
}

int64_t ASCII::OpInput()
{
    switch (m_stage)
    {
        case 1:
            if (!m_mainMovementRoutine.empty())
            {
                const char* c = m_mainMovementRoutine.substr(0, 1).c_str();
                m_mainMovementRoutine.erase(0, 1);
                return int(*c);
            }
            else
            {
                m_stage++;
                return 10;
            }
        case 2:
            if (!m_movementFunctionA.empty())
            {
                const char* c = m_movementFunctionA.substr(0, 1).c_str();
                m_movementFunctionA.erase(0, 1);
                return int(*c);
            }
            else
            {
                m_stage++;
                return 10;
            }
        case 3:
            if (!m_movementFunctionA.empty())
            {
                const char* c = m_movementFunctionA.substr(0, 1).c_str();
                m_movementFunctionA.erase(0, 1);
                return int(*c);
            }
            else
            {
                m_stage++;
                return 10;
            }
        case 4:
            if (!m_movementFunctionB.empty())
            {
                const char* c = m_movementFunctionB.substr(0, 1).c_str();
                m_movementFunctionB.erase(0, 1);
                return int(*c);
            }
            else
            {
                m_stage++;
                return 10;
            }
        case 5:
            if (!m_movementFunctionC.empty())
            {
                const char* c = m_movementFunctionC.substr(0, 1).c_str();
                m_movementFunctionC.erase(0, 1);
                return int(*c);
            }
            else
            {
                m_stage++;
                return 10;
            }
        case 6:
            char isContinuousVideoFeed;
            std::cout << "Would you like to see a continuous video feed? (y/n)";
            std::cin >> isContinuousVideoFeed;
            m_stage++;
            return int(isContinuousVideoFeed);
        default:
            return 10;
    }

    return 10;
}

bool ASCII::OpOutput(int64_t output)
{
    if (m_stage > 0) 
    {
        std::cout << "Output: " << output << std::endl;
        return false;
    }

    if (output == 10)
    {
        m_Views.emplace_back(m_View);
        m_View.clear();
    }
    else { m_View.emplace_back(output); }

    return false;
}


int64_t ASCII::LocateIntersections()
{
    m_stage++;
    int64_t sum = 0;
    for (int col = 1; col < GetColumns() - 1; col++)
    {
        for (int row = 1; row < m_Views.size() - 1; row++)
        {
            if ((m_Views[col][row] == 35) && (m_Views[col][row] == m_Views[col - 1][row]) && (m_Views[col][row] == m_Views[col + 1][row]) &&
                (m_Views[col][row] == m_Views[col][row - 1]) && (m_Views[col][row] == m_Views[col][row + 1]))
            {
                m_Views[col][row] = 'O';
                sum += col * row;
            }
        }
    }

    return sum;
}


void ASCII::SetRobotsPosition()
{
    int column = GetColumns();
    int row = m_Views.size();
    for (int c = 0; c < column; c++)
    {
        for (int r = 0; r < row - 1; r++)
        {
            if (m_Views[r][c] == '>' || m_Views[r][c] == '<' ||
                m_Views[r][c] == 'v' || m_Views[r][c] == '^')
            {
                m_Vacuum.InitVacuum(r, c, m_Views[r][c]);
            }
        }
        std::cout << "\n";
    }
}

