//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day2.h"

#include <fstream>
#include <iostream>

void Day2::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            if (!s_input.empty()) {
                v_inputs.emplace_back(Decode(s_input));
            }
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


Day2::Input Day2::Decode(std::string& s_input)
{
    // Form of the input: 8-9 n: nnnnnnnnn

    Input input;

    // Set min
    const std::string dash_delimiter("-");
    input.min = stoi(s_input.substr(0, s_input.find(dash_delimiter)));
    s_input.erase(0, s_input.find(dash_delimiter) + dash_delimiter.length());

    // Set max
    const std::string space_delimiter(" ");
    input.max = stoi(s_input.substr(0, s_input.find(space_delimiter)));
    s_input.erase(0, s_input.find(space_delimiter) + space_delimiter.length());
    
    // Set element
    input.element = s_input.substr(0, 1)[0];
    s_input.erase(s_input.begin(), s_input.begin() + 3); // delete begin + 3 since we need to delete the colon(":") and the space after the colon too. 

    // Set password
    input.password = s_input;

    return input;
}


void Day2::PrintInputs()
{
    for (const auto& input : v_inputs)
    {
        std::cout << input.min << "-" << input.max << " " << input.element << ": " << input.password << "\n";
    }
}

bool Day2::IsValidFirstMethod(const Input& input)
{
    size_t count = std::count_if(input.password.begin(), input.password.end(), [&input](char c) { return c == input.element; });
    if (count >= input.min && count <= input.max)
        return true;
    return false; 
}


bool Day2::IsValidSecondMethod(const Input& input)
{
    if((input.element == input.password[input.min - 1] && input.element != input.password[input.max - 1]) || 
       (input.element == input.password[input.max - 1] && input.element != input.password[input.min - 1]))
    {
        return true;
    }
    return false;
}


int Day2::CountValidPasswords(Method m)
{
    int16_t counter = 0;
    if (m == Day2::Method::FIRST)
    {
        for (const auto& input : v_inputs)
        {
            if (IsValidFirstMethod(input))
            {
                counter++;
            }
        }
    }
    else
    {
        for (const auto& input : v_inputs)
        {
            if (IsValidSecondMethod(input))
            {
                counter++;
            }
        }
    }
    
    return counter;
}


int main()
{
    Day2 d;

    std::cout << "The valid passwords using first method are " << d.CountValidPasswords(Day2::Method::FIRST) << "!!\n";
    std::cout << "The valid passwords using second method are " << d.CountValidPasswords(Day2::Method::SECOND) << "!!\n";

    

    return 0;
}