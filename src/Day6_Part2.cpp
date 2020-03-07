#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <numeric>


typedef std::vector<std::pair<std::string, std::string>> Orbits;


void FindOrbitNum(Orbits& orbits, std::vector<std::string>& orb, std::string& o, int& count)
{
	auto it = std::find_if(orbits.begin(), orbits.end(),
		[&o](std::pair<std::string, std::string>& element) { return element.first == o; });

	if (it != orbits.end())
	{
		orb.emplace_back(it->second);
		++count;
		FindOrbitNum(orbits, orb, it->second, count);
	}
}


int main(int argc, char* argv[])
{
    std::string FILE = "resources/Day6.txt";

	std::ifstream input(FILE);
	Orbits orbits;
	std::string s;
	if (input.is_open())
	{
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
	std::vector<std::string> orbit_you, orbit_san;
	std::string s_you = "YOU";
	FindOrbitNum(orbits, orbit_you, s_you, count);

	count = 0;
	std::string s_san = "SAN";
	FindOrbitNum(orbits, orbit_san, s_san, count);


	std::vector<std::string> intersection;
	std::vector<std::string> temp_you(orbit_you);
	std::vector<std::string> temp_san(orbit_san);
	std::sort(temp_san.begin(), temp_san.end());
	std::sort(temp_you.begin(), temp_you.end());
	std::set_intersection(temp_san.begin(),temp_san.end(), temp_you.begin(), temp_you.end(), back_inserter(intersection));
	std::vector<int> res;
	for (auto o : intersection)
	{
		auto it_san = std::find(orbit_san.begin(), orbit_san.end(), o);
		auto it_you = std::find(orbit_you.begin(), orbit_you.end(), o);
		if (it_san != orbit_san.end() && it_you != orbit_you.end())
		{
			res.emplace_back((it_san - orbit_san.begin()) + (it_you - orbit_you.begin()));
		}
	}
	std::sort(res.begin(), res.end());
	std::cout << "\nres: " << res[0] << std::endl;
	
	return 0;
}
