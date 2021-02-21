//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day23.h"
#include "Timer.h"


int32_t Day23::GetDestinationCup(std::vector<int32_t> label, const int32_t currentCup) {
    int32_t dest = currentCup;
    while (true) {
        dest = (dest - 1 < 0) ? *std::max_element(label.begin(), label.end()) : (dest - 1);
        auto it = std::find(label.begin(), label.end(), dest);
        if(dest != currentCup && it != label.end()) {
            return dest;
        }
    }
}


std::vector<int32_t> Day23::GetThreeCups(std::vector<int32_t>& label, const int32_t currentCup) {
    int32_t pos = std::find(label.begin(), label.end(), currentCup) - label.begin() + 1;
    std::vector<int32_t> threeCups;

    for (int32_t i = 0; i < 3; i++) {
        int ssize = label.size();
        if (pos >= ssize) pos = 0;

        threeCups.emplace_back(label[pos]);
        label.erase(std::remove(label.begin(), label.end(), label[pos]), label.end());
    }

    return threeCups;
}


void Day23::Rotate(std::vector<int32_t>& label, const int32_t currentCup, const int32_t expectedCupPos) {
    int32_t curCupPos = std::find(label.begin(), label.end(), currentCup) - label.begin();
    int32_t diff = curCupPos - expectedCupPos;
    if (diff == 0) return;
    else if (diff < 0) std::rotate(label.rbegin(), label.rbegin() + abs(diff), label.rend());
    else std::rotate(label.begin(), label.begin() + abs(diff), label.end());
}


void Day23::PlayTheGame_Part1(std::vector<int32_t>& label, const int32_t rounds) {
    int32_t curCupPos = 0;
    for(int i = 0; i < rounds; i++) {
        std::vector<int32_t> temp_label(label);
        int32_t currentCup = label[curCupPos];
        std::vector<int32_t> threeCups = GetThreeCups(temp_label, currentCup);
        int32_t destCup = GetDestinationCup(temp_label, currentCup);
        auto it_dest = std::find(temp_label.begin(), temp_label.end(), destCup);
        if (it_dest == temp_label.end()) throw std::out_of_range("Day23::PlayTheGame:: destination position out of range...");
        temp_label.insert(it_dest + 1, threeCups.begin(), threeCups.end());

        Rotate(temp_label, currentCup, curCupPos);

        label = temp_label;

        curCupPos = (curCupPos == label.size() - 1) ? 0 : (curCupPos + 1);
    }
}


void Day23::PrintLabel(const std::vector<int32_t>& label) {
    for (const auto cup : label) std::cout << cup;
    std::cout << "\n";
}


int main() {
    Day23 d;
    std::vector<int32_t> label;

    std::string str("653427918");

    for (const char c : str) {
        label.emplace_back(static_cast<int32_t>(c) - '0');
    }

    {
        Timer t;
        d.PlayTheGame_Part1(label, 100);
        std::cout << "Final state of cups is: ";
        d.PrintLabel(label);
    }
    
    return 0;
}