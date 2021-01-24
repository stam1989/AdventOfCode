//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY6_H
#define DAY6_H

#include <set>
#include <vector>

using Groups = std::vector<std::set<char>>;

class Day6
{
public:
    void ReadFile();
    void PrintGroups();
    int32_t SumCounts();
    void ReadFilePart2();

private:
    Groups m_groups;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day6/resources/Day6.txt";
};



#endif