//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day23_Part2.h"
#include "Timer.h"


void Day23_Part2::FillCups(const std::string& label) {
    for (int i = 0; i < label.size(); i++) {
        int32_t num = int32_t(label[i]) - '0';
        auto node{std::make_shared<MyLinkedList>(num)};

        if (i == 0) {
            firstCup = node;
            currentCup = firstCup;
        }
        else
        {
            currentCup->next = node;
            currentCup = currentCup->next;
        }

        cups[num] = node;

        if(num == 1) one = node;
    }

    for(int i = 10; i <= 1000000; i++)
    {
        auto node(std::make_shared<MyLinkedList>(i));
        cups[i] = node;
        currentCup->next = node;
        currentCup = currentCup->next;
    }

    currentCup->next = firstCup;
    currentCup = firstCup;

}

void Day23_Part2::PlayTheGame_Part2(const std::string& label, const int32_t rounds) {
    FillCups(label);
    for(int i = 0; i < rounds; i++)
    {
        std::shared_ptr<MyLinkedList> removed = currentCup->next;
        currentCup->next = currentCup->next->next->next->next;

        int32_t destNumber = currentCup->value == 1 ? cups.size() : currentCup->value - 1;
        while(removed->value == destNumber || removed->next->value == destNumber || removed->next->next->value == destNumber)
        {
            destNumber--;
            if(destNumber == 0) destNumber = cups.size();
        }

        std::shared_ptr<MyLinkedList> insertNode = cups[destNumber];
        removed->next->next->next = insertNode->next;
        insertNode->next = removed;

        currentCup = currentCup->next;
    }
    
    currentCup = one;
    int64_t num1 = currentCup->next->value;
    int64_t num2 = currentCup->next->next->value;
    std::cout << "The result is: " << (num1 * num2) << "!\n";
}


int main() {
    Day23_Part2 d;

    std::string label("653427918");


    {
        Timer t;
        d.PlayTheGame_Part2(label, 10000000);
    }
    
    return 0;
}