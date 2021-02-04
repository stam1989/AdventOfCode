//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day14.h"

#include <fstream>
#include <string>
#include <bitset>
#include <numeric>

void Day14::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        int64_t maxAddress = 0;
        Program p;
        while (std::getline(inputFile, s_input)) {
            if(s_input.find("mask = ") != std::string::npos) {
                if (!p.address.empty()) m_programInput.emplace_back(p.mask, p.address);
                p.address.clear();

                p.mask = s_input.substr(s_input.find("mask = ") + 7);
                continue;
            }

            AddressData ad;
            ad.pos = stol(s_input.substr(s_input.find("mem[") + 4, s_input.find("] = ")));
            if (ad.pos > maxAddress) maxAddress = ad.pos;

            s_input.erase(0, s_input.find("] = ") + 4);
            ad.value = stol(s_input);

            p.address.emplace_back(ad);
        }
        m_programInput.emplace_back(p.mask, p.address);

        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day14::PrintInput() {
    for (const auto& pi : m_programInput) {
        std::cout << "mask = " << pi.mask << "\n";
        for (const auto& a : pi.address) {
            std::cout << "mem[" << a.pos << "] = " << a.value << "\n";
        }
    }

    std::cout << "\n";
}


void Day14::FillAddresses() {
    for (const auto& pi : m_programInput) {
        for (const auto& ad : pi.address) {
            std::string binary = std::bitset<36>(ad.value).to_string();
            std::string temp_value;
            for (int16_t i = 0; i < binary.size(); i++) {
                // apply bitmask to the address
                if (pi.mask[i] == 'X') temp_value += binary[i];
                else temp_value += pi.mask[i];
            }
            m_values[ad.pos - 1] = stol(temp_value, nullptr, 2);
        }
    }
}


void Day14::PrintValues() {   
    for (auto a : m_values){
        std::cout << "m_values[" << a.first << "] : " << a.second << "\n";
    }
}


int64_t Day14::GetSum() {
    return std::accumulate(m_values.begin(), m_values.end(), static_cast<int64_t>(0), [](auto a, const auto b) { return a + b.second; });
}


void Day14::ApplyMaskToAddressAndStore(std::string position, const AddressData& ad) {
    
    size_t posToChange = position.find("X");
    
    if (posToChange == std::string::npos) {
        int64_t temp_pos = stol(position, nullptr, 2);
        m_values[temp_pos] = ad.value;
        return;
    }

    position[posToChange] = '0';
    ApplyMaskToAddressAndStore(position, ad);

    position[posToChange] = '1';
    ApplyMaskToAddressAndStore(position, ad);
}



void Day14::DecodeVersion2() {
    m_values.clear();
    for (const auto& pi : m_programInput) {
        for (auto ad : pi.address) {
            std::string binaryPos = std::bitset<36>(ad.pos).to_string();
            std::string temp_pos;
            for (int64_t i = 0; i < binaryPos.size(); i++) {
                // apply bitmask to the address positions with the version 2 decoder
                if (pi.mask[i] == '0') temp_pos += binaryPos[i];
                else temp_pos += pi.mask[i];
            }
            ApplyMaskToAddressAndStore(temp_pos, ad);
        }
    }
}


int main() {
    Day14 d;
    // d.PrintInput();

    d.FillAddresses();
    std::cout << "Sum is: " << d.GetSum() << "!\n";

    {
        // with map it takes around 170ms, while with unordered map needs around 150ms!
        Timer t;
        d.DecodeVersion2();
        std::cout << "Sum in Part 2 is: " << d.GetSum() << "!\n";
    }
    return 0;
}