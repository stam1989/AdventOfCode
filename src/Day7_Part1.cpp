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
#include <algorithm>
#include <array>
#include <future>
#include <exception>
#include <sstream>


enum OpCode
{
	OP_ADD = 1, // adds together numbers read from two positions and stores the result in a third position
	OP_MUL = 2, // multiplies together numbers read from two positions and stores the result in a third position
	OP_IN = 3,  // takes a single integer as input and saves it to the position given by its only parameter
	OP_OUT = 4, // outputs the value of its only parameter
	OP_JUMP_IF_TRUE = 5,  // if the first parameter is non-zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
	OP_JUMP_IF_FALSE = 6, // if the first parameter is zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
	OP_LESS_THAN = 7, // if the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter.
	OP_EQUALS = 8, // if the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
	OP_TERMINATE = 99 // the program is finished and should immediately halt
};
/// 1 == immediate mode
/// 0 == position mode


void InitializingMemory(std::string FILE, std::vector<int>& opcodes)
{
	opcodes.clear();
	std::ifstream input(FILE);
	std::string code;
	try
	{
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
			std::string exception_string =  "Could not open input file";
			throw std::runtime_error(exception_string);
		}
	}
	catch(std::string& exception_string)
	{
		std::cout << exception_string << std::endl;
	}
}


void FillWithZeros(std::vector<int>& param_modes)
{
	while (param_modes.size() < 2)
	{
		param_modes.emplace_back(0);
	}
}


int Operation(std::vector<int> opcodes, std::future<int>& f_input, int phase_setting)
{
	int res;
    int op_in_counter = 0;
// 	std::cout << "\nOperation!!\n";
	int ip = 0;
	while (ip < opcodes.size())
	{
		int opcode = opcodes[ip];
//         std::thread::id this_id = std::this_thread::get_id();
//         std::cout << "THREAD ID: " << this_id << ", Setting: " << phase_setting << ", Opcode: " << opcode << std::endl;

        int temp;
		std::vector<int> param_modes;
		opcode = opcodes[ip] % 100;
		temp = opcodes[ip] / 100;

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
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];
			opcodes[opcodes[ip + 3]] = arg1 + arg2;
			ip += 4;
			break;
		}
		case OpCode::OP_MUL:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];
			opcodes[opcodes[ip + 3]] = arg1 * arg2;
			ip += 4;
			break;
		}
		case OpCode::OP_IN:
		{
            if(op_in_counter == 0)
            {
                opcodes[opcodes[ip + 1]] = phase_setting;
            }
            else
            {
                int input = f_input.get();
                opcodes[opcodes[ip + 1]] = input;
            }

			ip += 2;
            ++op_in_counter;
			break;
		}
		case OpCode::OP_OUT:
		{
// 			std::cout << "Position " << opcodes[ip + 1] << ", num: " << opcodes[opcodes[ip + 1]] << std::endl;
			res = opcodes[opcodes[ip + 1]];
			ip += 2;
			break;
		}
		case OpCode::OP_JUMP_IF_TRUE:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];
			if (arg1 != 0)
			{
				ip = arg2;
				break;
			}
			ip += 3;
			break;
		}
		case OpCode::OP_JUMP_IF_FALSE:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];
			if (arg1 == 0)
			{
				ip = arg2;
				break;
			}
			ip += 3;
			break;
		}
		case OpCode::OP_LESS_THAN:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];

			opcodes[opcodes[ip + 3]] = (arg1 < arg2) ? 1 : 0;

			ip += 4;
			break;
		}
		case OpCode::OP_EQUALS:
		{
			int arg1, arg2;
			arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : opcodes[ip + 1];
			arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] : opcodes[ip + 2];

			opcodes[opcodes[ip + 3]] = (arg1 == arg2) ? 1 : 0;

			ip += 4;
			break;
		}
		case OpCode::OP_TERMINATE:
		{
// 			std::cout << "Terminate!!\n";
			return res;
		}
		default:
		{
            std::stringstream ss;
            ss << "wrong opcode!!!!\n ";
            ss << "OPCODE: " << opcode << "\n";
            ss << "Program counter: " << ip << "\n";
			throw std::runtime_error(ss.str());
		}
		}
	}
	return false;
}


// void PrintOpcodes(std::vector<int>& opcodes)
// {
// 	for (auto& opcode : opcodes)
// 	{
// 		std::cout << opcode << ",";
// 	}
// 	std::cout << std::endl;
// }


void StartAmplifiers(std::array<int, 5>& settings, std::vector<int>& opcodes, std::vector<int>& res)
{
// 	std::cout << "Phase Settings: " << settings[0] << ", " << settings[1] << ", " << settings[2] << ", " << settings[3] << ", "
// 	<< settings[4] << std::endl;

	try
	{
        std::promise<int> p_amp1;
        std::future<int> f1 = p_amp1.get_future();
        std::future<int> f_ampl1 = std::async(Operation, opcodes, std::ref(f1), settings[0]);
        p_amp1.set_value(0);

        std::promise<int> p_amp2;
        std::future<int> f2 = p_amp2.get_future();
        std::future<int> f_ampl2 = std::async(Operation, opcodes, std::ref(f2), settings[1]);
        p_amp2.set_value(f_ampl1.get());

        std::promise<int> p_amp3;
        std::future<int> f3 = p_amp3.get_future();
        std::future<int> f_ampl3 = std::async(Operation, opcodes, std::ref(f3),settings[2]);
        p_amp3.set_value(f_ampl2.get());

        std::promise<int> p_amp4;
        std::future<int> f4 = p_amp4.get_future();
        std::future<int> f_ampl4 = std::async(Operation, opcodes, std::ref(f4), settings[3]);
        p_amp4.set_value(f_ampl3.get());

        std::promise<int> p_amp5;
        std::future<int> f5 = p_amp5.get_future();
        std::future<int> f_ampl5 = std::async(Operation, opcodes, std::ref(f5), settings[4]);
        p_amp5.set_value(f_ampl4.get());

		res.emplace_back(f_ampl5.get());
	}
	catch(std::string e)
	{
		std::cout << e;
	}
}



int main(int argc, char* argv[])
{
	std::string FILE = "../../../resources/Day7.txt";

	std::vector<int> opcodes;

	InitializingMemory(FILE, opcodes);
	
	std::array<int, 5> settings{{0, 1, 2, 3, 4}};
	std::vector<int> res;
	do
    {
		StartAmplifiers(settings, opcodes, res);
	}
	while ( std::next_permutation(settings.begin(), settings.end()) );
	
	std::sort(res.begin(), res.end());
	std::cout << "Result is: " << res.back() <<std::endl;
	//    PrintOpcodes(opcodes);

	return 0;
}
