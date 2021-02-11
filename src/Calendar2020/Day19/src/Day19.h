//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY19_H
#define DAY19_H


#include <cstdlib>
#include <vector>
#include <map>

using Rule = std::vector<int16_t>;

class Day19
{
public:
    Day19() { ReadFile(); }

    void PrintResolved();
    void PrintUnresolved();
    int16_t CountValidMessages(int16_t id);

private:
    std::map<int16_t, std::string> m_resolved;
    std::map<int16_t, std::vector<Rule>> m_unresolved;
    std::vector<std::string> m_validMessages;
    std::vector<std::string> m_inputMessages;

    static constexpr char const *FILENAME = "../src/Calendar2020/Day19/resources/Day19.txt";

    void ReadFile();
    void DecodeRule(std::string& input, std::vector<Rule>& rules);
};


#endif