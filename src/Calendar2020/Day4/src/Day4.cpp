//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day4.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <ctype.h>


void Day4::ReadFile()
{
    std::ifstream input(FILENAME);
	std::string line;
	try
	{
		if (input.is_open())
		{
            const std::string colon_delimiter(":");
            std::map<std::string, std::string> temp_passData;
			while (std::getline(input, line))
			{
                if(line.empty())
                {
                    m_passports.emplace_back(temp_passData);
                    temp_passData.clear();
                    continue;
                }
                std::istringstream data(line);
                std::string d;
                while(data >> d)
                {
                    std::string field(d.substr(0, d.find(colon_delimiter))); 
                    d.erase(0, d.find(colon_delimiter) + colon_delimiter.length());
                    temp_passData.emplace(field, d);
                }
			}

            m_passports.emplace_back(temp_passData);

			input.close();
		}
		else
		{
			std::string exception_string =  "Could not open input file";
			throw std::runtime_error(exception_string);
		}
	}
	catch(std::string& exception_string)
	{
		std::cout << exception_string << std::endl;
	}
}


void Day4::PrintPassports()
{
    for (const auto& passport : m_passports)
    {
        for (const auto& data : passport)
        {
            std::cout << data.first << ":" << data.second << "\n";
        }
        std::cout << "\n";
    }
}


bool Day4::IsFieldDataValid(const std::map<std::string, std::string>& passport)
{

    bool isValid = false;
    for(const auto& p : passport)
    {
        if (p.first == "byr")
        {
            if (!(is_digits(p.second) && (stol(p.second) >= 1920 && stol(p.second) <= 2002)))
            {
                return false;
            }
        }
        else if (p.first == "iyr")
        {    
            if (!(is_digits(p.second) && (stol(p.second) >= 2010 && stol(p.second) <= 2020)))
            {
                return false;
            }
        }
        else if (p.first == "eyr")
        {    
            if (!(is_digits(p.second) && (stol(p.second) >= 2020 && stol(p.second) <= 2030)))
            {
                return false;
            }
        }
        else if (p.first == "hgt")
        {
            if(!((p.second.substr(p.second.size() - 2, p.second.size()) == "cm" && stol(p.second.substr(0, p.second.size() - 2)) >= 150 && stol(p.second.substr(0, p.second.size() - 2)) <= 193) ||
                 (p.second.substr(p.second.size() - 2, p.second.size()) == "in" && stol(p.second.substr(0, p.second.size() - 2)) >= 59 && stol(p.second.substr(0, p.second.size() - 2)) <= 76)))
                {
                    return false;
                }
        }
        else if (p.first == "hcl")
        {
            if(!((p.second[0] == '#') && (is_alphasOrDigits(p.second.substr(1, p.second.size())))))
            {
                return false;
            }
        }
        else if (p.first == "ecl")
        {
            if (!(p.second == "amb" || p.second == "blu" || p.second == "brn" || p.second == "gry" || p.second == "grn" || p.second == "hzl" || p.second == "oth"))
            {
                std::cout << p.first << ":" << p.second << "\n";
                return false;
            }
        }
        else if (p.first == "pid")
        {
            if (!(is_digits(p.second) && p.second.size() == 9))
            {
                return false;
            }
        }
        else if (p.first == "cid")
        {
            continue;
        }
        else
        {
            std::cerr << p.first << ":" << p.second << "\n";
            throw std::invalid_argument("Day4::IsFieldDataValid invalid filed...");
        }
    }
 
    return true;
}


std::tuple<int32_t, int32_t> Day4::CountValidPassports()
{
    int32_t validPassportCounter = 0, validPassportCounter_enhanced = 0;
    for (const auto& passport : m_passports)
    {
        if ((passport.size() == 8) || ((passport.size() == 7) && passport.find("cid") == passport.end()))
        {
            if(IsFieldDataValid(passport))
            {
                validPassportCounter_enhanced++;
            }
            validPassportCounter++;
        }
    }

    return {validPassportCounter, validPassportCounter_enhanced};
}

int main()
{
    Day4 d;
    d.PrintPassports();

    auto [validPassportCounter, validPassportCounter_enhanced] = d.CountValidPassports();
    std::cout << "The valid passwords are: " << validPassportCounter << "\n";
    std::cout << "The valid passwords are: " << validPassportCounter_enhanced << "\n";

    return 0;
}