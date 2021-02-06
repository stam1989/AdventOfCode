//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day16.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>


void Day16::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        std::string colon_del(":");
        while (std::getline(inputFile, s_input)) {
            auto pos = s_input.find(colon_del);
            auto fieldName = s_input.substr(0, pos);
            if (fieldName == "your ticket") {
                std::string ticketFields;
                while (std::getline(inputFile, ticketFields)) {
                    if (ticketFields.empty()) break;
                    m_myTicket = InsertTicket(ticketFields);
                }
           }
            else if (fieldName == "nearby tickets") {
                std::string nearbyTicket;
                while(std::getline(inputFile, nearbyTicket)) {
                    m_nearbyTickets.emplace_back(InsertTicket(nearbyTicket));
                }
            }
            else {
                while (true) {
                    if (s_input.empty()) break;
                    InsertRange(s_input);
                    std::getline(inputFile, s_input);
                }
            }
        }

        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


int16_t Day16::IsValid(Ticket t) {
    for (const auto& value : t) {
        bool isValid = false;
        for (const auto& r : m_restr) {
            if (((value >= r.second.r1.first && value <= r.second.r1.second) ||
                (value >= r.second.r2.first && value <= r.second.r2.second))) {
                isValid = true;
            }
        }
        if (!isValid) return value;  
    }
    return -1;
}


int32_t Day16::ScanNearbyTickets() {
    // ticket scanning error rate
    int32_t tser = 0;

    for(auto it = m_nearbyTickets.begin(); it != m_nearbyTickets.end(); it++) {
        auto errorRate = IsValid(*it);
        if(errorRate > 0) {
            tser += errorRate;
            m_nearbyTickets.erase(std::remove_if(m_nearbyTickets.begin(), m_nearbyTickets.end(), 
                                [&it](const Ticket& t) { return t == *it;}), m_nearbyTickets.end());
            it--;
        }
    }

    return tser;
}


void Day16::InsertRange(std::string& ranges) {
    std::string colon_del(": ");
    auto pos = ranges.find(colon_del);
    std::string name = ranges.substr(0, pos);
    ranges.erase(0, pos + colon_del.size());
    
    std::string or_del(" or ");
    std::string r;
    pos = ranges.find(or_del);
    auto r1 = GetRange<>(ranges.substr(0, pos));
    ranges.erase(0, pos + or_del.size());
    auto r2 = GetRange<>(ranges);

    m_restr[name] = Ranges(r1, r2);
}


Ticket Day16::InsertTicket(std::string& ticket) {
    std::istringstream ss(ticket);
    std::string value;
    Ticket temp_ticket;
    while(std::getline(ss, value, ',')) {
        temp_ticket.emplace_back(stol(value));
    }

    return temp_ticket;
}


void Day16::FillMapFields() {
    for (const auto& nt : m_nearbyTickets) {
        // this holds field positions to possible valid field names for each nearby ticket
        std::map<int16_t, std::set<std::string>> posToField;
        for (int16_t j = 0; j < nt.size(); j++) {
            // this holds all possible valid field names for the specific value at j position
            std::set<std::string> possibleValidFields;
            std::string temp_field;
            for (const auto& r : m_restr) {
                if (((nt[j] >= r.second.r1.first && nt[j] <= r.second.r1.second) ||
                     (nt[j] >= r.second.r2.first && nt[j] <= r.second.r2.second))) {
                    possibleValidFields.emplace(r.first);
                }
            }
            posToField[j] = possibleValidFields;
        }
        m_mapFields.emplace_back(posToField);
    }
}


std::map<std::string, int16_t> Day16::DetermineFields() {
    FillMapFields();
    // holds all fields that their position is determined
    std::map<std::string, int16_t> posToField;
    
    int16_t j = 0;    // this is the pos of the field we are looking to identify
    while(true) {

        // if the current j position is already identified, continue to next j
        auto it_ptf = std::find_if(posToField.begin(), posToField.end(), [&j](const auto& p) { return j == p.second; });
        if (it_ptf != posToField.end()) {
            j++;
            if (j ==  m_restr.size()) j = 0;
            continue;
        }

        // it holds the common possible field names between same position values
        auto commonFields(m_mapFields.begin()->find(j)->second);
        for (int16_t i = 0; i < m_mapFields.size(); i++) {
            auto it = m_mapFields[i].find(j);
    
            // if the field exists in posToField, it has to be removed from possible common fields
            for(const auto& ptf : posToField) {
                it->second.erase(ptf.first);
            }

            auto temp = commonFields;
            commonFields.clear();
            std::set_intersection(temp.begin(), 
                            temp.end(), 
                            it->second.begin(), 
                            it->second.end(), 
                            std::inserter(commonFields, commonFields.begin()));

            if (commonFields.size() == 1) {
                if(posToField.find(*commonFields.begin()) != posToField.end()) {
                    throw std::runtime_error("DetermineFields something went very wrong...");
                }
                posToField[*commonFields.begin()] = j;
            }
        }

        if (posToField.size() == m_restr.size()) break;
        
        j++;
        if (j ==  m_restr.size()) j = 0;
    }

    for (const auto& ptf : posToField)
        std::cout << ptf.first << ": " << ptf.second << "\n";

    return posToField;
}


uint64_t Day16::GetDepartureValuesMultipled() {
    std::string s_departure("departure");
    auto posToField = DetermineFields();

    uint64_t departureMultiple = 1;
    for (const auto& f : posToField) {
        if (f.first.find(s_departure) != std::string::npos) {
            departureMultiple *= m_myTicket[f.second];
        }
    }

    return departureMultiple;
}



int main() {
    Day16 d;
    // d.PrintInput();

    {
        Timer t;
        std::cout << "My ticket scanning error rate is: " << d.ScanNearbyTickets() << "!\n";
    }

    {
        Timer t;
        std::cout << "If you multiply the departure six values together you get: " << 
                    d.GetDepartureValuesMultipled() << "!\n";
    }
    
    return 0;
}