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
#include <exception>
#include <sstream>
#include <map>

#include <thread>
#include <mutex>
#include <chrono>
#include <future>

std::mutex mu;
std::condition_variable cond_amp;

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

void SetMode(std::vector<int>& opcodes, std::vector<int>& param_modes, int& opcode, int ip)
{
	int temp;
	opcode = opcodes[ip] % 100;
	temp = opcodes[ip] / 100;
	
	while (temp)
	{
		param_modes.emplace_back(temp % 10);
		temp /= 10;
	}
}

void Operation(std::vector<int> opcodes, std::map<int, int>&  thread_data, int phase_setting, int thread_id, int& res)
{
	int op_in_counter = 0;
	int ip = 0;
	bool cont = true;
	while (ip < opcodes.size() && cont)
	{
		int opcode = opcodes[ip];
		std::vector<int> param_modes;		
		SetMode(opcodes, param_modes, opcode, ip);
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
					std::unique_lock<std::mutex> locker(mu);
					while(thread_data.find(thread_id) == thread_data.end())
					{
						cond_amp.wait(locker);
					}
					opcodes[opcodes[ip + 1]] = thread_data.find(thread_id)->second;
					thread_data.erase(thread_id);
				}
				
				ip += 2;
				++op_in_counter;
				break;
			}
			case OpCode::OP_OUT:
			{
				std::unique_lock<std::mutex> locker(mu);
				
				int id = (thread_id == 4) ? 0 : (thread_id + 1);
				res = opcodes[opcodes[ip + 1]];
				thread_data.emplace(id, res);
				cond_amp.notify_all();
				std::this_thread::sleep_for(std::chrono::microseconds(50));
				
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
				cont = false;
				break;
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
}


// void PrintOpcodes(std::vector<int>& opcodes)
// {
// 	for (auto& opcode : opcodes)
// 	{
// 		std::cout << opcode << ",";
// 	}
// 	std::cout << std::endl;
// }


void StartAmplifiers(std::array<int, 5>& settings, std::vector<int>& opcodes, std::vector<int>& results)
{
	// 	std::cout << "Phase Settings: " << settings[0] << ", " << settings[1] << ", " << settings[2] << ", " << settings[3] << ", "
	// 	<< settings[4] << std::endl;
	int res;
	try
	{
		std::map<int, int> thread_data;  // a map from amplifier id to its data
		thread_data[0] = 0;
		std::thread t1(Operation, opcodes, std::ref(thread_data), settings[0], 0, std::ref(res));
		std::thread t2(Operation, opcodes, std::ref(thread_data), settings[1], 1, std::ref(res));
		std::thread t3(Operation, opcodes, std::ref(thread_data), settings[2], 2, std::ref(res));
		std::thread t4(Operation, opcodes, std::ref(thread_data), settings[3], 3, std::ref(res));
		std::thread t5(Operation, opcodes, std::ref(thread_data), settings[4], 4, std::ref(res));
		
		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
	}
	catch(std::string e)
	{
		std::cout << e;
	}
	results.emplace_back(res);
}



int main(int argc, char* argv[])
{
	std::string FILE = "../../../resources/Day7.txt";
	
	std::vector<int> opcodes;
	
	InitializingMemory(FILE, opcodes);
	
	std::vector<int> results;
	std::array<int, 5> settings{{5, 6, 7, 8, 9}};
	do
	{
		StartAmplifiers(settings, opcodes, results);
	}
	while ( std::next_permutation(settings.begin(), settings.end()) );
	
		std::sort(results.begin(), results.end());
		std::cout << "Result is: " << results.back() <<std::endl;
	//    PrintOpcodes(opcodes);
	
	return 0;
}

