//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY20_PART2_H
#define DAY20_PART2_H


#include <cstdlib>
#include <vector>
#include <set>


class Day20_Part2
{
public:
    Day20_Part2() { ReadFile(); }

    struct Tile {
        int id;
        std::vector<std::string> cells; // cells[S][S]
        
        bool can_below(const Tile& b) const {
            return cells[S-1] == b.cells[0];
        }
        bool can_right(const Tile& b) const {
            for(int row = 0; row < S; ++row) {
                if(cells[row][S-1] != b.cells[row][0]) {
                    return false;
                }
            }
            return true;
        }
    };

    void PrintTiles();
    void Search(int16_t row, int16_t col, std::set<int16_t>& visited);

private:
    int16_t GRID_SIZE;
    std::vector<Tile> m_tiles; // all 8*N available tiles
    Tile m_grid[20][20];
    
    static constexpr char const *FILENAME = "../src/Calendar2020/Day20/resources/Day20.txt";
    static constexpr int16_t S = 10;  // Tile size
    const std::string monster[3] = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    void ReadFile();
    void Rotate(std::vector<std::string>& a);
    void Flip(std::vector<std::string>& a);
    void RemoveFrames();
    void FindMonsters(std::vector<std::string> sea);
};

#endif