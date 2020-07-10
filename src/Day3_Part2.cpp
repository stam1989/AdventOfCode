#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <array>
#include <algorithm>

struct Coords
{
	Coords() : x(0), y(0), steps(0) {}
	Coords(int x, int y, int s) : x(x), y(y), steps(s) {}
	Coords(const Coords& c) : x(c.x), y(c.y), steps(c.steps) {}
	bool operator==(const Coords& c)
	{
		return (c.x == x && c.y == y);
	}

	bool operator<(const Coords& c) const
	{
		if (x != c.x)
		{
			return (x < c.x);
		}
			return (y < c.y);
	}

	int x, y, steps;
};

typedef std::vector<std::vector<Coords>> Coordinates;
typedef std::vector<std::vector<std::string>> Wires;
typedef std::vector<Coords> Intersections;

std::vector <Coords> BuildPoints(std::vector<std::string>& p)
{
	Coords last_point;
	std::vector < Coords> coords;

	for (int i = 0; i < p.size(); ++i)
	{
		std::string dest = p[i];

		if (!coords.empty())
		{
			last_point.x = coords.back().x;
			last_point.y = coords.back().y;
			last_point.steps = coords.back().steps;
		}
		switch (dest.at(0))
		{
			case 'U':
			{
				dest.erase(dest.begin());
				for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
				{
					Coords buf(last_point.x, last_point.y + i + 1, ++last_point.steps);
					coords.push_back(buf);
				}
				continue;
			}
			case 'D':
			{
				dest.erase(dest.begin());
				for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
				{
					Coords buf(last_point.x, last_point.y - i - 1, ++last_point.steps);
					coords.push_back(buf);
				}
				continue;
			}
			case 'L':
			{
				dest.erase(dest.begin());
				for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
				{
					Coords buf(last_point.x- i - 1, last_point.y, ++last_point.steps);
					coords.push_back(buf);
				}
				continue;
			}
			case 'R':
			{
				dest.erase(dest.begin());
				for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
				{
					Coords buf(last_point.x + i + 1, last_point.y, ++last_point.steps);
					coords.push_back(buf);
				}

				continue;
			}
			default:
			{
				std::cerr << "Wrong Path:" << dest.at(0) << ", i=" << i << std::endl;
				break;
			}
		}
	}
	return coords;
}

void GetCoordinates(Wires& wires, Coordinates& c)
{
	for (auto wire : wires)
	{
		c.push_back(BuildPoints(wire));
	}
}


bool CompareByX(const Coords& a, const Coords& b)
{
	return a.x < b.x;
}


void GetIntersectons(Coordinates coordinates, Intersections& intersections)
{
	std::cout << "Getintersections starts \n ";
	std::cout << "coords[0].size(): " << coordinates[0].size() << std::endl;
	std::cout << "coords[1].size(): " << coordinates[1].size() << std::endl;
	sort(coordinates[0].begin(), coordinates[0].end(), CompareByX);
	sort(coordinates[1].begin(), coordinates[1].end(), CompareByX);

	//set_intersection(coordinates[0].begin(), coordinates[0].end(), coordinates[1].begin(), coordinates[1].end(), back_inserter(intersections));

	for (int i = 0; i < coordinates[0].size(); i++)
	{
		for (int j = 0; j < coordinates[1].size(); j++)
		{
			if (coordinates[0][i] == coordinates[1][j])
			{
				Coords temp(coordinates[0][i].x, coordinates[0][i].y, coordinates[0][i].steps + coordinates[1][j].steps);
				intersections.push_back(temp);
			}
		}
	}
}

bool CompareBySteps(const Coords& a, const Coords& b)
{
	return a.steps < b.steps;
}

void PrintSortestDistance(Intersections& intersections)
{
	sort(intersections.begin(), intersections.end(), CompareBySteps);
	std::cout << "\nSortest intersection steps: " << intersections.front().steps;
}

int main(int argc, char* argv[])
{
    std::string FILE = "../../../resources/Day3.txt";

	std::ifstream input(FILE);
	Wires wires;
	std::string p, current_string;
	if (input.is_open())
	{
		auto i = 0;
		while (std::getline(input, p))
		{
			std::stringstream ss(p);
			std::vector<std::string> buf;
			while (std::getline(ss, current_string, ','))
			{
				buf.push_back(current_string);
			}
			wires.push_back(buf);
		}
		input.close();
	}
	else
	{
		std::cout << "could not open input file: " << FILE << std::endl;
	}
	Coordinates coordinates;
	GetCoordinates(wires, coordinates);
	
	Intersections intersections;
	GetIntersectons(coordinates, intersections);
	std::cout << "after getintersections\n";
	std::cout << "Intersections are: ";
	for (auto x : intersections)
	{
		std::cout << "(" << x.x << "," << x.y << ", " << x.steps << "), ";
	}
	PrintSortestDistance(intersections);


	return 0;
}
