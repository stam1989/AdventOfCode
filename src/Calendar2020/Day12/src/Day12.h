//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY12_H
#define DAY12_H

#include <vector>
#include <cstdlib>

using SeatLayout = std::vector<std::vector<char>>;

class Day12
{
public:
    Day12() { ReadFile(); }

    void PrintInstructions();
    void ExecuteInstructions();

    struct NavInstructions
    {
        char dir;
        int step;
    };

    struct Ship
    {
        Ship(): north(0), east(0), facing('E') {}

        int north, east;
        char facing;
    };

    inline int32_t GetShipsDistance() { return abs(m_ship.north) + abs(m_ship.east); } 

private:
    std::vector<NavInstructions> m_instructions;
    Ship m_ship;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day12/resources/Day12.txt";

    void ReadFile();
    void MoveShip(const NavInstructions& instr);
    char GetDir(const NavInstructions& instr);
};


#endif