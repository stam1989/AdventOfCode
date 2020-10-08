//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <cstdint>
#include <tuple>
#include <utility>
#include <stdarg.h>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <algorithm>

#include <iostream>

static uint32_t s_AllocCount = 0;

void* operator new(size_t s)
{
    s_AllocCount++;
//     std::cout << "Allocating " << s << std::endl;
    return malloc(s);
}

class Reaction {
public:
    Reaction() = default;
    Reaction( std::vector<std::pair<size_t, std::string_view>>& in,  std::pair<size_t, std::string_view>& out)
        : input(in), output(out) { std::cout << "Copied\n"; }
    Reaction( std::vector<std::pair<size_t, std::string_view>>&& in,  std::pair<size_t, std::string_view>&& out)
        : input(std::move(in)), output(std::move(out)) { std::cout << "Moved\n"; }

    Reaction(const Reaction& r) : input(r.input), output(r.output) { std::cout << "Copied\n"; }

    bool operator=(Reaction& r){
        return input == r.input && output == r.output;
    }
    bool operator=(Reaction&& r){
        return input == r.input && output == r.output;
    }

	void SetInput(size_t count, std::string_view element) {
		
	}
	
	void SetOutput(size_t count, std::string_view element) {
		output = std::make_pair(count, element);
	}
	
private:
    std::vector<std::pair<size_t, std::string_view>> input;
    std::pair<size_t, std::string_view> output;
};



void DecodeReaction(std::string s, Reaction res_reaction) {
	if(s.empty()) {
		return;
	}
		
	std::string delimiter1 = "=>";
	std::string s_out;
	size_t pos = 0, pos2 = 0;
	std::vector<std::pair<size_t, std::string_view>> v_input;
	std::string input_chems;
	while ((pos = s.find(delimiter1)) != std::string::npos) {
		input_chems = s.substr(0, pos);
// 		std::cout << "token: " << token << std::endl;
		
		std::stringstream s_stream(input_chems);
		while(s_stream.good()) {
			std::string substr;
			getline(s_stream, substr, ','); //get first string delimited by comma
			std::stringstream inp(substr);
			std::string temp_count;
			std::string temp_el;
			inp >> temp_count >> temp_el;
			std::remove(temp_el.begin(), temp_el.end(), ' ');
			std::remove(temp_count.begin(), temp_count.end(), ' ');
			std::cout << "input:: temp_count: " << temp_count << ", temp_el: " << temp_el << std::endl;			v_input.emplace_back(std::make_pair(stoll(temp_count, nullptr, 10), temp_el.c_str()));
		}
		 
		 
		 s.erase(0, pos + delimiter1.length());
	}
	std::stringstream out(s);
	std::string temp_count;
	std::string temp_el;
	out >> temp_count >> temp_el;
	std::remove(temp_count.begin(), temp_count.end(), ' ');
	std::remove(temp_el.begin(), temp_el.end(), ' ');
	std::cout << "output:: temp_count: " << temp_count << ", temp_el: " << temp_el << std::endl;
	std::pair<size_t, std::string_view> p_output({stoll(temp_count, nullptr, 10), temp_el.c_str()});
	
	res_reaction = Reaction(v_input, p_output);
}


void ReadFile(const char* filename, std::vector<Reaction>& v_reactions)
{
    std::cout << "ReadFile starts\n";

    std::ifstream input(filename);
    std::string s_reaction;
	
    if (input.is_open())
    {
        while (std::getline(input, s_reaction))
        {
			Reaction temp_r;
			std::cout << "ds\n";
			DecodeReaction(s_reaction, temp_r);
			v_reactions.emplace_back(temp_r);
        }
        input.close();
    }
    else
    {
        std::string exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}



int main() {
	std::vector<Reaction> v_reactions;
	const char* filename = "../../../resources/Day14.txt";
	ReadFile(filename, v_reactions);
	
	
	
	std::cout << "Allocations:" << s_AllocCount << std::endl;

    return 0;
}
