#include <iostream>
#include <fstream>
#include <string>

int Calc(int mass)
{
	int temp = std::floor(mass / 3) - 2;
	if (temp < 1)
	{
		return 0;
	}
	else
	{	
		return temp += Calc(temp);
	}
	return temp;
	
}

void AddMass(int& res,int mass)
{
	res += Calc(mass);
}

void PrintResult(int& res)
{
	std::cout << "The sum of the fuel requirements is: " << res << std::endl;
}

int main(int argc, char* argv[]) {

	std::string FILE = "C:\Users\stam1989\source\repos\AdventOfCode\resources\Day1.txt";

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