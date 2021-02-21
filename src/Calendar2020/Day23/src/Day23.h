//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY23_H
#define DAY23_H


#include <cstdlib>
#include <vector>


class Day23
{
public:
    int32_t GetDestinationCup(std::vector<int32_t> label, const int32_t currentCup);
    std::vector<int32_t> GetThreeCups(std::vector<int32_t>& label, const int32_t currentCup);
    void Rotate(std::vector<int32_t>& label, const int32_t currentCup, const int32_t expectedCupPos);
    void PlayTheGame_Part1(std::vector<int32_t>& label, const int32_t rounds);
    void PrintLabel(const std::vector<int32_t>& label);
};


#endif