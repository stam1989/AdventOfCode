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

bool IfBlocked(std::pair<int, int>& possible_station, std::pair<int, int>& point_to_check, Coords& Coords)
{
    if()
}

int GetNumber(std::pair<int, int>& possible_station, Coords& coords)
{
    Coords asteroids_detected;
    for (auto &point : coords)
    {
        if (point == possible_station)
        {
            continue;
        }

        if (!IfBlocked(possible_station, point, asteroids_detected)
        {
            asteroids_detected.emplace_back(point);
        }
    }
    return asteroid_detected.size();
}

std::pair<int, int> FindStation(Coords coords)
{
    std::vector<int> asteroid_num;
    for(auto &possible_station : coords)
    {
        asteroid_num.emplace_back(GetNumber(possible_station, coords));
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
	
	
	return 0;
}
