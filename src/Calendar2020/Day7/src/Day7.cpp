//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day7.h"

#include <fstream>
#include <iostream>
#include <sstream>


void Day7::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        std::string contain_del("contain");
        while (std::getline(inputFile, s_input))
        {
            std::string key(s_input.substr(0, s_input.find(contain_del) - 1));
            GetBagType(key);

            s_input.erase(0, s_input.find(contain_del) + contain_del.size() + 1);
            std::map<std::string, int> value_elements;
            GetContents(s_input, value_elements);
            
            m_rules.insert({key, value_elements});
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day7::GetContents(std::string& rhs_str, std::map<std::string, int>& value_elements)
{
    std::string space_del(" ");
    std::string comma_del(", ");
    while(!rhs_str.empty())
    {
        size_t commaDel_pos = rhs_str.find(comma_del);
        std::string temp_str;

        if(commaDel_pos == std::string::npos)
        {
            // handle the case that it is the last bag contained
            temp_str = rhs_str;
            rhs_str.clear();
        }
        else
        {
            // get the first bag which is contained and erase it from the str
            temp_str = (rhs_str.substr(0, commaDel_pos));
            rhs_str.erase(0, rhs_str.find(comma_del) + comma_del.size());
        }

        // here we handle the case that element contains no other bags
        int el_count = 0;
        std::string hasNum(temp_str.substr(0, temp_str.find(space_del)));
        if(hasNum != "no")
        {
            el_count = stol(hasNum);
        }

        temp_str.erase(0, temp_str.find(space_del) + space_del.size());
        GetBagType(temp_str);
        value_elements.insert({temp_str, el_count});
    }
}


void Day7::GetBagType(std::string& s)
{
    const auto pos = s.find_last_of(" \t\n"); 
    s = s.substr(0, pos);
}



void Day7::PrintRules()
{
    for(const auto& rule : m_rules)
    {
        std::cout << rule.first << " bags contain ";
        for (const auto& r : rule.second)
        {
            std::cout << r.second << " " << r.first << " bags, ";
        }
        std::cout << "\n";
    }

}


bool Day7::Search(const std::map<std::string, int>& rule, const std::string& bagColor, int& count)
{
    bool res = false;
    for(const auto& r : rule)
    {
        // case that bag contains no other bags
        if (r.first == "other")
        {
            return false;
        }

        // bag color is contained, so increment count and return true
        if (r.first == bagColor)
        {
            count++;
            return true;
        }
        // else search if this element contains my bag
        else
        {
           if(SeachIfContainsMyBag(bagColor, r.first, count))
           {
               return true;
           }
        }
    }

    return res;
}


bool Day7::SeachIfContainsMyBag(const std::string& bagColor, const std::string& bagColorToSearchIn, int& count)
{
    auto it = m_rules.find(bagColorToSearchIn);
    if (it != m_rules.end())
    {
        return Search(it->second, bagColor, count);
    }
    else
    {
        return false;
    }
}


int Day7::CountDifferentColors(const std::string& bagColor)
{
    int count = 0;
    for (const auto& rule : m_rules)
    {
        Search(rule.second, bagColor, count);
    }

    return count;
}


int Day7::CountIndividualBags(const std::string& bagColor)
{
    int count = 0;
    auto it = m_rules.find(bagColor);
    if (it != m_rules.end())
    {
        for (const auto& rule : it->second)
        {
            if (rule.first == "other")
            {
                return 0;
            }

            count += rule.second * CountIndividualBags(rule.first) + rule.second;
        }
    }
    
    return count;
}


int main()
{
    Day7 d;

    // d.PrintRules();
    std::cout << d.CountDifferentColors("shiny gold") << " bag colors can eventually contain at least one shiny gold bag!\n";

    std::cout << d.CountIndividualBags("shiny gold") << " individual bags are required inside my single shiny gold bag!\n";

    return 0;
}