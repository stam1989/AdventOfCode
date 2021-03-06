//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef INTCODE_H
#define INTCODE_H

#include <cstdint>
#include <vector>

class IntcodeProgram
{
public:

    IntcodeProgram(const char* filename) { InitializeMemory(filename); }
    virtual ~IntcodeProgram() = default;

    enum OpCode
    {
        OP_ADD = 1, // adds together numbers read from two positions and stores the result in a third position
        OP_MUL = 2, // multiplies together numbers read from two positions and stores the result in a third position
        OP_IN = 3,  // takes a single integer as input and saves it to the position given by its only parameter
        OP_OUT = 4, // outputs the value of its only parameter
        OP_JUMP_IF_TRUE = 5,  // if the first parameter is non-zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
        OP_JUMP_IF_FALSE = 6, // if the first parameter is zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
        OP_LESS_THAN = 7, // if the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
        OP_EQUALS = 8, // if the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
        OP_REL_MODE = 9, //adjusts the relative base by the value of its only parameter. The relative base increases (or decreases, if the value is negative) by the value of the parameter.
        OP_TERMINATE = 99 // the program is finished and should immediately halt
    };
    /// 2 == relative mode
    /// 1 == immediate mode
    /// 0 == position mode

    void PrintOpcodes();

    void InitializeMemory(const char* filename);

    void Operation();

    inline std::vector<int64_t>& GetOpcodes() { return m_opcodes; }

private:

    void FillWithZeros(std::vector<int>& param_modes);

    void SetMode(std::vector<int>& param_modes, int64_t& opcode, const int64_t ip);

    void SetArgs(int64_t &arg1, int64_t& arg2, const int64_t& ip, std::vector<int>& param_modes, int64_t& relative_base);

    void CheckPosition(const int64_t pos);

    virtual int64_t OpInput() = 0;

    virtual bool OpOutput(int64_t output)  = 0;

    std::vector<int64_t> m_opcodes;
};

#endif
