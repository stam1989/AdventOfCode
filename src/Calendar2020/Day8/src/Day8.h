//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY8_H
#define DAY8_H

#include <vector>
#include <string>


class Day8
{
public:
    Day8() { ReadFile(); }

    enum class Opcode
    {
        ACC,    // increases or decreases a single global value called the accumulator by the value given in the argument
        JMP,    // jumps to a new instruction relative to itself. The next instruction to execute is found using the argument as an offset from the jmp instruction
        NOP     // stands for No OPeration - it does nothing. The instruction immediately below it is executed next.
    };


    struct Instruction
    {
        Instruction(Opcode o, int s) : op(o), step(s), isVisited(false) {}

        Opcode op;
        int step;
        bool isVisited;
    };


    using Instructions = std::vector<Instruction>;

    void PrintOpcodes();
    bool Operation(int& accumulator, Instructions instructions);
    Instructions ChangeInstruction(int& ip);

    inline Instructions GetInstructions() { return m_instructions; }

private:
    Instructions m_instructions;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day8/resources/Day8.txt";

    void ReadFile();
    Opcode StringToOpcode(const std::string& op);
    std::string OpcodeToString(const Opcode& op);
};


#endif