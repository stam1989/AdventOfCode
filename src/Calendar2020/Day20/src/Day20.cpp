//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day20.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <algorithm>


void Day20::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
    

    if (inputFile.is_open()) {
        int32_t temp_tileId;
        std::regex regex_tileId("([0-9]+)");
        while (std::getline(inputFile, s_input)) {
            std::smatch match_tileId;
            if (std::regex_search(s_input, match_tileId, regex_tileId)) {
                temp_tileId = stol(match_tileId.str(1));
            }
            
            Tile temp_tiles;
            while(std::getline(inputFile, s_input)) {
                if (s_input.empty()) break;
                
                temp_tiles.emplace_back(s_input);
            }
            m_tiles[temp_tileId] = temp_tiles;
        }
        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day20::PrintTiles() {
    for (const auto& tiles : m_tiles) {
        std::cout << "\nTile " << tiles.first << ":\n";
        for (const auto tileRow : tiles.second) {
            std::cout << tileRow << "\n";
        }
    }
}


void Day20::GetSides() {
    for (const auto& t : m_tiles) {
        // we have 8 possible sides of the puzzle piece since it can be either rotated or flipped 

        auto it = m_tiles.find(t.first);

        std::string top(t.second[0]);  // get top side
        std::string rtop(top);
        std::reverse(rtop.begin(), rtop.end()); // get top side reverse

        std::string bottom(t.second[t.second.size() - 1]);  // get bottom side
        std::string rbottom(bottom);
        std::reverse(rbottom.begin(), rbottom.end());   // get bottom side reverse

        std::string left, rleft, right, rright;

        for(int i = 0; i < t.second.size(); i++) {
            left.push_back(t.second[i][0]);   // get left side
            rleft.push_back(t.second[t.second.size() - 1 - i][0]);   // get left side reverse
            right.push_back(t.second[i][t.second.size() - 1]);    // get right side
            rright.push_back(t.second[t.second.size() - 1 - i][t.second.size() - 1]);    // get right side reverse
        }

        m_tileSides[t.first] = {top, bottom, left, right, rtop, rbottom, rleft, rright};
    }
      
}


int64_t Day20::GetCornerMultiple() {
    GetSides();    
    int64_t res = 1;
    for (auto it = m_tileSides.begin(); it != m_tileSides.end(); it++) {
        int countCommon = 0;
        for (auto rit = m_tileSides.rbegin(); rit != m_tileSides.rend(); rit++) {
            if (*rit == *it) continue;
            auto it_first = std::find_first_of(it->second.begin(), it->second.end(), 
                                  rit->second.begin(), rit->second.end());
            if (it_first != it->second.end()) countCommon++;
        }
        if (countCommon == 2) res *= it->first;    // if the sides that match are 2, our piece is a corner
    }

    return res;
}


int main() {
    Day20 d;
    d.PrintTiles();
    
    {
        Timer t;
        std:: cout << "The multiple between corner ids is: " << d.GetCornerMultiple() << "!\n";
    }

    {
        Timer t;

    }
    
    return 0;
}