//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY15_H
#define DAY15_H

#include <cstdlib>
#include <unordered_map>

class Day15
{
public:
    struct Number {
        Number(int64_t t, int64_t v) : turn(t), value(v) {}
        int64_t turn, value;

        bool operator==(const Number& n) {
            return n.turn == turn && n.value == value;
        }

    };

    int64_t PlayWithMap(const int64_t rounds);
    void PrintMap();
    
private:
    std::unordered_map<int64_t, int64_t> m_mapNumbers;
};


#endif