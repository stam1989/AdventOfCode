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
#include <string>

using SeatLayout = std::vector<std::vector<char>>;

class Day12
{
public:
    Day12() { ReadFile(); }

    struct NavInstructions
    {
        std::string dir;
        int step;
    };

        
    struct Point
    {
        Point(): east(0), north(0), facing("E") {}
        Point(int e, int n, std::string f) : east(e), north(n), facing(f) {}

        int east, north;
        std::string facing;
    };

    void PrintInstructions();
    void ExecuteInstructions();
    void ExecuteInstructions(Point& waypoint);
    inline int32_t GetShipsDistance() { return abs(m_ship.north) + abs(m_ship.east); } 

private:
    std::vector<NavInstructions> m_instructions;
    Point m_ship;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day12/resources/Day12.txt";

    void ReadFile();
    std::string RotateShip(const NavInstructions& instr);
    void RotateWaypoint(Point& waypoint, const NavInstructions& instr);
    void MoveWaypoint(Point& waypoint, const NavInstructions& instr);

};


#endif