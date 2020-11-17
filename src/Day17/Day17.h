//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY17_H
#define DAY17_H


#include "Intcode.h"
#include <array>


class ASCII : public IntcodeProgram
{
public:
    ASCII(const char* filename) : IntcodeProgram(filename)
    , m_View()
    , m_Views()
    , m_Vacuum()
    , m_stage(0)
    , m_mainMovementRoutine("C,A,B,A,B,A")
    , m_movementFunctionA("L,6,R,12,L,6,L,10,L,10,R,6")
    , m_movementFunctionB("L,6,R,12,L,4,L,6,R,6")
    , m_movementFunctionC("L,6,R,12,R,6")
    {}

    virtual ~ASCII() = default;

    virtual int64_t OpInput() override;

    virtual bool OpOutput(int64_t output) override;
 
    struct VacuumRobot
    {
        void InitVacuum(int tx, int ty, char tfacing)
        {
            x = tx;
            y = ty;
            facing = tfacing;
        }

        int x, y;
        char facing;
    };

    void SetRobotsPosition();

    void PrintViews();
    
    int64_t LocateIntersections();

private:
    void InializePanel();

    int GetColumns();


private:
    std::vector<char> m_View;
    std::vector<std::vector<char>> m_Views;
    VacuumRobot m_Vacuum;
    int m_stage;    //this is used when intcode program asks for input to know in wich stage we are

    std::string m_mainMovementRoutine;
    std::string m_movementFunctionA;
    std::string m_movementFunctionB;
    std::string m_movementFunctionC;
}; 



#endif