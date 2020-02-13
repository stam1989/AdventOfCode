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
    OP_TERMINATE = 99
};

void Reset(std::string FILE, std::vector<int>& opcodes)
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

bool Operation(std::vector<int>& opcodes, int noun, int verb)
{

    opcodes[1] = noun;
    opcodes[2] = verb;
    for (int i = 0; i < opcodes.size(); i += 4)
    {
        switch(opcodes[i])
        {
            case OpCode::OP_ADD :
            {
                opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] + opcodes[opcodes[i + 2]];
                break;
            }
            case OpCode::OP_MUL :
            {
                opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] * opcodes[opcodes[i + 2]];
                break;
            }
            case OpCode::OP_TERMINATE :
            {
                return true;
            }
            default :
            {
                std::cout << "Invalid opcode: " << opcodes[i] << std::endl;
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
    std::string FILE = "/home/neo/workspace/Adventofcode/resources/Day2_input.txt";

    std::vector<int> opcodes;

    for (int noun = 0; noun < 100; noun++)
    {
        for (int verb = 0; verb < 100; verb++)
        {
            Reset(FILE, opcodes);
            Operation(opcodes, noun, verb);
            if (opcodes[0] == 19690720)
            {
                std::cout << "Result is: " << 100 * noun + verb << std::endl;
                break;
            }
        }
    }

    return 0;
}
