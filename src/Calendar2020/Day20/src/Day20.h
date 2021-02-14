//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY20_H
#define DAY20_H


#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <map>

using Tile = std::vector<std::string>;
using Tiles = std::unordered_map<int32_t, Tile>;
using TileSides = std::map<int32_t, std::vector<std::string>>;


class Day20
{
public:
    Day20() { ReadFile(); }

    void PrintTiles();
    int64_t GetCornerMultiple();
private:
    Tiles m_tiles;
    TileSides m_tileSides;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day20/resources/Day20.txt";

    void ReadFile();
    void GetSides();
};

#endif