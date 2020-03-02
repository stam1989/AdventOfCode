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


static constexpr char FILENAME[] = "../../../resources/Day10.txt";

struct Point
{
	Point(int x, int y) : x(x), y(y) {}
	Point(int x, int y, long a) : x(x), y(y), angle(a) {}
	
	bool operator <(Point& p)
	{
		return angle < p.angle;
	}
	
	bool operator ==(Point& p)
	{
		return x == p.x && y == p.y;
	}
	
	int x, y;
	long angle;
};


using Coords = std::vector<Point>;



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
						coords.emplace_back(Point(x, y));
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



Coords DetectAsteroids(Point& possible_station, Coords coords)
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
			if(std::atan2(possible_station.x - asteroids_detected[j].x, possible_station.y - asteroids_detected[j].y) == 
				std::atan2(possible_station.x - coords[i].x, possible_station.y - coords[i].y))
			{
				intersection_flag = true;
				
				if(abs(possible_station.y - asteroids_detected[j].y) > abs(possible_station.y - coords[i].y))
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
	return asteroids_detected;
}

int GetNumber(Point& possible_station, Coords coords)
{
	return DetectAsteroids(possible_station, coords).size();
}


Point FindStation(Coords coords)
{
    std::vector<int> asteroid_num;
    for(auto &possible_station : coords)
    {
        asteroid_num.emplace_back(GetNumber(possible_station, coords));
    }
    
    auto max_ast_pos = std::max_element(asteroid_num.begin(), asteroid_num.end());
	int pos = std::distance(asteroid_num.begin(), max_ast_pos);
	
	std::cout << "The station should be built in: (" << coords[pos].x << " ," << coords[pos].y << ") with " << *max_ast_pos << " asteroids detected!\n";
	
	return coords[pos];
}


void VaporizeAsteroid(Point station, Coords coords)
{
	Coords asteroids_detected = DetectAsteroids(station, coords);
	
	std::sort(asteroids_detected.begin(), asteroids_detected.end());
	
	for (auto ast : asteroids_detected)
	{
		std::cout << "(" << ast.x << ", " << ast.y << "): " << std::atan2(station.x -ast.x, station.y - ast.y) << std::endl;
	}
}


void PrintCoords(Coords& coords)
{
	for (auto& point : coords)
	{
		std::cout << "(" << point.x << ", " << point.y << "), ";
	}
	std::cout << std::endl;
}


int main()
{
	Coords coords, line_coords;
	ReadFile(coords);
	
// 	PrintCoords(coords);
	Point station = FindStation(coords);
	
	VaporizeAsteroid(station, coords);
// 	std::cout << std::atan2(0, 1) << ", " << std::atan2(1,0) << std::endl;
	
	return 0;
}
