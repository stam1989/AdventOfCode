//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <cstdint>
#include <map>
#include <utility>
#include <stdarg.h>
#include <string_view>
#include <fstream>
#include <sstream>
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



int main() {
	std::vector<Reaction> v_reactions;
	ReadFile(v_reactions);
	
	auto it = std::find_if(v_reactions.begin(), v_reactions.end(), [](Reaction& r) {
        return (r.GetOutput().second == "FUEL");
    });

    std::cout << "input first: " << it->GetInput()[0].first << " " << it->GetInput()[0].second << std::endl;
    std::cout << "output: " << it->GetOutput().first << " " << it->GetOutput().second << std::endl;

	std::cout << "Allocations:" << s_AllocCount << std::endl;

    return 0;
}
