//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef DAY15_H
#define DAY15_H

#include "Intcode.h"

#include <array>
#include <stack>
#include <set>


static constexpr size_t COLUMN = 50;
static constexpr size_t ROW = 50;
using Panel = std::array<std::array<std::string, ROW>, COLUMN>;

class Maze : public IntcodeProgram
{ 
public:
    Maze(const char* filename) : IntcodeProgram(filename) { InializePanel(); }
    virtual ~Maze() = default;

public:
    enum Direction
    {
        NORTH = 1,
        SOUTH = 2,
        WEST = 3,
        EAST = 4
    };

    struct Droid
    {
        Droid() : x(ROW / 2), y(COLUMN / 2), start_X(ROW / 2), start_Y(COLUMN / 2), backtrack_state(false) {}
        Droid(int tx, int ty, int t_startX, int t_startY) :
            x(tx), y(ty), start_X(t_startX), start_Y(t_startY), backtrack_state(false) {}
        Droid(const Droid& d) :
            x(d.x), y(d.y), start_X(d.start_X), start_Y(d.start_Y), backtrack_state(d.backtrack_state) {}
        ~Droid() = default;
        bool operator=(const Droid& d)
        {
            return x == d.x && y == d.y;
        }

        int x, y, start_X, start_Y;
        bool backtrack_state;
    };

// DFS
public:
    void PrintPanel();

    virtual int64_t OpInput() override;

    virtual bool OpOutput(int64_t status) override;

// DFS
private:
    void InializePanel();

    void FillBlock(const Direction& dir);

    uint8_t MoveToUnexplored();

    void MoveDroid(const Direction& dir);

    Direction Backtrack();


// Shortest Path
public:
    std::pair<int, int> GetOxygenPosition();

    inline std::pair<int, int> GetStartPoint()
    {
        return std::make_pair(m_Droid.start_X, m_Droid.start_Y);
    }

    void FindShortestPath(int cur_X, int cur_Y, std::pair<int, int> dest, int32_t curDistance, int32_t& minDistance);


// Shortest Path
private:

    // Check if it is possible to go to (x, y) from current position. The
    // function returns false if the cell has value 0 or already visited
    inline bool IsSafe(int x, int y)
    {
        auto it = m_Visited.find(std::make_pair(x, y));
        if (m_Panel[x][y] == "#" || it != m_Visited.end())
            return false;

        return true;
    }

    // if not a valid position, return false
    inline bool IsValid(int x, int y)
    {
        if (x < ROW && y < COLUMN && x >= 0 && y >= 0)
            return true;

        return false;
    }


// Part2 Fill with oxygen
public:
    void CaluclateTimeToFillOxygen(uint16_t& timeElapsed);


// Part2 Fill with oxygen
private:
    bool IsFullOfOxygen();

    void FillAdjacent();


private:
    // DFS
    Panel m_Panel;
    Droid m_Droid;
    std::stack<std::pair<int, int>> m_SuspendedVertexes;
    uint8_t m_Dir;

    // Shortest Path
    std::set<std::pair<int, int>> m_Visited;

};

#endif