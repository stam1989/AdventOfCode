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
    // 	std::cout << "output:: temp_count: " << temp_count << ", temp_el: " << temp_el << std::endl;
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
//         std::cout << "input:: temp_count: " << temp_count << ", temp_el: " << temp_el << std::endl;
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
// 		std::cout << "token: " << token << std::endl;
        v_input = MakeInput(str_inputChems);

        s.erase(0, pos + delimiter1.length());
	}

	ReactOutput p_output(MakeOutput(s));

    return Reaction(v_input, p_output);
}


void Decode(std::string s_reaction) {
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> m_reactions;
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

bool CalcOres(std::unordered_map<std::string, size_t>& m_needings, std::vector<Reaction>& v_reactions, size_t& ore_counter) {
	bool check_changes = false;
	std::unordered_map<std::string, size_t> temp_needings(m_needings);
	for (auto it_needings = temp_needings.begin(); it_needings != temp_needings.end(); it_needings++) {
		auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
			return (r.GetOutput().second == it_needings->first); });
			
		if ((it_reactions != v_reactions.end()) && 
		    (it_needings->second % it_reactions->GetOutput().first == 0)) {
				uint8_t div = it_needings->second / it_reactions->GetOutput().first;
				for (auto& input: it_reactions->GetInput()) {
					std::pair<std::unordered_map<std::string, size_t>::iterator,bool> ret;
					if (input.second == "ORE") {
						ore_counter += div * input.first;
					}
					else {
						ret = m_needings.insert(std::pair<std::string, size_t>(input.second, div * input.first));
						if (ret.second == false) {
							m_needings[input.second] += div * input.first;
						}
					}
				}
				m_needings.erase(it_reactions->GetOutput().second);
				check_changes = true;
			}
	}
	
	return check_changes;
}

// void InsertElement() {
// 	std::pair<std::unordered_map<std::string, size_t>::iterator,bool> ret;
// 	if (input.second == "ORE") {
// 		ore_counter += div * input.first;
// 	}
// 	else {
// 		ret = m_needings.insert(std::pair<std::string, size_t>(input.second, div * input.first));
// 		if (ret.second == false) {
// 			m_needings[input.second] += div * input.first;
// 		}
// 	}
// }



int main() {
	std::vector<Reaction> v_reactions;
	ReadFile(v_reactions);

	auto it = std::find_if(v_reactions.begin(), v_reactions.end(), [](Reaction& r) {
        return (r.GetOutput().second == "FUEL");
    });

	std::unordered_map<std::string, size_t> m_needings;
	
	for (const auto& in: it->GetInput()) {
		m_needings.emplace(in.second, in.first);
	}

	for (auto it = m_needings.begin(); it != m_needings.end(); it++) {
		std::cout << it->first << " has " << it->second << std::endl;
	}

	size_t ore_counter = 0;
	while (!m_needings.empty()) {
		if (!CalcOres(m_needings, v_reactions, ore_counter)) {
			auto it_reactions = std::find_if(v_reactions.begin(), v_reactions.end(), [&](Reaction& r) {
				return (r.GetOutput().second == m_needings.begin()->first); });
			uint8_t div = (m_needings.begin()->second / it_reactions->GetOutput().first) + 1;
			for (auto& input: it_reactions->GetInput()) {
				std::pair<std::unordered_map<std::string, size_t>::iterator,bool> ret;
				if (input.second == "ORE") {
					ore_counter += div * input.first;
				}
				else {
					ret = m_needings.insert(std::pair<std::string, size_t>(input.second, div * input.first));
					if (ret.second == false) {
						m_needings[input.second] += div * input.first;
					}
				}
			}
			m_needings.erase(it_reactions->GetOutput().second);
		}
	}

	std::cout << "We need " << ore_counter << " OREs!\n";
//     std::cout << "input first: " << it->GetInput()[0].first << " " << it->GetInput()[0].second << std::endl;
//     std::cout << "output: " << it->GetOutput().first << " " << it->GetOutput().second << std::endl;
// 
// 	std::cout << "Allocations:" << s_AllocCount << std::endl;

    return 0;
}
