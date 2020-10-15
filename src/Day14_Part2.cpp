//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <cstdint>
#include <utility>
#include <stdarg.h>
#include <string_view>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <exception>
#include <algorithm>
#include<iterator>
#include <assert.h>

#include <iostream>


using ReactInput = std::vector<std::pair<size_t, std::string>>;
using ReactOutput = std::pair<size_t, std::string>;

static uint32_t s_AllocCount = 0;
static const char* filename = "../../../resources/Day14.txt";

void* operator new(size_t s)
{
    s_AllocCount++;
    //     std::cout << "Allocating " << s << std::endl;
    return malloc(s);
}

class Reaction {
public:
    Reaction() = default;
    Reaction( ReactInput& in,  ReactOutput& out)
    : input(in), output(out) {}
    Reaction( ReactInput&& in,  ReactOutput&& out)
    : input(std::move(in)), output(std::move(out)) {}

    Reaction(const Reaction& r) : input(r.input), output(r.output) {}

    bool operator=(Reaction& r){
        return input == r.input && output == r.output;
    }
    bool operator=(Reaction&& r){
        return input == r.input && output == r.output;
    }

    const ReactInput GetInput() { return input;}
    const ReactOutput GetOutput() { return output;}

private:
    ReactInput input;
    ReactOutput output;
};

void ExtractFromStream(std::string str, std::string& count, std::string& element) {
    std::stringstream ss(str);
    ss >> count >> element;
}

ReactOutput MakeOutput(std::string& s) {
    std::string temp_count, temp_el;
    ExtractFromStream(s, temp_count, temp_el);

    std::remove(temp_count.begin(), temp_count.end(), ' ');
    std::remove(temp_el.begin(), temp_el.end(), ' ');
    return {stoll(temp_count, nullptr, 10), temp_el};
}

ReactInput MakeInput(std::string& str_inputChems) {
    std::stringstream ss_inputChems(str_inputChems);
    ReactInput v_input;
    while(ss_inputChems.good()) {
        std::string chem;
        getline(ss_inputChems, chem, ','); //get first string delimited by comma
        std::string temp_el, temp_count;

        ExtractFromStream(chem, temp_count, temp_el);

        std::remove(temp_el.begin(), temp_el.end(), ' ');
        std::remove(temp_count.begin(), temp_count.end(), ' ');
        v_input.emplace_back(std::make_pair(stoll(temp_count, nullptr, 10), temp_el.c_str()));
    }
    return v_input;
}

Reaction DecodeReaction(std::string& s) {

    const std::string delimiter1("=>");

    size_t pos = 0;
    ReactInput v_input;
    std::string str_inputChems;
    while ((pos = s.find(delimiter1)) != std::string::npos) {
        str_inputChems = s.substr(0, pos);
        v_input = MakeInput(str_inputChems);

        s.erase(0, pos + delimiter1.length());
    }

    ReactOutput p_output(MakeOutput(s));

    return Reaction(v_input, p_output);
}


void Decode(std::string s_reaction) {
    std::map<std::string, std::map<std::string, size_t>> m_reactions;
}


