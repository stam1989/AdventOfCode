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

void Operation(std::vector<int>& opcodes)
{
	for (int i = 0; i < opcodes.size(); i++)
	{
		if (opcodes[i] == 1)
		{
			opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] + opcodes[opcodes[i + 2]];
			i += 3;
		}
		else if (opcodes[i] == 2)
		{
			opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] * opcodes[opcodes[i + 2]];
			i += 3;
		}
		else if (opcodes[i] == 99)
		{
			break;
		}
	}
}

void PrintOpcodes(std::vector<int>& opcodes)
{
	for (auto& opcode : opcodes)
	{
		std::cout << opcode << ",";
	}
}

void CopyResultIntoFile(std::vector<int>& opcodes)
{
	std::string OUTPUT_FILE = "resources/Day2_output.txt";
	std::ofstream output_file(OUTPUT_FILE);
	std::ostream_iterator<int> output_iterator(output_file, ",");
	std::copy(opcodes.begin(), opcodes.end(), output_iterator);
}

int main(int argc, char* argv[])
{
    std::string FILE = "../../../resources/Day2_input.txt";

	std::ifstream input(FILE);
	std::string code;
	std::vector<int> opcodes;
	if (input.is_open())
	{
		while (std::getline(input, code, ','))
		{
			opcodes.push_back(stoi(code, nullptr, 10));
		}
		input.close();
	}
	else
	{
		std::cout << "could not open input file: " << FILE << std::endl;
	}
	std::cout << "\nvector before operation: ";
	PrintOpcodes(opcodes);

	Operation(opcodes);

	std::cout << "\nvector after operation: ";
	PrintOpcodes(opcodes);

	return 0;
}
