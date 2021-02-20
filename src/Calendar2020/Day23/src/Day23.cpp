//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day23.h"
#include "Timer.h"


int64_t Day23::GetDestinationCup(std::vector<int64_t>& label, const int64_t currentCup) {
    int64_t dest = currentCup;

    while (true) {
        dest = (dest - 1 < 0) ? *std::max_element(label.begin(), label.end()) : (dest - 1);
        auto it = std::find(label.begin(), label.end(), dest);
        if(dest != currentCup && it != label.end()) {
            return dest;
        }
    }
}


std::vector<int64_t> Day23::GetThreeCups(std::vector<int64_t>& label, const int64_t currentCup) {
    int64_t pos = std::find(label.begin(), label.end(), currentCup) - label.begin() + 1;
    std::vector<int64_t> threeCups;

    for (int64_t i = 0; i < 3; i++) {
        int ssize = label.size();
        if (pos >= ssize) pos = 0;

        threeCups.emplace_back(label[pos]);
        label.erase(std::remove(label.begin(), label.end(), label[pos]), label.end());
    }

    return threeCups;
}


void Day23::Rotate(std::vector<int64_t>& label, const int64_t currentCup, const int64_t curCupPos) {
    while(label[curCupPos] != currentCup) {
        std::rotate(label.rbegin(), label.rbegin() + 1, label.rend());
    }
}


void Day23::PlayTheGame_Part1(std::vector<int64_t>& label, const int64_t rounds) {
    int64_t curCupPos = 0;
    for(int i = 0; i < rounds; i++) {
        std::vector<int64_t> temp_label(label);
        int64_t currentCup = label[curCupPos];
        std::vector<int64_t> threeCups = GetThreeCups(temp_label, currentCup);
        int64_t destCup = GetDestinationCup(temp_label, currentCup);
        auto it_destPos = std::find(temp_label.begin(), temp_label.end(), destCup);
        if (it_destPos == temp_label.end()) throw std::out_of_range("Day23::PlayTheGame:: destination position out of range...");
        temp_label.insert(it_destPos + 1, threeCups.begin(), threeCups.end());

        Rotate(temp_label, currentCup, curCupPos);

        label = temp_label;

        curCupPos = (curCupPos == label.size() - 1) ? 0 : (curCupPos + 1);
    }
}


void Day23::FillCups(std::vector<int64_t>& label) {
    int64_t max = *std::max_element(label.begin(), label.end());

    for (int64_t i = max + 1; i < 1000001; i++) {
        label.emplace_back(i);
    }

}

void Day23::PlayTheGame_Part2(std::vector<int64_t>& label, const int64_t rounds) {
    FillCups(label);
    PlayTheGame_Part1(label, rounds);
}


void Day23::PrintLabel(const std::vector<int64_t>& label) {
    for (const auto cup : label) std::cout << cup;
    std::cout << "\n";
}


void Day23::PrintLabels_Part2(const std::vector<int64_t>& label) {
    auto it = std::find(label.begin(), label.end(), 1);
    int64_t res = *(it + 1) * *(it + 2);
    std::cout << "The multiple of the elements is " << res << "!\n";
}

int main() {
    Day23 d;
    std::vector<int64_t> label;

    std::string str("653427918");

    for (const char c : str) {
        label.emplace_back(static_cast<int64_t>(c) - '0');
    }

    // {
    //     Timer t;
    //     d.PlayTheGame_Part1(label, 100);
    //     std::cout << "Final state of cups is: ";
    //     d.PrintLabel(label);
    // }

    {
        Timer t;
        d.PlayTheGame_Part2(label, 10000000);
        d.PrintLabels_Part2(label);
    }
    
    return 0;
}