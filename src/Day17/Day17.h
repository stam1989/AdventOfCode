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

// static constexpr size_t COLUMN = 50;
// static constexpr size_t ROW = 50;
// using Panel = std::array<std::array<std::string, ROW>, COLUMN>;

class ASCII : public IntcodeProgram
{
public:
    ASCII(const char* filename) : IntcodeProgram(filename) {  }
    virtual ~ASCII() = default;

    // struct VacuumRobot
    // {
    //     VacuumRobot() {}
    //     ~VacuumRobot() {}

    //     int x, y;
    //     char facing;
    // };


    // void PrintPanel();

    // enum Code
    // {

    // };

    void PrintView();
    
    virtual int64_t OpInput() override;

    virtual bool OpOutput(int64_t output) override;

    inline std::vector<char> GetView() { return m_View; }

private:
    void InializePanel();

private:
    // Panel m_Panel;
    std::vector<char> m_View;
    // VacuumRobot m_Vacuum;
}; 



#endif