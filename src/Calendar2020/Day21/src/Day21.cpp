//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day21.h"
#include "Timer.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>


void Day21::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, s_input)) {
            auto allergens_pos = s_input.find("(");
            if (allergens_pos == std::string::npos) throw(std::runtime_error("ReadFile:: Parsing error..."));
            std::istringstream ss_ingrs(s_input.substr(0, allergens_pos));
            s_input.erase(0, allergens_pos);
            std::string ingr;
            std::set<std::string> ingrs;
            while(ss_ingrs >> ingr) {
                ingrs.emplace(ingr);
                m_foods.emplace_back(ingr);
            }
            // std::regex r("/[A-Za-z0-9]+(['_-]?[A-Za-z0-9]+)?/g");
            // std::smatch match_allergen;
            // if (std::regex_match(s_input, match_allergen, r)) {
            //     for(const auto allergen : match_allergen) {
            //         auto it_atf = m_atf.find(allergen);
            //         if (it_atf == m_atf.end()) m_atf[allergen] = ingrs;
            //         else {
            //             std::set<std::string> temp_ingrs;
            //             std::set_intersection(it_atf->second.begin(), it_atf->second.end(),
            //                                   ingrs.begin(), ingrs.end(),
            //                                   std::inserter(temp_ingrs, temp_ingrs.begin()));
            //             m_atf[allergen] = temp_ingrs;
            //         }
            //     }
            // }

            s_input.erase(std::remove_if(s_input.begin(), s_input.end(), [](char c) { return (c == ')' || c == ','); }), s_input.end());
            std::string allergen;
            std::istringstream ss_allergens(s_input.substr(s_input.find(" "), s_input.size()));
            while(ss_allergens >> allergen) {
                auto it_atf = m_atf.find(allergen);
                    if (it_atf == m_atf.end()) m_atf[allergen] = ingrs;
                    else {
                        std::set<std::string> temp_ingrs;
                        std::set_intersection(it_atf->second.begin(), it_atf->second.end(),
                                              ingrs.begin(), ingrs.end(),
                                              std::inserter(temp_ingrs, temp_ingrs.begin()));
                        m_atf[allergen] = temp_ingrs;
                    }
            }

        }
        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day21::PrintMap() {
    for (const auto& atf : m_atf) {
        std::cout << "\nAllergen: " << atf.first << " contains ";
        for (const auto& f : atf.second) {
            std::cout << f << ", ";
        }
    }

    std::cout << "\n";
}


bool Day21::AreAllergensMatched() {
    for (const auto atf : m_atf) {
        if (atf.second.size() != 1) return false;
    }

    return true;
}


void Day21::FindAllergens() {
    while (!AreAllergensMatched()) {
        auto temp_atf(m_atf);
        for (const auto& tatf : temp_atf) {
            if (tatf.second.size() == 1) {
                std::string s(*tatf.second.begin());
                std::for_each(m_atf.begin(), m_atf.end(), [&s](auto& t) { if(t.second.size()!=1) t.second.erase(s); });
            }
        }
    }
}


int32_t Day21::CountFoodsWithoutAllergens() {
    std::set<std::string> all_allergens;
    for (const auto& atf : m_atf) {
        all_allergens.insert(atf.second.begin(), atf.second.end());
    }

    for (const auto& a : all_allergens) {
        m_foods.erase(std::remove(m_foods.begin(), m_foods.end(), a), m_foods.end());
    }

    return m_foods.size();
}


void Day21::MakeIngredientList() {
    FindAllergens();
    std::string myList;
    for (const auto& atf : m_atf) {
        std::for_each(atf.second.begin(), atf.second.end(), [&myList](std::string f) { myList.append(f); myList.append(","); });
    }

    std::cout << "My list is:\n" << myList << "\n"; 
}


int main() {
    Day21 d;
    // d.PrintMap();
    {
        Timer t;
        std::cout << "Foods without allergens used " << d.CountFoodsWithoutAllergens() << " times!\n";
    }

    {
        Timer t;
        d.MakeIngredientList();
    }
    
    return 0;
}