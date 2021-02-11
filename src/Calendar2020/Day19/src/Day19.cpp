//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day19.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>
#include <set>


void Day19::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, s_input)) {
            if(s_input.empty()) {
                while (std::getline(inputFile, s_input)) {
                    m_inputMessages.emplace_back(s_input);
                }
            }

            auto colonPos = s_input.find(':');
            int16_t id = stol(s_input.substr(0, colonPos));
            s_input.erase(0, colonPos + 2);
            auto charPos = s_input.find('"');
            if (charPos != std::string::npos) {
                m_resolved[id] = s_input[1];
            }
            else {
                std::vector<Rule> v_rules;
                DecodeRule(s_input, v_rules);
                m_unresolved[id] = v_rules;
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


void Day19::DecodeRule(std::string& input, std::vector<Rule>& rules) {
    while (!input.empty()) {
        auto pos = input.find('|');
        Rule v_rule;

        if (pos == std::string::npos) {
            for (const auto c : input) {
                if (c != ' ') v_rule.emplace_back(c - '0');
            }
            rules.emplace_back(v_rule);
            return;
        }
        else {
            std::string str = input.substr(0, pos - 1);
            DecodeRule(str, rules);
            input.erase(0, pos + 2);    
        }
    }
}


void Day19::PrintResolved() {
    std::cout << "\nResolved:\n";
    for (const auto& r : m_resolved) {
        std::cout << r.first << ": " << r.second << "\n";
    }
}


void Day19::PrintUnresolved() {
    std::cout << "\nUnresolved:\n";
    for (const auto& ur : m_unresolved) {
        std::cout << ur.first << ": ";
        for (const auto& rules : ur.second) {
            for (const auto rule : rules) {
                std::cout << rule << " "; 
            }
            std::cout << "| ";
        }
        std::cout << "\n";
    }
}


std::string Day19::GetMessage(int16_t id) {
    if (m_resolved.find(id) != m_resolved.end()) {
        return m_resolved[id];
    }
    auto ruleOptions = m_unresolved[id];

    std::string final;
    for (auto option : ruleOptions) {
        std::string strOps;
        for (auto rule : option) {
            std::string subOps = GetMessage(rule);

            if (strOps.empty()) strOps = subOps;
            else {
                std::string combined;
                for (auto s : subOps) {
                    for (auto op : strOps) {
                        combined.push_back(op);
                        combined.push_back(s);
                    }
                }
                strOps = combined;
            }
        }
        final.append(strOps);
    }
    m_validMessages.emplace_back(final);

    m_resolved[id] = final;

    return final;
}


int16_t Day19::CountValidMessages(int16_t id) {
    auto allPossiblities = GetMessage(id);
    std::set<std::string> allSet;
    for (auto a : allPossiblities)
        allSet.emplace(a);

    // auto count = 0;
    // for (auto msg : msgs)
    //     if msg in allSet:
    //         count += 1
    // print(count)

    return m_validMessages.size();
}


int main() {
    Day19 d;
    d.PrintResolved();
    d.PrintUnresolved();
    {
        Timer t;
        auto count = d.CountValidMessages(0);
        std::cout << "Valid Messages count for rule 0 are: " << count << "!\n";
    }

    {
        Timer t;

    }
    
    return 0;
}