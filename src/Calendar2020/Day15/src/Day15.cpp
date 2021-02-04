//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day15.h"
#include "Timer.h"

#include <string>
#include <algorithm>


void Day15::PrintMap() {
    for (const auto& n : m_mapNumbers) {
        std::cout << "Turn " << n.second << ": " << n.first << "\n";
    }
}


int64_t Day15::PlayWithMap(const int64_t rounds) {
    // m_mapNumbers = {{0, 1}, {3, 2}, {6, 3}};
    // m_mapNumbers = {{1, 1}, {3, 2}, {2, 3}};

    m_mapNumbers = {{17, 1}, {1, 2}, {3, 3}, {16, 4}, {19, 5}, {0, 6}};
    
    int64_t i = m_mapNumbers.size();
    bool isSpoken = false;
    int64_t lastPos = 0;
    while(i < rounds) {
        i++;
        
        int64_t newValue = 0;
        if (isSpoken) {
            newValue = i - 1 - lastPos;
        }

        auto it = m_mapNumbers.find(newValue);
        if (it != m_mapNumbers.end()) {
            isSpoken = true;
            lastPos = it->second;
            m_mapNumbers[newValue] = i;
        }
        else {
            m_mapNumbers[newValue] = i;
            isSpoken = false;    
        }
    }

    auto res_it = std::find_if(m_mapNumbers.begin(), m_mapNumbers.end(), [rounds](const auto& n) { return n.second == rounds; });
    return res_it->first;
}


int main() {
    Day15 d;
    {
        Timer t;
        std::cout << "The 2020th number spoken is: " << d.PlayWithMap(2020) << "!\n";
    }

    {
        Timer t;
        std::cout << "The 2020th number spoken is: " << d.PlayWithMap(30000000) << "!\n";
    }

    return 0;
}