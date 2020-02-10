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


void Operation(std::vector<int>& opcodes)
{
    for (int i = 0; i < opcodes.size(); i += 4)
    {
        if (opcodes[i] == OpCode::OP_ADD)
        {
            opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] + opcodes[opcodes[i + 2]];
        }
        else if (opcodes[i] == OpCode::OP_MUL)
        {
            opcodes[opcodes[i + 3]] = opcodes[opcodes[i + 1]] * opcodes[opcodes[i + 2]];
        }
        else if (opcodes[i] == OpCode::OP_TERMINATE)
        {
            break;
        }
        else
        {
            std::cout << "Invalid Input!" << std::endl;
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
