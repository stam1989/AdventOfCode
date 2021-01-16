//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day18.h"
#include "Color.h"

#include <iostream>
#include <fstream>



void Day18::ScanMap()
{
	std::ifstream input(FILENAME);
	std::string line;
    if (input.is_open())
    {
        std::vector<char> temp_map;
        while (std::getline(input, line))
        {
            for(auto& ch : line)
            {
                temp_map.emplace_back(ch);
            }
            m_map.emplace_back(temp_map);
            temp_map.clear();
        }

        input.close();
    }
    else
    {
        std::string exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }
}


void Day18::PrintMap()
{

    for (const auto& m : m_map)
    {
        for(const auto& el : m)
        {
            if(el == '#') { std::cout << YELLOW << el << RESET; }
            else if(el == '.') { std::cout << GREEN << el << RESET; }
            else if(el == '@') { std::cout << BOLDMAGENTA << el << RESET; }
            else if(int(el) > 96) { std::cout << RED << el << RESET; }
            else { std::cout << BOLDRED << el << RESET; }
        }
        std::cout << "\n";
    }
}


void Day18::InitPosition()
{
    for(int y = 0; y < m_map.size(); y++)
    {
        for(int x = 0; x < m_map[y].size(); x++)
        {
            if (m_map[y][x] == '@' )
            {
                m_pos.x = x;
                m_pos.y = y;
                return;
            }
        }
    }
    
    throw std::runtime_error("InitPosition:: start position not found...");
}


bool Day18::IsAllCollected()
{
    auto it_map = std::find_if(m_map.begin(), m_map.end(), 
    [](const std::vector<char>& el) 
    {
        auto it_el = std::find_if(el.begin(), el.end(), 
        [](const char ch) { return (int(ch) > 96 && int(ch) < 123); });
        return it_el != el.end();
    });

    return it_map == m_map.end();
}


void Day18::Move(Direction dir)
{
    switch (static_cast<int>(dir))
    {
    case Up:
        m_pos.prev_y = m_pos.y;
        m_pos.y += 1;
        break;
    case Down:
        m_pos.prev_y = m_pos.y;
        m_pos.y -= 1;
        break;
    case Right:
        m_pos.prev_x = m_pos.x;
        m_pos.x += 1;
        break;
    case Left:
        m_pos.prev_x = m_pos.x;
        m_pos.x -= 1;
        break;
    default:
        break;
    }
    
}


int Day18::NextPosition()
{
    // if()
}


int main()
{
    try
    {
        Day18 d;
        d.PrintMap();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
	catch(std::string& exception_string)
	{
		std::cout << exception_string << std::endl;
	}

    return 0;
}