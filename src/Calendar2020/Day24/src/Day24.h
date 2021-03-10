//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY24_H
#define DAY24_H


#include <cstdlib>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


using Tiles = std::vector<std::vector<char>>;

class Day24
{
public:
    Day24() : m_tiles(REFERENCE_Y * 2, std::vector<char>(REFERENCE_X * 2, 'W')) { ReadFile(); }

    enum class Directions {
        E = 0,
        SE,
        SW,
        W,
        NW,
        NE
    };

    struct Hexagon {
        Hexagon() : x(REFERENCE_X), y(REFERENCE_Y) {}

        int32_t x, y;
    };

    void PrintDirs();
    void IdentifyTiles();
    void PrintTiles();
    void FlipTile(const int16_t x, const int16_t y);
    int32_t CountBlackTiles();
    int8_t CountBlackAdjacent(const int16_t x, const int16_t y);
    void ArtExhibition();

private:
    std::vector<std::vector<Directions>> m_dirs;
    Tiles m_tiles;

    static constexpr int16_t REFERENCE_X = 70;
    static constexpr int16_t REFERENCE_Y = 70;

    fs::path FILENAME = "../src/Calendar2020/Day24/resources/Day24.txt";

    void ReadFile();
};


#endif