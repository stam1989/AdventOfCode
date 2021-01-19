//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY3_H
#define DAY3_H

#include <vector>


using Pattern = std::vector<std::vector<char>>;

class Day3
{
public:
    Day3() { ReadFile(); }

    void ReadFile();
    void PrintPattern();
    void RepeatPattern();
    Pattern LocateTrees(int16_t right, int16_t down);
    int64_t CountTrees(const Pattern& pattern);

    inline Pattern GetPattern() { return m_pattern; }

private:
    Pattern m_pattern;
    int64_t m_column, m_row;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day3/resources/Day3.txt";
};



#endif