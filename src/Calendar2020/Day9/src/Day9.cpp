//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day9.h"

#include <fstream>


void Day9::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            m_data.emplace_back(stol(s_input));
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


int64_t Day9::FindFirstInvalid(int64_t preamble)
{
    for(int i = preamble; i < m_data.size(); i++)
    {
        bool isValid = false;
        for(int m = i - preamble; m < i - 1; m++)
        {
            for(int n = m + 1; n < i; n++)
            {
                if(m_data[i] == m_data[m] + m_data[n])
                {
                    isValid = true;
                    break;
                }
            }
            if(isValid)
            {
                break;
            }
        }
        
        if(!isValid)
        {
            return m_data[i];
        }
    }
}


int64_t Day9::FindEncryptionWeakness(int64_t firstInvalid)
{
    for(int64_t i = 0; i < firstInvalid - 1; i++)
    {
        int64_t sum = m_data[i];
        for(int64_t j = i + 1; j < firstInvalid; j++)
        {
            sum += m_data[j];
            if(sum == firstInvalid)
            {
                return  (*std::min_element(m_data.begin() + i, m_data.begin() + j) + 
                         *std::max_element(m_data.begin() + i, m_data.begin() + j));
            }
            
            if(sum > firstInvalid)
            {
                break;
            }
        }
    }
}


int main()
{
    Day9 d;
    d.PrintData();

    int64_t firstInvalid = d.FindFirstInvalid(25);
    std::cout << "The first invalid number is: " << firstInvalid << "!!\n";
    std::cout << "The encryption weakness in the XMAS-encrypted list of numbers is: " << d.FindEncryptionWeakness(firstInvalid) << "!!\n";
    return 0;
}