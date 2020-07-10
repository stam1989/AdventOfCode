//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <numeric>

typedef std::vector<std::pair<std::string, std::string>> Orbits;


void FindOrbitNum(Orbits& orbits, int& count, std::string& o)
{
	/*auto it = std::find_if(orbits.begin(), orbits.end(),
		[&o](std::pair<std::string, std::string>& element) { return element.first == o; });
	it = std::find(orbits.begin(), orbits.end(), o);
	if (it != orbits.end())
	{
		FindOrbitNum(orbits, count, it->second);
		count++;
	}*/

	for (auto orbit : orbits)
	{
		if (orbit.first == o)
		{
			FindOrbitNum(orbits, count, orbit.second);
			count++;
		}
	}

}


int main(int argc, char* argv[])
{
    std::string FILE = "../../../resources/Day6.txt";

	std::ifstream input(FILE);
	Orbits orbits;
	std::string s;
	if (input.is_open())
	{
		auto i = 0;
		while (std::getline(input, s))
		{
			orbits.emplace_back(std::make_pair(s.substr(4, 7), s.substr(0, 3)));
		}
		input.close();
	}
	else
	{
		std::cout << "could not open input file: " << FILE << std::endl;
	}

	int count = 0;
	std::map<std::string, int> orbit_count;
	for (auto o : orbits)
	{
		int count = 1;
		FindOrbitNum(orbits, count, o.second);
		orbit_count.emplace(o.first, count);
		//std::cout << o.first << "-> " << count << std::endl;
	}

	const int result = std::accumulate(std::begin(orbit_count), std::end(orbit_count), 0,
		[](const std::size_t previous, const std::pair<const std::string, int>& p)
		{ return previous + p.second; });
	std::cout << result << "\n";

	return 0;
}
