//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day12.h"

#include <fstream>
#include <iostream>


void Day12::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        while (std::getline(inputFile, s_input))
        {
            NavInstructions ni;
            ni.dir = s_input[0];
            s_input.erase(0, 1);
            ni.step = stol(s_input);
            m_instructions.emplace_back(NavInstructions(ni));
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day12::PrintInstructions()
{
    for(const auto instruction : m_instructions) std::cout << instruction.dir << instruction.step << "\n";
}


char Day12::GetDir(const NavInstructions& instr)
{
    std::vector<char> dirs_right({'E', 'S', 'W', 'N'});
    std::vector<char> dirs_left({'E', 'N', 'W', 'S'});

    std::vector<char> dirs = (instr.dir == 'R') ? dirs_right : dirs_left;

    auto it = std::find(dirs.begin(), dirs.end(), m_ship.facing);
   
    int count = instr.step / 90;
    for(int i = 0; i < count; i++)
    {
        it ++;
        if(it == dirs.end()) it = dirs.begin();
    }

    return *it;
}


void Day12::MoveShip(const NavInstructions& instr)
{
    char direction;
    if(instr.dir == 'F') direction = m_ship.facing;
    else if(instr.dir == 'L' || instr.dir == 'R') { m_ship.facing = GetDir(instr); return; }
    else direction = instr.dir;

    if(direction == 'N') m_ship.north += abs(instr.step);
    else if(direction == 'S') m_ship.north -= abs(instr.step);
    else if(direction == 'E') m_ship.east += abs(instr.step);
    else if(direction == 'W') m_ship.east -= abs(instr.step);
}

void Day12::ExecuteInstructions() {
    for(const auto instruction : m_instructions) {
        MoveShip(instruction);
    }
}



int main()
{
    Day12 d;
    d.PrintInstructions();

    d.ExecuteInstructions();
    std::cout << "The ship's Manhattan distance is: " << d.GetShipsDistance() << "!\n";

    
    return 0;
}