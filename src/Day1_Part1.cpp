#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void AddMass(int& res, int mass)
{
	res += floor(mass / 3) -2;
}

void PrintResult(int& res)
{
	std::cout << "The sum of the fuel requirements is: " << res << std::endl;
}

int main() {

    std::string FILE = "resources/Day1.txt";

	std::ifstream input(FILE);
	std::string line_input;
	int res = 0;
	if (input.is_open())
	{
		while (std::getline(input, line_input))
		{
			AddMass(res, std::stoi(line_input, nullptr, 10));
		}
		input.close();
	}
	else
	{
		std::cout << "could not open input file: " << FILE << std::endl;
	}

	PrintResult(res);
	return 0;
}
