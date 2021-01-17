//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY2_H
#define DAY2_H

#include <vector>
#include <cstdint>

class Day2
{
public:

    struct Input
    {
        uint8_t min, max;
        char element;
        std::string password;
    };

    using PasswordList = std::vector<Input>;
    
    void ReadFile()
    bool IsValid();

private:
    PasswordList inputs;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day2/resources/Day2.txt";
};


#endif