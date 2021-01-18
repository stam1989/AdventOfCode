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
#include <string>
#include <cstdint>

class Day2
{
public:

    Day2() { ReadFile(); }

    struct Input
    {
        int min, max;
        std::string password;
        char element;
    };

    enum class Method
    {
        FIRST = 1,
        SECOND = 2
    };

    using PasswordList = std::vector<Input>;
    
    void ReadFile();
    void PrintInputs();
    Input Decode(std::string& s_input);
    bool IsValidFirstMethod(const Input& input);
    bool IsValidSecondMethod(const Input& input);
    int CountValidPasswords(Method m);
private:
    PasswordList v_inputs;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day2/resources/Day2.txt";
};


#endif