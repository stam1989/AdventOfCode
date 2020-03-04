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
	Point(int x, int y, double a) : x(x), y(y), angle(a) {}
	
	bool operator <(Point& p)
    {
        return angle < p.angle;
    }

	bool operator ==(Point& p)
	{
		return x == p.x && y == p.y;
	}
	
	int x, y;
	double angle;
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


Coords PopulateAsteroidMap(Point& candidate_station, Coords coords)
{
	Coords asteroids_detected;
	for (auto i = 0; i < coords.size(); i++)
	{		
        if (coords[i].x == candidate_station.x && coords[i].y == candidate_station.y)
		{
			continue;
		}
		
		if (asteroids_detected.empty())
		{
            coords[i].angle = std::atan2(candidate_station.x - coords[i].x, candidate_station.y - coords[i].y);
			asteroids_detected.emplace_back(coords[i]);
			continue;
		}
		
		bool intersection_flag = false;
		for (auto j = 0; j < asteroids_detected.size(); j++)
		{
			if(std::atan2(candidate_station.x - asteroids_detected[j].x, candidate_station.y - asteroids_detected[j].y) ==
				std::atan2(candidate_station.x - coords[i].x, candidate_station.y - coords[i].y))
			{
				intersection_flag = true;
				
				if(abs(candidate_station.y - asteroids_detected[j].y) > abs(candidate_station.y - coords[i].y))
				{
                    coords[i].angle = std::atan2(candidate_station.x - coords[i].x, candidate_station.y - coords[i].y);
                    std::swap(asteroids_detected[j], coords[i]);
				}
				else if(abs(candidate_station.x - asteroids_detected[j].x) > abs(candidate_station.x - coords[i].x))
                {
                    coords[i].angle = std::atan2(candidate_station.x - coords[i].x, candidate_station.y - coords[i].y);
                    std::swap(asteroids_detected[j], coords[i]);
                }
				
				break;
			}
		}
		
		if (!intersection_flag)
		{
            coords[i].angle = std::atan2(candidate_station.x - coords[i].x, candidate_station.y - coords[i].y);
            asteroids_detected.emplace_back(coords[i]);
		}
	}
	return asteroids_detected;
}


int GetAsteroidNumber(Point& candidate_station, Coords coords)
{
	return PopulateAsteroidMap(candidate_station, coords).size();
}


Point FindStation(Coords coords)
{
    std::vector<int> asteroid_num;
    for(auto &candidate_station : coords)
    {
        asteroid_num.emplace_back(GetAsteroidNumber(candidate_station, coords));
    }
    
    auto max_ast_pos = std::max_element(asteroid_num.begin(), asteroid_num.end());
	int pos = std::distance(asteroid_num.begin(), max_ast_pos);
	
	std::cout << "The station should be built in: (" << coords[pos].x << " ," << coords[pos].y << ") with " << *max_ast_pos << " asteroids detected!\n";
	
	return coords[pos];
}


void PrintCoords(Coords& coords)
{
	for (auto& point : coords)
	{
		std::cout << "(" << point.x << ", " << point.y << "): " << point.angle << std::endl;
	}
	std::cout << std::endl;
}


void ReplaceOrRemove(Coords& coords, Coords& asteroids, Point& station, int pos)
{
	std::cout << "ast to be rem: (" << asteroids[pos].x << ", " << asteroids[pos].y << ")\n"; 
	bool flag;
	
	Coords temp_point;
	
	coords.erase(std::remove_if(coords.begin(), coords.end(), [&](Point& p) { return p == asteroids[pos]; }), coords.end());
	
	auto iter = std::find_if(coords.begin(), coords.end(), [&](const Point& p) { return asteroids[pos].angle == p.angle; });
	
	if (iter == coords.end())
	{
// 		std::cout << "Not replaced! \n\n\n";
		asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [&](Point& p) { return p == asteroids[pos]; }), asteroids.end());
		return;
	}
	
	std::swap(asteroids[pos], *iter);
	
	while ((iter = std::find_if(iter, coords.end(), [&](const Point& p) { return asteroids[pos].angle == p.angle; })) != coords.end())
	{
		flag = true;
		
		if(abs(station.y - asteroids[pos].y) > abs(station.y - iter->y))
		{
			iter->angle = std::atan2(station.x - iter->x, station.y - iter->y);
			std::swap(asteroids[pos], *iter);
		}
		else if(abs(station.x - asteroids[pos].x) > abs(station.x - iter->x))
		{
			iter->angle = std::atan2(station.x - iter->x, station.y - iter->y);
			std::swap(asteroids[pos], *iter);
		}
		temp_point.emplace_back(*iter);
		
		iter++;
	}
}



void VaporizeAsteroid(Point station, Coords coords, int vap_count)
{
	Coords asteroids_detected = PopulateAsteroidMap(station, coords);
	
//     std::sort(asteroids_detected.begin(), asteroids_detected.end());
	
    Coords ast_neg, ast_pos;

	for (auto ast : asteroids_detected)
	{
// 		std::cout << "(" << ast.x << ", " << ast.y << "): " << ast.angle << std::endl;
        if (ast.angle > 0)
            ast_pos.emplace_back(ast);
        else
            ast_neg.emplace_back(ast);
	}

	PrintCoords(ast_pos);
	PrintCoords(ast_neg);
	
	int count = 0;
	
    while (count < vap_count)
    {
        for(int i = ast_neg.size(); i > 0; i--)
        {
			std::sort(ast_neg.begin(), ast_neg.end());
            if (count == vap_count)
                break;

//             ast_neg.erase(std::remove_if(ast_neg.begin(), ast_neg.end(), [&](Point& p) { return p == ast_neg[i]; }), ast_neg.end());

			ReplaceOrRemove(coords, ast_neg, station, i);
			
            count++;
        }

        for(int i = ast_pos.size(); i > 0; i--)
        {
			std::sort(ast_pos.begin(), ast_pos.end());
            if (count == vap_count)
                break;

// 			ast_pos.erase(std::remove_if(ast_pos.begin(), ast_pos.end(),[&](Point& p) { return p == ast_pos[i]; }), ast_pos.end());
			
			ReplaceOrRemove(coords, ast_pos, station, i);
			
            count++;
        }

    }

    PrintCoords(ast_pos);
	PrintCoords(ast_neg);
    
}


int main()
{
	Coords coords, line_coords;
	ReadFile(coords);
	
// 	PrintCoords(coords);
	Point station = FindStation(coords);
	
	VaporizeAsteroid(station, coords, 200);
// 	std::cout << std::atan2(0, 1) << ", " << std::atan2(1,0) << std::endl;
	
	return 0;
}
