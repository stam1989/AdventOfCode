//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <math.h>

//void CalcFuel(int mass, uint32_t* res)
//{
//    res += round(mass / 3) - 2;
//}

void AddFuel(uint32_t mass, int& res)
{
   res += floor(mass / 3) - 2;
}

void PrintRes(int& res)
{
    std::cout << res << std::endl;
}

int main () {
    std::string FILE = "/home/neo/workspace/Adventofcode/resources/Day1_input.txt";
    std::ifstream file(FILE);
    int res = 0;
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            AddFuel(stoi(line, nullptr, 10), res);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open the file" << std::endl;
    }
    PrintRes(res);
    return 0;
}
