//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day15.h"
#include "Color.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

void Maze::InializePanel()
{
    for (size_t col = 0; col < COLUMN; col++)
    {
        for (size_t row = 0; row< ROW; row++)
        {
                m_Panel[row][col] = " ";
        }
    }
    m_Panel[COLUMN / 2][ROW / 2] = ".";     // Droid's start point 
}

void Maze::PrintPanel()
{
    for(size_t col = 0; col < COLUMN; col++)
    {
        for (size_t row = 0; row < ROW; row++)
        {
            if (m_Panel[col][row] == "O")
            {
            std::cout << MAGENTA << m_Panel[col][row] << RESET;
            continue;
            }

            if (col == m_Droid.y && row == m_Droid.x)
            {
                std::cout << BOLDRED << "D" << RESET;
                continue;
            }
            
            if (col == COLUMN / 2 && row == ROW / 2)
            {
                std::cout << RED << "S" << RESET;
                continue;
            }
            
            if (m_Panel[col][row] == ".")
                std::cout << GREEN << m_Panel[col][row] << RESET;
            else if (m_Panel[col][row] == "#")
                std::cout << YELLOW << m_Panel[col][row] << RESET;
            else 
                std::cout << BLUE << m_Panel[col][row] << RESET;        
        }
        std::cout << std::endl;
    }
}


uint8_t Maze::MoveToUnexplored()
{
    if((m_Droid.y + 1 < COLUMN) && (m_Panel[m_Droid.y + 1][m_Droid.x] == " "))
    {
        return Direction::NORTH; 
    }

    if((m_Droid.y + 1 >= 0) && (m_Panel[m_Droid.y - 1][m_Droid.x] == " "))
    {
        return Direction::SOUTH; 
    }
    
    if((m_Droid.x + 1 < ROW) && (m_Panel[m_Droid.y][m_Droid.x + 1] == " "))
    {
        return Direction::WEST;
    }

    if((m_Droid.x - 1 >= 0) && (m_Panel[m_Droid.y][m_Droid.x - 1] == " "))
    {
        return Direction::EAST;
    }

    return 0;
}


Maze::Direction Maze::Backtrack() 
{
    int prevVertex_X = m_SuspendedVertexes.top().first;
    int prevVertex_Y = m_SuspendedVertexes.top().second;

    if ((m_Droid.x == prevVertex_X) && (m_Droid.y + 1 == prevVertex_Y))
    {
        return Direction::NORTH;
    }

    if ((m_Droid.x == prevVertex_X) && (m_Droid.y - 1 == prevVertex_Y))
    {
        return Direction::SOUTH;
    }

    if ((m_Droid.x + 1 == prevVertex_X) && (m_Droid.y == prevVertex_Y))
    {
        return Direction::WEST;
    }

    if ((m_Droid.x - 1 == prevVertex_X) && (m_Droid.y == prevVertex_Y))
    {
        return Direction::EAST;
    }

    throw std::runtime_error("Backtrack:: Backtrack failed...");
}


void Maze::FillBlock(const Maze::Direction& dir)
{
    switch (static_cast<uint8_t>(dir))
    {
        case NORTH:
            m_Panel[m_Droid.y + 1][m_Droid.x] = "#";
            break;
        case SOUTH:
            m_Panel[m_Droid.y - 1][m_Droid.x] = "#";
            break;
        case WEST:
            m_Panel[m_Droid.y][m_Droid.x + 1] = "#";
            break;
        case EAST:
            m_Panel[m_Droid.y][m_Droid.x - 1] = "#";
            break;
        default:
            std::cout << "Can't move to " << static_cast<uint8_t>(dir) << std::endl;
            throw std::invalid_argument("invalid move...");
    }
}


int64_t Maze::OpInput()
{
    m_Droid.backtrack_state = false;
    m_Dir = MoveToUnexplored();
    if (m_Dir)
    {
        return m_Dir;
    }

    m_Droid.backtrack_state = true;
    m_Dir = static_cast<int64_t>(Backtrack());
    return m_Dir;
}


void Maze::MoveDroid(const Direction& dir)
{
    switch (static_cast<uint8_t>(dir))
    {
        case NORTH:
            m_Droid.y += 1;
            break;
        case SOUTH:
            m_Droid.y -= 1;
            break;
        case WEST:
            m_Droid.x += 1;
            break;
        case EAST:
            m_Droid.x -= 1;
            break;
        default:
            std::cout << "Can't move to " << static_cast<uint8_t>(dir) << std::endl;
            throw std::invalid_argument("invalid move...");
    }
}

