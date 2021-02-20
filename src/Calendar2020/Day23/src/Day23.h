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
    int64_t GetDestinationCup(std::vector<int64_t>& label, const int64_t currentCup);
    std::vector<int64_t> GetThreeCups(std::vector<int64_t>& label, const int64_t currentCup);
    void Rotate(std::vector<int64_t>& label, const int64_t currentCup, const int64_t curCupPos);
    void PlayTheGame_Part1(std::vector<int64_t>& label, const int64_t rounds);
    void FillCups(std::vector<int64_t>& label);
    void PlayTheGame_Part2(std::vector<int64_t>& label, const int64_t rounds);
    void PrintLabel(const std::vector<int64_t>& label);
    void PrintLabels_Part2(const std::vector<int64_t>& label);
private:

};


#endif