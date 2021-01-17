//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day13.h"

#include <chrono>
#include <thread>
#include <iostream>


void Day13::DrawTile()
{
    m_Panel[m_Output[0] + (m_Output[1] * COLUMN)] = m_Output[2];
    m_Output.clear();
}


void Day13::PrintPanel()
{
    // std::cout << "PrintPanel starts \n";

    const char* tile[] = {"  ", "##", "**", "==", "()"};

    for(int r = 0, n = 0; r < ROW; r++)
    {
        for (int c = 0; c < COLUMN; c++, n++)
        {
            std::cout << tile[m_Panel[n]];
        }
        std::cout << std::endl;
    }

    // std::cout << "PrintPanel finished \n";
}



int Day13::MoveJoystick()
{
    if (m_Paddle > m_Ball) { return -1; }
    else if (m_Paddle < m_Ball) { return 1; }
    else { return 0; }
}


int64_t Day13::OpInput()
{
    return MoveJoystick();
}


bool Day13::OpOutput(int64_t output)
{
    m_Output.emplace_back(output);



    if(m_Output.size() == 3)
    {
        if (m_Output[0] == -1 && m_Output[1] == 0)
        {
            m_Score = m_Output[2];
            m_Output.clear();
            PrintPanel();
            std::cout << "-----000" << m_Score << "-----\n\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
            return false;
        }

        if (m_Output[2] == 3)
        {
            m_Paddle = m_Output[0];
        }
        else if (m_Output[2] == 4)
        {
            m_Ball = m_Output[0];
            PrintPanel();
            std::cout << "-----000" << m_Score << "-----\n\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }

        DrawTile();
        

    }
    return false;
}