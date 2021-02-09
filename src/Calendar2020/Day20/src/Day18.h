//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY18_H
#define DAY18_H


#include <cstdlib>


class Day18
{
public:
    Day18() { ReadFile(); }


private:
  
    static constexpr char const *FILENAME = "../src/Calendar2020/Day18/resources/Day18.txt";

    void ReadFile();
};


#endif