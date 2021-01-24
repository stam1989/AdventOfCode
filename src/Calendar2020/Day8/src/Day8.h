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
        acc, jmp, nop
    };

    using Opcodes = std::vector<std::pair<std::string, int>>;

    void ReadFile();
    void PrintOpcodes();

private:
    Opcodes m_opcodes;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day8/resources/Day8.txt";
};


#endif