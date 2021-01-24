//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY7_H
#define DAY7_H


#include <map>
#include <string>

using Rules = std::map<std::string, std::map<std::string, int>>;

class Day7
{
public:
    Day7() { ReadFile(); }

    void ReadFile();
    void PrintRules();
    int CountDifferentColors(const std::string& bagColor);
    int CountIndividualBags(const std::string& bagColor);

private:
    Rules m_rules;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day7/resources/Day7.txt";

    bool SeachIfContainsMyBag(const std::string& bagColor, const std::string& bagColorToSearchIn, int& count);
    bool Search(const std::map<std::string, int>& rule, const std::string& bagColor, int& count);
    void GetBagType(std::string& s);
    void GetContents(std::string& rhs_str, std::map<std::string, int>& value_elements);
};


#endif