//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day8.h"

#include <fstream>
#include <iostream>
#include <sstream>

void Day8::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            std::istringstream ss(s_input);
            std::string opcode;
            int step;
            ss >> opcode;
            ss >> step;
            m_instructions.emplace_back(StringToOpcode(opcode), step);
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


Day8::Opcode Day8::StringToOpcode(const std::string& op)
{
    if(op == "acc")
    {
        return Opcode::ACC;
    }
    else if(op == "jmp")
    {
        return Opcode::JMP;
    }
    else if(op == "nop")
    {
        return Opcode::NOP;
    }
    else
    {
        throw std::invalid_argument("GetOpcode:: Invalid opcode...");
    }
}


std::string Day8::OpcodeToString(const Opcode& op)
{
    if(op == Opcode::ACC)
    {
        return "acc";
    }
    else if(op == Opcode::JMP)
    {
        return "jmp";
    }
    else if(op == Opcode::NOP)
    {
        return "nop";
    }
    else
    {
        throw std::invalid_argument("GetOpcode:: Invalid opcode...");
    }
}


void Day8::PrintOpcodes()
{
    for (const auto& inst : m_instructions)
    {
        std::cout << OpcodeToString(inst.op) << ": " << inst.step << "\n";
    }
}


bool Day8::Operation(int& accumulator, Instructions instructions)
{
    int ip = 0;
    while (1)
    {
        if(instructions[ip].isVisited == true)
        {
            return false;
        }
        if(ip >= instructions.size())
        {
            return true;
        }

        instructions[ip].isVisited = true;

        switch (instructions[ip].op)
        {
        case Opcode::ACC:
            accumulator += instructions[ip].step;
            ip++;
            break;
        case Opcode::JMP:
            ip += instructions[ip].step;
            break;
        case Opcode::NOP:
            ip++;
            break;
        default:
            throw std::invalid_argument("Operation:: Invalid opcode...");
            break;
        }
    }   
}


Day8::Instructions Day8::ChangeInstruction(int& ip)
{
    Instructions res_instructions(m_instructions);

    for (int i = ip; i < res_instructions.size(); i++)
    {
        if (res_instructions[i].op == Opcode::JMP)
        {
            res_instructions[i].op = Opcode::NOP;
            ip++;
            return res_instructions;
        }
        else if (res_instructions[i].op == Opcode::NOP && res_instructions[i].step != 0)
        {
            res_instructions[i].op = Opcode::JMP;
            ip++;
            return res_instructions;
        }

    }
}



int main()
{
    Day8 d;

    // d.PrintOpcodes();
    int acc = 0;
    auto instr = d.GetInstructions();
    d.Operation(acc, instr);
    std::cout << "The value in the accumulator is: " << acc << "\n";

    int ip = 0;
    while (!d.Operation(acc, instr))
    {
        acc = 0;
        instr = d.ChangeInstruction(ip);
    } 
    std::cout << "The value in the accumulator after the change is: " << acc << "\n";
    

    return 0;
}