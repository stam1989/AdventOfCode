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




Coords drawline(int x0, int y0, int x1, int y1)
{
	int dx, dy, p, x, y;
	
	dx=x1-x0;
	dy=y1-y0;
	
	x=x0;
	y=y0;
	
	p=2*dy-dx;
	
	Coords line_coords;
	
	while(x<x1)
	{
		if(p>=0)
		{
			line_coords.emplace_back(x, y);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			line_coords.emplace_back(x, y);
			p=p+2*dy;
		}
		x=x+1;
	}
	return line_coords;
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
	std::cout << "\n\nline between: " << "(" << coords[0].first << ", " << coords[0].second << "), and: " << "(" << coords[8].first << ", " << coords[8].second << ")\n";
	line_coords = drawline(coords[0].first, coords[0].second, coords[8].first, coords[8].second);
	PrintCoords(line_coords);
	
	
	return 0;
}