bool Maze::OpOutput(int64_t status)
{
    if (status == 2)
    {
        if(m_Droid.backtrack_state)
        {
            m_SuspendedVertexes.pop();
            if (m_SuspendedVertexes.empty())
            {
                std::cout << "Map is explored!!!\n";
                return true;
            }
        }
        else
        {
            m_SuspendedVertexes.emplace(std::make_pair(m_Droid.x, m_Droid.y));            
        }

        if (m_Dir > 0 && m_Dir <= 4)
        {
            MoveDroid(static_cast<Direction>(m_Dir)); 
        }
        else
        {
            throw std::runtime_error("OpOutput:: invalid dir...\n");
        }

        m_Panel[m_Droid.y][m_Droid.x] = "O";
        PrintPanel();
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
        
        // return false;
    }

    if (status == 1)
    {
        if(m_Droid.backtrack_state)
        {
            m_SuspendedVertexes.pop();
            if (m_SuspendedVertexes.empty())
            {
                std::cout << "Map is explored!!!\n";
                return true;
            }
        }
        else
        {
            m_SuspendedVertexes.emplace(std::make_pair(m_Droid.x, m_Droid.y));            
        }

        if (m_Dir > 0 && m_Dir <= 4)
        {
            MoveDroid(static_cast<Direction>(m_Dir)); 
        }
        else
        {
            throw std::runtime_error("OpOutput:: invalid dir...\n");
        }

        m_Panel[m_Droid.y][m_Droid.x] = ".";
    }

    if (status == 0)
    {
        if (m_Dir > 0 && m_Dir <= 4)
        {
            FillBlock(static_cast<Direction>(m_Dir));
        }
        else
        {
            throw std::runtime_error("OpOutput:: invalid dir...\n");
        }
        
    }

    PrintPanel();
    std::this_thread::sleep_for(std::chrono::milliseconds(17));

    return false;
}


std::pair<int, int> Maze::GetOxygenPosition()
{
    for(int y = 0; y < COLUMN; y++)
    {
        for(int x = 0; x < ROW; x++)
        {
            if (m_Panel[y][x] == "O")
            {
                return std::make_pair(x, y);
            }
        }
    }
}


void Maze::FindShortestPath(int cur_X, int cur_Y, std::pair<int, int> dest, int32_t curDistance, int32_t& minDistance)
{
    if((cur_X == dest.first) && (cur_Y == dest.second))
    {
        minDistance = std::min(curDistance, minDistance);
        return;
    }

    m_Visited.emplace(std::make_pair(cur_X, cur_Y));

    if(IsSafe(cur_X + 1, cur_Y) && IsValid(cur_X + 1, cur_Y))
    {
        FindShortestPath(cur_X + 1, cur_Y, dest, curDistance + 1, minDistance);
    }

    if(IsSafe(cur_X, cur_Y + 1) && IsValid(cur_X, cur_Y + 1))
    {
        FindShortestPath(cur_X, cur_Y + 1, dest, curDistance + 1, minDistance);
    }

    if(IsSafe(cur_X - 1, cur_Y) && IsValid(cur_X - 1, cur_Y))
    {
        FindShortestPath(cur_X - 1, cur_Y, dest, curDistance + 1, minDistance);
    }

    if(IsSafe(cur_X, cur_Y - 1) && IsValid(cur_X, cur_Y - 1))
    {
        FindShortestPath(cur_X, cur_Y - 1, dest, curDistance + 1, minDistance);
    }

    auto it = m_Visited.find(std::make_pair(cur_X, cur_Y));
    if(it != m_Visited.end())
    {
        m_Visited.erase(it);
    }
}


bool Maze::IsFullOfOxygen()
{
    for (int col = 0; col < COLUMN; col++)
    {
        for (int row = 0; row < ROW; row++)
        {
            if(m_Panel[col][row] == ".")
                return false;
        }
    }

    return true;
}


void Maze::FillAdjacent()
{
    Panel temp_Panel = m_Panel;
    for (int col = 0; col < COLUMN; col++)
    {
        for (int row = 0; row < ROW; row++)
        {
            if(temp_Panel[col][row] == "O")
            {
                if(temp_Panel[col + 1][row] == ".")
                    m_Panel[col + 1][row] = "O";
                
                if(temp_Panel[col - 1][row] == ".")
                    m_Panel[col - 1][row] = "O";
                
                if(temp_Panel[col][row + 1] == ".")
                    m_Panel[col][row + 1] = "O";
                
                if(temp_Panel[col][row - 1] == ".")
                    m_Panel[col][row - 1] = "O";

            }
        }
    }
}


void Maze::CaluclateTimeToFillOxygen(uint16_t& timeElapsed)
{
    FillAdjacent();
    timeElapsed++;
    if(!IsFullOfOxygen())
    {
        PrintPanel();
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
        CaluclateTimeToFillOxygen(timeElapsed);
    }
}