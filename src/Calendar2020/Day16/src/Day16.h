//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY16_H
#define DAY16_H


#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>

using Range = std::pair<int16_t, int16_t>;
using Ticket = std::vector<int16_t>;
using MapFields = std::vector<std::map<int16_t, std::set<std::string>>>;

class Day16
{
public:
    Day16() { ReadFile(); }

    struct Ranges
    {
        Ranges() {}
        Ranges(Range a, Range b) : r1(a), r2(b) {}

        Range r1, r2;
    };

    // returns ticket scanning error rate
    int32_t ScanNearbyTickets();
    uint64_t GetDepartureValuesMultipled();

private:
    std::map<std::string, Ranges> m_restr;
    Ticket m_myTicket;
    std::vector<Ticket> m_nearbyTickets;
    // this holds field positions to possible valid field names for all each nearby ticket
    MapFields m_mapFields;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day16/resources/Day16.txt";

    void ReadFile();
    void InsertRange(std::string& range);
    Ticket InsertTicket(std::string& nearbyTicket);
    Range GetRange(std::string&& range);
    int16_t IsValid(Ticket t);
    void FillMapFields();
    std::map<std::string, int16_t> DetermineFields();

static inline bool dummy_comp(const std::string &lhs, const std::string &rhs)
{ 
   return (lhs.size() == rhs.size()) ? lhs < rhs : lhs.size() < rhs.size();
}

template <typename T>
Range GetRange(T&& range) {
    int16_t r1, r2;
    std::string dash_del("-");
    auto pos = range.find(dash_del);
    r1 = stol(range.substr(0, pos));
    range.erase(0, pos + dash_del.size());
    r2 = stol(range);

    return Range(r1, r2);
}

};


#endif