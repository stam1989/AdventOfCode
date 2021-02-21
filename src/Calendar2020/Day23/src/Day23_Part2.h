//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY23_PART2_H
#define DAY23_PART2_H


#include <cstdlib>
#include <vector>
#include <memory>
#include <unordered_map>

class Day23_Part2
{
public:
    void FillCups(const std::string& label);
    void PlayTheGame_Part2(const std::string& label, const int32_t rounds);

    struct MyLinkedList {
    public:
        MyLinkedList(int32_t v) : value{v}, next{nullptr} {}
        int32_t value;
       std::shared_ptr<MyLinkedList> next;
    };
private:
    std::unordered_map<int32_t, std::shared_ptr<MyLinkedList>> cups;
    std::shared_ptr<MyLinkedList> firstCup;
    std::shared_ptr<MyLinkedList> currentCup;
    std::shared_ptr<MyLinkedList> one;
};

#endif