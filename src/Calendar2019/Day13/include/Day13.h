//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY13_H
#define DAY13_H

#include "Intcode.h"

#include <array>

static constexpr int ROW = 28;
static constexpr int COLUMN = 52;
using Panel = std::array<int, COLUMN * ROW>;

class Day13 : public IntcodeProgram
{
public:

    Day13(const char* filename) : IntcodeProgram(filename), m_Paddle(0), m_Ball(0), m_Score(0) { std::fill(m_Panel.begin(), m_Panel.end(), 0); }
    virtual ~Day13() = default;

    enum TileId
    {
        Empty = 0,          // No game object appears in this tile ('  ')
        Wall,               // Walls are indestructible barriers ('##')
        Block,              // Blocks can be broken by the ball ('**')
        HorizontalPaddle,   // The paddle is indestructible ('==')
        Ball                // The ball moves diagonally and bounces off objects ('()')
    };

    virtual int64_t OpInput() override;

    virtual bool OpOutput(int64_t output) override;

    void PrintPanel();

    inline int64_t GetScore() { return m_Score; }

    inline bool IsPanelClear() { return std::find(m_Panel.begin(), m_Panel.end(), 2) == m_Panel.end(); }

    inline size_t CountBlocks() { return std::count_if(m_Panel.begin(), m_Panel.end(), [](const int tile) { return tile == 2; }); }

private:
    void DrawTile();

    int MoveJoystick();


    Panel m_Panel;
    std::vector<int64_t> m_Output;
    int64_t m_Paddle, m_Ball, m_Score;
};


#endif
