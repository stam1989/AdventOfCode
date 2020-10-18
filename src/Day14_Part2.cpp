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

#include <iostream>


using ReactInput = std::vector<std::pair<size_t, std::string>>;
using ReactOutput = std::pair<size_t, std::string>;

static uint32_t s_AllocCount = 0;
static const char* filename = "../resources/Day14.txt";

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
//     Reaction(const Reaction&& r) : input(r.input), output(r.output) { std::cout << "Moved\n"; }

    bool operator=(Reaction& r){
        return input == r.input && output == r.output;
    }
    bool operator=(Reaction&& r){
        return input == r.input && output == r.output;
    }

    ReactInput GetInput() { return input;}
    ReactOutput GetOutput() { return output;}

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
    std::cout << "ReadFile starts\n";

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

    std::cout << "ReadFile finished\n";
}

size_t InsertNeeds(std::map<std::string, size_t>& umap_needs,
                 const std::pair<size_t, std::string>& input, const size_t& div) {
    size_t oreCounter = 0;
    std::pair<std::map<std::string, size_t>::iterator,bool> ret;

    if (input.second == "ORE") {
        oreCounter += div * input.first;
    }
    else {
        ret = umap_needs.insert(std::pair<std::string, size_t>(input.second, div * input.first));
        if (ret.second == false) {
            umap_needs[input.second] += div * input.first;
        }
    }
    return oreCounter;
}


void CheckLeftovers(std::map<std::string, size_t>& umap_needs,
                    std::map<std::string, size_t>& umap_leftovers,
                    const size_t element_count, const std::string& element_name
                   ) {

    auto it_leftovers = umap_leftovers.find(element_name);

    if (it_leftovers != umap_leftovers.end())
    {
        if (it_leftovers->second > element_count) {
            it_leftovers->second -= element_count;
            umap_needs.erase(element_name);
        }

        if (it_leftovers->second == element_count) {
            umap_leftovers.erase(it_leftovers->first);
            umap_needs.erase(element_name);
        }
    }
}


bool IsNextToDelete(size_t& element_count, const std::string& element_name,
                    const size_t reactionElement_count,
                    std::map<std::string, size_t>& umap_leftovers) {

    size_t mod = element_count % reactionElement_count;
    if (mod == 0) {
        return true;
    }

    auto it_leftovers = umap_leftovers.find(element_name);
    if (element_count > reactionElement_count && it_leftovers != umap_leftovers.end()) {
        if (it_leftovers->second > mod) {
            it_leftovers->second -= mod;
            element_count -= mod;
            return true;
        }

        if (it_leftovers->second == mod) {
            umap_leftovers.erase(it_leftovers);
            element_count -= mod;
            return true;
        }


    }

    return false;
}


bool CalcOres(std::map<std::string, size_t>& umap_needs, std::vector<Reaction>& v_reactions,
              size_t& oreCounter, std::map<std::string, size_t>& umap_leftovers) {
    bool check_changes = false;
    std::map<std::string, size_t> temp_needs(umap_needs);
    for (auto it_needs = temp_needs.begin(); it_needs != temp_needs.end(); it_needs++) {

        std::string element_name = it_needs->first;
        size_t element_count = it_needs->second;
        auto it_leftovers = umap_leftovers.find(element_name);

        CheckLeftovers(umap_needs, umap_leftovers, element_count, element_name);

        auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
            return (r.GetOutput().second == element_name); });

        if ((it_reactions != v_reactions.end()) &&
            IsNextToDelete(element_count, element_name, it_reactions->GetOutput().first, umap_leftovers)) {
            size_t div = element_count / it_reactions->GetOutput().first;
            for (auto& input: it_reactions->GetInput()) {
                oreCounter += InsertNeeds(umap_needs, input, div);
            }
            umap_needs.erase(element_name);
            check_changes = true;
            break;
        }
    }

    return check_changes;
}


void InsertLeftovers(const size_t& leftovers, std::map<std::string, size_t>& umap_leftovers,
                     const std::map<std::string, size_t>::iterator& it_needs) {
    std::pair<std::map<std::string, size_t>::iterator,bool> ret_leftovers;
    ret_leftovers = umap_leftovers.insert(std::pair<std::string, size_t>(it_needs->first, leftovers));
    if (ret_leftovers.second == false) {
        umap_leftovers[it_needs->first] += leftovers;
    }
}

size_t OreRequired(std::vector<Reaction>& v_reactions, size_t fuelCount)
{
    std::map<std::string, size_t> umap_needs, umap_leftovers;
    umap_needs.emplace("FUEL", fuelCount);

	size_t oreCounter = 0;

	while (!umap_needs.empty()) {
		if (!CalcOres(umap_needs, v_reactions, oreCounter, umap_leftovers)) {
			auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
				return (r.GetOutput().second == umap_needs.begin()->first); });
			size_t div = (umap_needs.begin()->second / it_reactions->GetOutput().first) + 1;
            size_t leftovers = (div * it_reactions->GetOutput().first) - umap_needs.begin()->second;

            InsertLeftovers(leftovers, umap_leftovers, umap_needs.begin());

			for (auto& input: it_reactions->GetInput()) {
                oreCounter += InsertNeeds(umap_needs, input, div);
			}
			umap_needs.erase(it_reactions->GetOutput().second);
		}
	}

    return oreCounter;
}

int main() {
	std::vector<Reaction> v_reactions;
	ReadFile(v_reactions);


    size_t availableOres = 1000000000000;
    size_t low = availableOres / OreRequired(v_reactions, 1);
    size_t high = low * 10;

    while(OreRequired(v_reactions, high) < availableOres)
    {
        low = high;
        high *= 10;
    }

    while(low < high - 1)
    {
        size_t mid = (high + low) / 2;
        size_t oreCounter = OreRequired(v_reactions, mid);

        std::cout << "high: " << high << ", low: " << low << ", fuel: " << mid << ", oreCounter: " << oreCounter << "\n\n";
        if (oreCounter < availableOres)
        {
            low = mid;
        }
        else if (oreCounter > availableOres)
        {
            high = mid;
        }
        else 
        {
            std::cout << "We produce " << mid << " fuel\n";
            break;
        }
    }

    return 0;
}
