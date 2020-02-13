//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <array>
#include <functional>
#include <algorithm>

typedef std::vector<std::vector<std::pair<int, int>>> Coordinates;
typedef std::vector<std::vector<std::string>> Paths;
typedef std::vector<std::pair<int, int>> Intersections;

std::vector < std::pair<int, int>> BuildPoints(std::vector<std::string>& p)
{
    std::pair<int, int> last_point;
    std::vector < std::pair<int, int>> coords;

    for (int i = 0; i < p.size(); ++i)
    {
        std::string dest = p[i];

        if (coords.empty())
        {
            last_point = std::make_pair(0, 0);
        }
        else
        {
            last_point = coords.back();
        }
        switch (dest.at(0))
        {

            case 'U':
            {
                dest.erase(dest.begin());
                for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
                {
                    std::pair<int, int> buf(last_point.first, last_point.second + i + 1);
                    coords.push_back(buf);
                }
                continue;
            }
            case 'D':
            {
                dest.erase(dest.begin());
                for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
                {
                    std::pair<int, int> buf(last_point.first, last_point.second - i - 1);
                    coords.push_back(buf);
                }
                continue;
            }
            case 'L':
            {
                dest.erase(dest.begin());
                for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
                {
                    std::pair<int, int> buf(last_point.first - i - 1, last_point.second);
                    coords.push_back(buf);
                }
                continue;
            }
            case 'R':
            {
                dest.erase(dest.begin());
                for (int i = 0; i < abs(std::stoi(dest, nullptr, 10)); i++)
                {
                    std::pair<int, int> buf(last_point.first + i + 1, last_point.second);
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

void GetCoordinates(Paths& paths, Coordinates& c)
{
    for (auto path : paths)
    {
        c.push_back(BuildPoints(path));
    }
}

void GetIntersectons(Coordinates coords, Intersections& intersections)
{
    Coordinates temp(coords);
    std::sort(coords[0].begin(),coords[0].end());
    std::sort(coords[1].begin(), coords[1].end());

    std::vector<std::pair<int, int>>::iterator it, st;

    std::set_intersection(coords[0].begin(),
        coords[0].end(),
        coords[1].begin(),
        coords[1].end(),
        back_inserter(intersections));
    std::vector<std::vector<int>> steps;
    for(auto i : intersections)
    {
        auto it0 = std::find(coords[0].begin(), coords[0].end(), i);
        auto it1 = std::find(coords[1].begin(), coords[1].end(), i);

        if (it0 == coords[0].end() || it1 == coords[1].end())
        {
            std::cout << "Something is wrong!!!\n";
            break;
        }

        std::cout << "after set intersection\n";
        std::vector<int> temp0(std::distance(coords[0].begin(), it0));
        std::vector<int> temp1(std::distance(coords[1].begin(), it1));
        steps.emplace_back(temp0);
        steps.emplace_back(temp1);
        std::vector<int> result;
        std::transform(steps[0].begin(), steps[0].end(), steps[1].begin(), std::back_inserter(result), std::plus<int>());
        std::sort(result.begin(), result.end());
        std::cout << "Shortest distance is: " << result[0] << std::endl;
    }
}

void PrintSortestDistance(Intersections& intersections)
{
    std::vector<int> temp;
    for (auto d : intersections)
    {
        temp.push_back(abs(d.first) + abs(d.second));
    }
    std::sort(temp.begin(), temp.end());
    std::cout << "\nSortest intersection distance: " << temp.front();
}

int main(int argc, char* argv[])
{
    std::string FILE = "/home/neo/workspace/Adventofcode/resources/Day3.txt";

    std::ifstream input(FILE);
    Paths paths;
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
            paths.push_back(buf);
        }
        input.close();
    }
    else
    {
        std::cout << "could not open input file: " << FILE << std::endl;
    }

    Coordinates coordinates;
    GetCoordinates(paths, coordinates);
    Intersections intersections;
    GetIntersectons(coordinates, intersections);

   // PrintSortestDistance(intersections);


    return 0;
}