void ReadFile(std::vector<Reaction>& v_reactions)
{
//     std::cout << "ReadFile starts\n";

    std::ifstream input(filename);
    std::string s_reaction;

    if (input.is_open())
    {
        while (std::getline(input, s_reaction))
        {
            if (!s_reaction.empty()) {
                v_reactions.emplace_back(DecodeReaction(s_reaction));
            }
        }
        input.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

//     std::cout << "ReadFile finished\n";
}

void InsertNeeds(std::map<std::string, size_t>& m_needs,
                   const std::pair<size_t, std::string>& input,
                 const size_t& div, size_t& available_ores) {
    std::pair<std::map<std::string, size_t>::iterator,bool> ret;

    if (input.second == "ORE") {
        size_t ores = div * input.first;
        available_ores -= ores;
        if (available_ores < 0)
            std::cout<< "Problem!\n";
        assert(available_ores >= 0);
    }
    else {
        ret = m_needs.insert(std::pair<std::string, size_t>(input.second, div * input.first));
        if (ret.second == false) {
            m_needs[input.second] += div * input.first;
        }
    }
}


bool CheckLeftovers(std::map<std::string, size_t>& m_needs,
                std::map<std::string, size_t>& m_leftovers,
                const size_t element_count, const std::string& element_name) {

    auto it_leftovers = m_leftovers.find(element_name);

    if (it_leftovers != m_leftovers.end())
    {
        if (it_leftovers->second > element_count) {
            it_leftovers->second -= element_count;
            m_needs.erase(element_name);
            return true;
        }

        if (it_leftovers->second == element_count) {
            m_leftovers.erase(it_leftovers->first);
            m_needs.erase(element_name);
            return true;
        }
    }
    return false;
}


bool IsNextToDelete(size_t& element_count, const std::string& element_name,
                const size_t reactionElement_count,
                std::map<std::string, size_t>& m_leftovers) {

    size_t mod = element_count % reactionElement_count;
    if (mod == 0) {
        return true;
    }

    auto it_leftovers = m_leftovers.find(element_name);
    if (element_count > reactionElement_count && it_leftovers != m_leftovers.end()) {
        if (it_leftovers->second > mod) {
            it_leftovers->second -= mod;
            element_count -= mod;
            return true;
        }

        if (it_leftovers->second == mod) {
            m_leftovers.erase(it_leftovers);
            element_count -= mod;
            return true;
        }


    }

    return false;
}


bool CalcOres(std::map<std::string, size_t>& m_needs, std::vector<Reaction>& v_reactions,
                size_t& available_ores, std::map<std::string, size_t>& m_leftovers) {
    bool check_changes = false;
    std::map<std::string, size_t> temp_needs(m_needs);
    for (auto it_needs = temp_needs.begin(); it_needs != temp_needs.end(); it_needs++) {

        std::string element_name = it_needs->first;
        size_t element_count = it_needs->second;
        auto it_leftovers = m_leftovers.find(element_name);

        check_changes = CheckLeftovers(m_needs, m_leftovers, element_count, element_name);

        auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
            return (r.GetOutput().second == element_name); });

        if ((it_reactions != v_reactions.end()) &&
            IsNextToDelete(element_count, element_name, it_reactions->GetOutput().first, m_leftovers)) {
            size_t div = element_count / it_reactions->GetOutput().first;
        for (auto& input: it_reactions->GetInput()) {
            InsertNeeds(m_needs, input, div, available_ores); }
        m_needs.erase(element_name);
        check_changes = true;
        }
    }

    return check_changes;
}


void InsertLeftovers(const size_t& leftovers, std::map<std::string, size_t>& m_leftovers,
                    const std::map<std::string, size_t>::iterator& it_needs) {
    std::pair<std::map<std::string, size_t>::iterator,bool> ret_leftovers;
    ret_leftovers = m_leftovers.insert(std::pair<std::string, size_t>(it_needs->first, leftovers));
    if (ret_leftovers.second == false) {
        m_leftovers[it_needs->first] += leftovers;
    }
}

void InitNeeds(std::vector<Reaction>& v_reactions, std::map<std::string, size_t>& m_needs) {
    auto it = std::find_if(v_reactions.begin(), v_reactions.end(), [](Reaction& r) {
        return (r.GetOutput().second == "FUEL");
    });

    for (const auto& in: it->GetInput()) {
        m_needs.emplace(in.second, in.first);
    }

}

int main() {
    std::vector<Reaction> v_reactions;
    ReadFile(v_reactions);

    size_t available_ores = 1000000000000;
    size_t fuel_counter = 0;
//     bool exit_flag = false;
    std::map<std::string, size_t> m_leftovers;

    while (available_ores > 0/* && !exit_flag*/) {
//     exit_flag = true;
    std::map<std::string, size_t> m_needs;
//     std::cout << "Leftovers:\n";
//     for (auto it = m_leftovers.begin(); it != m_leftovers.end(); it++)
//         std::cout << it->first << ": " << it->second << ", ";
//     std::cout << "\n\n\nStarts!!\n";
    InitNeeds(v_reactions, m_needs);
        while (!m_needs.empty()) {
            if (!CalcOres(m_needs, v_reactions, available_ores, m_leftovers)) {
                auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
                    return (r.GetOutput().second == m_needs.begin()->first); });
                size_t div = (m_needs.begin()->second / it_reactions->GetOutput().first) + 1;
                size_t leftovers = (div * it_reactions->GetOutput().first) - m_needs.begin()->second;

                InsertLeftovers(leftovers, m_leftovers, m_needs.begin());

                for (auto& input: it_reactions->GetInput()) {
                    InsertNeeds(m_needs, input, div, available_ores);
                }
                m_needs.erase(it_reactions->GetOutput().second);
            }
        }

        fuel_counter += 1;
        if (m_leftovers.empty()) {
            std::cout << "fuel_counter: " << fuel_counter << ", available_ores: " << available_ores << std::endl;
            break;
        }
//         std::cout << "We produce " << fuel_counter << " FUEL!\n";
//         std::cout << "\n Finishes!!\n\n\n";

    }

    std::cout << "We produce " << fuel_counter << " FUEL!\n";

    std::cout << "Allocate " << s_AllocCount << " times\n";
    return 0;
}
