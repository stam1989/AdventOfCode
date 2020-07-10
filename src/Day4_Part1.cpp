#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <array>
#include <algorithm>

void CreatePswds(std::vector<int>& range, std::vector<std::string>& pswds)
{
	for (int i = range[0]; i < range[1] + 1; i++)
	{
		pswds.emplace_back(std::to_string(i));
	}
}

void PurgeNonSixDigit(std::vector<std::string>& pswds)
{
	pswds.erase(std::remove_if(pswds.begin(), pswds.end(), [](std::string pswd) { return (pswd.size() != 6); }),
		pswds.end());
}

bool IfDecrease(std::string& pswd)
{
	std::vector<int> digits;
	for (char p : pswd)
	{
		digits.emplace_back(int(p));
	}
	std::vector<int> temp(digits);
	std::sort(digits.begin(), digits.end());

	return (digits != temp);
}

void PurgeIfDecrease(std::vector<std::string>& pswds)
{
	pswds.erase(std::remove_if(pswds.begin(), pswds.end(), IfDecrease),
		pswds.end());
}

bool IfSame(std::string& pswd)
{
	bool res = true;
	std::map<char, int> digit_count;
	std::map<char, int>::iterator it;
	digit_count.emplace(pswd[0], 1);
	for (int i = 1; i < pswd.size(); i++)
	{
		it = digit_count.find(pswd[i]);
		if (it != digit_count.end())
		{
			it->second++;
		}
		else
		{
			digit_count.emplace(pswd[i], 1);
		}
    }
	for (it = digit_count.begin(); it != digit_count.end(); it++)
	{
		if (it->second == 2)
		{
			res = false;
			break;
		}
	}
	
	return res;
}

void PurgeIfNotSame(std::vector<std::string>& pswds)
{
	pswds.erase(std::remove_if(pswds.begin(), pswds.end(), IfSame),
		pswds.end());
}

void PrintPswds(std::vector<std::string> pswds)
{
	std::cout << "\nPasswords: ";
	for (auto p : pswds)
		std::cout << p << ", ";

	std::cout << "Number of valid pswds: " << pswds.size() << std::endl;
}

int main(int argc, char* argv[])
{
    std::string FILE = "../../../resources/Day4.txt";

	std::ifstream input(FILE);
	std::vector<int> range;
	std::string p, current_string;
	if (input.is_open())
	{
		auto i = 0;
		while (std::getline(input, p))
		{
			std::stringstream ss(p);
			while (std::getline(ss, current_string, '-'))
			{
				range.push_back(stoi(current_string, nullptr, 10));
			}
		}
		input.close();
	}
	else
	{
		std::cout << "could not open input file: " << FILE << std::endl;
	}

	
	std::vector<std::string> pswds;
	CreatePswds(range, pswds);	
	
	PurgeNonSixDigit(pswds);
	PurgeIfDecrease(pswds);
	PurgeIfNotSame(pswds);

	PrintPswds(pswds);

	return 0;
}
