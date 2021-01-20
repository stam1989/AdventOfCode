//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY4_H
#define DAY4_H


#include <map>
#include <vector>
#include <array>
#include <string>
#include <cstdint>

using Passports = std::vector<std::map<std::string, std::string>>;

class Day4
{
public:
    Day4() { ReadFile(); }

    void ReadFile();
    void DecodePassportData();
    void PrintPassports();
    std::tuple<int32_t, int32_t> CountValidPassports();
    bool IsFieldDataValid(const std::map<std::string, std::string>& passport);

    inline bool is_digits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

    inline bool is_alphas(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), ::isalpha); // C++11
    }

    inline bool is_alphasOrDigits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), [](const char c) { return (isdigit(c) || isalpha(c)); }); // C++11
    }

private:
    Passports m_passports;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day4/resources/Day4.txt";
};


#endif