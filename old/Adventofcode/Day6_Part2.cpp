#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <numeric>


typedef std::vector<std::pair<std::string, std::string>> Orbits;


void FindOrbitNum(Orbits& orbits, std::vector<std::pair<std::string, int>>& orb, std::string& o, int& count)
{
    auto it = std::find_if(orbits.begin(), orbits.end(),
        [&o](std::pair<std::string, std::string>& element) { return element.first == o; });

    if (it != orbits.end())
    {
        orb.emplace_back(std::make_pair(it->second, count));
        ++count;
        FindOrbitNum(orbits, orb, it->second, count);
    }
}


int main(int argc, char* argv[])
{
    std::string FILE = "/home/neo/workspace/Adventofcode/resources/Day6.txt";

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
    std::vector<std::pair<std::string, int>> orbit_you, orbit_san;
    std::string s_you = "YOU";
    FindOrbitNum(orbits, orbit_you, s_you, count);

    count = 0;
    std::string s_san = "SAN";
    FindOrbitNum(orbits, orbit_san, s_san, count);

    if (orbit_san.size() < orbit_you.size())
    {
        orbit_san.resize(orbit_you.size());
    }
    else
    {
        orbit_you.resize(orbit_san.size());
    }

    std::vector<int> res;
    std::transform(orbit_you.begin(), orbit_you.end(), orbit_san.begin(), back_inserter(res),
            [](std::pair<std::string, int>& you, std::pair<std::string, int>& san)
            {
                if (you.first == san.first)
                {
                    return you.second + san.second;
                }
            }
    );
    std::sort(res.begin(), res.end());
    res.erase(std::remove(res.begin(), res.end(), 0), res.end());
    for (auto& r : res)
        { std::cout << "Result: " << r << std::endl; }

//    int res = 0;
//    for (const auto& you : orbit_you)
//    {
//        for (const auto& san : orbit_san)
//        {
//            if (you.first == san.first)
//            {
//                res = you.second + san.second;
//                std::cout << "\nres: " << res << std::endl;
//                goto end_label;
//            }
//        }
//    }

end_label:  return 0;
}
