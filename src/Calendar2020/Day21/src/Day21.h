//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY21_H
#define DAY21_H


#include <cstdlib>
#include <map>
#include <vector>
#include <set>

using AllergenToFoods = std::map<std::string, std::set<std::string>>;

class Day21
{
public:
    Day21() { ReadFile(); }

    void PrintMap();
    int32_t CountFoodsWithoutAllergens();
    void MakeIngredientList();
private:
    AllergenToFoods m_atf;
    std::vector<std::string> m_foods;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day21/resources/Day21.txt";

    void ReadFile();
    void FindAllergens();
    bool AreAllergensMatched();
};


#endif