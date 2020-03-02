//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <math.h>

using Coords = std::vector<std::pair<int, int>>;

static constexpr char FILENAME[] = "../../../resources/Day10.txt";


void ReadFile(Coords& coords)
{
// 	std::vector<std::string> lines;
	std::ifstream input(FILENAME);
	std::string line;
	try
	{
		if (input.is_open())
		{
			size_t x = 0, y = 0;
			while (std::getline(input, line))
			{
				for(auto& ch : line)
				{
					if(ch == '#')
					{
						coords.emplace_back(std::make_pair(x, y));
					}
					x++;
				}
				y++;
				x = 0;
			}
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


int GetNumber(std::pair<int, int>& possible_station, Coords coords)
{
    Coords asteroids_detected;
    for (auto i = 0; i < coords.size(); i++)
    {		
		if (coords[i] == possible_station)
		{
			continue;
		}
		
		if (asteroids_detected.empty())
		{
			asteroids_detected.emplace_back(coords[i]);
			continue;
		}
		
		bool intersection_flag = false;
		for (auto j = 0; j < asteroids_detected.size(); j++)
		{
			if(std::atan2(possible_station.first - asteroids_detected[j].first, possible_station.second - asteroids_detected[j].second) == 
				std::atan2(possible_station.first - coords[i].first, possible_station.second - coords[i].second))
			{
				intersection_flag = true;
				
				if(abs(possible_station.second - asteroids_detected[j].second) < abs(possible_station.second - coords[i].second))
				{
					std::swap(asteroids_detected[j], coords[i]);
				}
				
				break;
			}
		}
		
		if (!intersection_flag)
		{
			asteroids_detected.emplace_back(coords[i]);
		}
		
    }
    return asteroids_detected.size();
}


void FindStation(Coords coords)
{
    std::vector<int> asteroid_num;
    for(auto &possible_station : coords)
    {
        asteroid_num.emplace_back(GetNumber(possible_station, coords));
    }
    
    auto max_ast_pos = std::max_element(asteroid_num.begin(), asteroid_num.end());
	int pos = std::distance(asteroid_num.begin(), max_ast_pos);
	
	std::cout << "The station should be built in: (" << coords[pos].first << " ," << coords[pos].second << ") with " << *max_ast_pos << " asteroids detected!\n";
}

struct Point
{
	int x, y, slope, position
}

void VaporizeAsteroid(Coords coords, std::pair<int, int> station)
{
	std::vector<std::pair<int, int>> slopes;   // vector of pairs of sloped and point's position in coords
	for (auto i = 0; i < coords.size(); i++)
	{
		if (coords[i] == station)
		{
			continue;
		}
		slope.emplace_back(std::atan2(), i);
	}
}


void PrintCoords(Coords& coords)
{
	for (auto& point : coords)
	{
		std::cout << "(" << point.first << ", " << point.second << "), ";
	}
	std::cout << std::endl;
}


int main()
{
	Coords coords, line_coords;
	ReadFile(coords);
	
	PrintCoords(coords);
	FindStation(coords);
	
// 	std::cout << std::atan2(0, 1) << ", " << std::atan2(1,0) << std::endl;
	
	return 0;
}
