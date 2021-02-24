//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day24.h"
#include "Timer.h"
#include "Color.h"

#include <fstream>
#include <string>
#include <regex>
#include <set>

void Day24::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
    std::regex r("([sn]?[ew]{1})");
    if (inputFile.is_open()) {
        while (std::getline(inputFile, s_input)) {
            std::smatch matches;
            std::vector<Directions> temp_dir;
            while (std::regex_search(s_input, matches, r)) {
                std::string m = matches.str(1);
                Directions dir;
                if (m == "e") dir = Directions::E;
                else if (m == "se") dir = Directions::SE;
                else if (m == "sw") dir = Directions::SW;
                else if (m == "w") dir = Directions::W;
                else if (m == "nw") dir = Directions::NW;
                else if (m == "ne") dir = Directions::NE;
                temp_dir.emplace_back(dir);
                s_input.erase(0, m.size());
            }
            m_dirs.emplace_back(temp_dir);
        }
        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day24::PrintDirs() {
    for (const auto& dirs : m_dirs) {
        for (const auto d : dirs) {
            if (d == Directions::E) std::cout << "e";
            else if (d == Directions::SE) std::cout << "se";
            else if (d == Directions::SW) std::cout << "sw";
            else if (d == Directions::W) std::cout << "w";
            else if (d == Directions::NW) std::cout << "nw";
            else if (d == Directions::NE) std::cout << "ne";
        }
        std::cout << "\n";
    }
}


void Day24::PrintTiles() {
    for (const auto tiles_row : m_tiles) {
        for (const auto t : tiles_row) {
            if (t == 'W') std::cout << MAGENTA << t << RESET;
            if (t == 'B') std::cout << BLACK << t << RESET;
        }
        std::cout << "\n";
    }
}


void Day24::IdentifyTiles() {
    for (const auto& dirs : m_dirs) {
        Hexagon hexagon;
        for (const auto d : dirs) {
            switch (d)
            {
            case Directions::E:
                hexagon.x++;
                break;
            case Directions::SE:
                hexagon.y--;
                if (hexagon.y % 2 == 0) hexagon.x++;
                break;
            case Directions::SW:
                hexagon.y--;
                if (hexagon.y % 2 == 1) hexagon.x--;
                break;
            case Directions::W:
                hexagon.x--;
                break;
            case Directions::NE:
                hexagon.y++;
                if (hexagon.y % 2 == 0) hexagon.x++;
                break;
            case Directions::NW:
                hexagon.y++;
                if (hexagon.y % 2 == 1) hexagon.x--;
                break;
            default:
                throw std::runtime_error("IdentifyTiles wrong dir...");
                break;
            }
        }
        FlipTile(hexagon.x, hexagon.y);
    }
}


int32_t Day24::CountBlackTiles() {
    int32_t count = 0;
    for (const auto& tiles : m_tiles) {
        count += std::count(tiles.begin(), tiles.end(), 'B');
    }

    return count;
}


void Day24::FlipTile(const int16_t x, const int16_t y) {
    m_tiles[y][x] = (m_tiles[y][x] == 'W') ? 'B' : 'W';
}


int8_t Day24::CountBlackAdjacent(const int16_t x, const int16_t y) {
    int8_t count = 0;

    if (x + 1 < m_tiles.size() && m_tiles[y][x + 1] == 'B') count++;
    if (x > 0 && m_tiles.size() && m_tiles[y][x - 1] == 'B') count++;

    int temp_x = x;
    if (y % 2 == 0) {
        temp_x--;
    }

    if(y > 0 && temp_x >= 0 && m_tiles[y - 1][temp_x] == 'B') count++;
    if(y + 1 < m_tiles.size() && temp_x >= 0 && m_tiles[y + 1][temp_x] == 'B') count++;
    if(y > 0 && temp_x + 1 < m_tiles.size() && m_tiles[y - 1][temp_x + 1] == 'B') count++;
    if(y + 1 < m_tiles.size() && temp_x + 1 < m_tiles.size() && m_tiles[y + 1][temp_x + 1] == 'B') count++;

    return count;
}


void Day24::ArtExhibition() {
    const int16_t days = 100;

    for (int16_t i = 1; i <= days; i++) {
        auto temp_tiles = m_tiles;
        for (int col = 0; col < m_tiles.size(); col++) {
            for (int row = 0; row < m_tiles[col].size(); row++) {
                auto count = CountBlackAdjacent(row, col);
                if (m_tiles[col][row] == 'B' && (count == 0 || count > 2)) {
                    temp_tiles[col][row] = 'W';
                }

                if (m_tiles[col][row] == 'W' && count == 2) {
                    temp_tiles[col][row] = 'B';
                }
            }
        }
        m_tiles = temp_tiles;
    }
}


int main() {
    Day24 d;
    {
        Timer t;
        d.IdentifyTiles();
        d.PrintTiles();

        std::cout << "\nThe black tiles are: " << d.CountBlackTiles() << "!\n";
    }

    {
        Timer t;
        d.ArtExhibition();
        d.PrintTiles();
        std::cout << "\nThe black tiles are: " << d.CountBlackTiles() << "!\n";
    }
    
    return 0;
}