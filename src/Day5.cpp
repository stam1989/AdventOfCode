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

enum OpCode
{
	OP_ADD = 1,
	OP_MUL = 2,
	OP_IN = 3,
	OP_OUT = 4,
	OP_TERMINATE = 99
};

void InitializingMemory(std::string FILE, std::vector<int>& opcodes)
{
	opcodes.clear();
	std::ifstream input(FILE);
	std::string code;
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
}

bool Operation(std::vector<int>& opcodes)
{
	std::cout << "\noperation!!\n";
	std::cout << "opcodes[2]: " << opcodes[2] % 100;
	int i = 0;
	while (i < opcodes.size())
	{
		int opcode = opcodes[i] % 100;
		
		switch (opcode)
		{
		case OpCode::OP_ADD:
		{

			opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] + opcodes[opcodes[i + 2]];
			i += 4;
			break;
		}
		case OpCode::OP_MUL:
		{
			opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] * opcodes[opcodes[i + 2]];
			i += 4;
			break;
		}
		case OpCode::OP_IN:
		{
			int temp;
			std::cout << "Give an int:";
			std::cin >> temp;
			opcodes[opcodes[i + 1]] = temp;
			i += 2;
			break;
		}
		case OpCode::OP_OUT:
		{
			std::cout << "Position " << opcodes[i + 1] << ", num: " << opcodes[opcodes[i + 1]] << std::endl;
			i += 2;
			break;
		}
		case OpCode::OP_TERMINATE:
		{
			std::cout << "terminate!! \n";
			return true;
		}
		default:
		{
			std::cout << "wrong opcode!!!! \n";
			return false;
		}
		}

	}
}

void PrintOpcodes(std::vector<int>& opcodes)
{
	for (auto& opcode : opcodes)
	{
		std::cout << opcode << ",";
	}
	std::cout << std::endl;
}


int main(int argc, char* argv[])
{
	std::string FILE = "C:\Users\stam1989\source\repos\AdventOfCode\resources\Day5.txt";

	std::vector<int> opcodes;

	//    for (int noun = 0; noun < 100; noun++)
	//    {
	//        for (int verb = 0; verb < 100; verb++)
	//        {
	InitializingMemory(FILE, opcodes);
	Operation(opcodes);
	//            if (opcodes[0] == 19690720)
	//            {
	//                std::cout << "Result is: " << 100 * noun + verb << std::endl;
	//                break;
	//            }
	//        }
	//    }

	return 0;
}
