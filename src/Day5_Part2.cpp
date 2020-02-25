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
	OP_JUMP_IF_TRUE = 5,
	OP_JUMP_IF_FALSE = 6,
	OP_LESS_THAN = 7,
	OP_EQUALS = 8,
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

	for (auto o : opcodes)
		std::cout << o << ", ";
}

void FillWithZeros(std::vector<int>& param_modes)
{
	while (param_modes.size() < 2)
	{
		param_modes.emplace_back(0);
	}
}


bool Operation(std::vector<int>& opcodes)
{
	std::cout << "\nOperation!!\n";
	int i = 0;
	while (i < opcodes.size())
	{
		int opcode = opcodes[i];
		int temp;
		std::vector<int> param_modes;

		opcode = opcodes[i] % 100;
		temp = opcodes[i] / 100;

		while (temp)
		{
			param_modes.emplace_back(temp % 10);
			temp /= 10;
		}
		FillWithZeros(param_modes);

		switch (opcode)
		{
		case OpCode::OP_ADD:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];
			opcodes[opcodes[i + 3]] = arg1 + arg2;
			i += 4;
			break;
		}
		case OpCode::OP_MUL:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];
			opcodes[opcodes[i + 3]] = arg1 * arg2;
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
		case OpCode::OP_JUMP_IF_TRUE:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];
			if (arg1 != 0)
			{
				opcodes[i] = arg2;
				break;
			}
			i += 3;
			break;
		}
		case OpCode::OP_JUMP_IF_FALSE:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];
			if (arg1 == 0)
			{
				opcodes[i] = arg2;
				break;
			}
			i += 3;
			break;
		}
		case OpCode::OP_LESS_THAN:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];

			opcodes[opcodes[i + 3]] = (arg1 < arg2) ? 1 : 0;

			i += 4;
			break;
		}
		case OpCode::OP_EQUALS:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[i + 1]] : opcodes[i + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[i + 2]] : opcodes[i + 2];

			opcodes[opcodes[i + 3]] = (arg1 == arg2) ? 1 : 0;

			i += 4;
			break;
		}
		case OpCode::OP_TERMINATE:
		{
			std::cout << "Terminate!! \n";
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
    std::string FILE = "resources/Day5.txt";

	std::vector<int> opcodes;

	InitializingMemory(FILE, opcodes);
	Operation(opcodes);
	//    PrintOpcodes(opcodes);

	return 0;
}
