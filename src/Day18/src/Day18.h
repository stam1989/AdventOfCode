//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY_H
#define DAY_H

#include <vector>
#include <set>

class Day18
{
public:
    Day18() : m_map(), m_pos(), m_steps(0) { ScanMap(); InitPosition(); }
    ~Day18() = default;


    enum Direction
    {
        Up = 0,
        Down,
        Left,
        Right,
        DIR_END
    };

    struct Point
    {
        Point() : x(0), y(0), prev_x(-1), prev_y(-1) {}
        int x, y, prev_x, prev_y;
    };

    void PrintMap();
    void Move(Direction dir);

private:
    void ScanMap();

    void InitPosition();

    bool IsAllCollected();

    int NextPosition();


    std::vector<std::vector<char>> m_map;
    Point m_pos;
    int m_steps;
    static constexpr char* const FILENAME = "../src/Day18/resources/Day18.txt";
};

#endif