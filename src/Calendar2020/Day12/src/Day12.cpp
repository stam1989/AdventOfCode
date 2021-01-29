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
#include <tuple>


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


std::string Day12::RotateShip(const NavInstructions& instr)
{
    std::vector<std::string> dirs_right({"E", "S", "W", "N"});
    std::vector<std::string> dirs_left({"E", "N", "W", "S"});

    std::vector<std::string> dirs = (instr.dir == "R") ? dirs_right : dirs_left;

    auto it = std::find(dirs.begin(), dirs.end(), m_ship.facing);
   
    int count = instr.step / 90;
    for(int i = 0; i < count; i++)
    {
        it++;
        if(it == dirs.end()) it = dirs.begin();
    }

    return *it;
}


void Day12::ExecuteInstructions() {
    for(const auto instr : m_instructions) {
        std::string direction;
        if(instr.dir == "F") direction = m_ship.facing;
        else if(instr.dir == "L" || instr.dir == "R") { m_ship.facing = RotateShip(instr); return; }
        else direction = instr.dir;

        if(direction == "N") m_ship.north += abs(instr.step);
        else if(direction == "S") m_ship.north -= abs(instr.step);
        else if(direction == "E") m_ship.east += abs(instr.step);
        else if(direction == "W") m_ship.east -= abs(instr.step);
    }
}


void Day12::RotateWaypoint(Point& waypoint, const NavInstructions& instr)
{
    std::vector<std::tuple<std::string, int, int>> dirs_right{{"NE", 1, 1}, {"SE", -1, 1}, {"SW", -1, -1}, {"NW", 1, -1}};
    std::vector<std::tuple<std::string, int, int>> dirs_left{{"NE", 1, 1}, {"NW", 1, -1}, {"SW", -1, -1}, {"SE", -1, 1}};

    std::vector<std::tuple<std::string, int, int>> dirs = (instr.dir == "R") ? dirs_right : dirs_left;

    auto it = std::find_if(dirs.begin(), dirs.end(), [&waypoint](const auto& d) {return std::get<0>(d) == waypoint.facing; });
   
    int count = instr.step / 90;
    for(int i = 0; i < count; i++)
    {
        it++;
        if(it == dirs.end()) it = dirs.begin();
        int temp_north = waypoint.north;
        waypoint.north = std::get<1>(*it) * abs(waypoint.east);
        waypoint.east = std::get<2>(*it) * abs(temp_north);
        waypoint.facing = std::get<0>(*it);
    }
}


void Day12::MoveWaypoint(Point& waypoint, const NavInstructions& instr)
{
    if(instr.dir == "N")
    {
        waypoint.north += abs(instr.step);
        if (waypoint.north > 0)
        {
            if(waypoint.facing == "SE") waypoint.facing = "NE";
            else if(waypoint.facing == "SW") waypoint.facing = "NW";
        }
    }
    else if(instr.dir == "S")
    {
        waypoint.north -= abs(instr.step);
        if (waypoint.north < 0)
        {
            if(waypoint.facing == "NE") waypoint.facing = "SE";
            else if(waypoint.facing == "NW") waypoint.facing = "SW";
        }
    }
    else if(instr.dir == "E")
    {
        waypoint.east += abs(instr.step);
        if (waypoint.east > 0)
        {
            if(waypoint.facing == "NW") waypoint.facing = "NE";
            else if(waypoint.facing == "SW") waypoint.facing = "SE";
        }
    }
    else if(instr.dir == "W")
    {
        waypoint.east -= abs(instr.step);
        if (waypoint.east < 0)
        {
            if(waypoint.facing == "NE") waypoint.facing = "NW";
            else if(waypoint.facing == "SE") waypoint.facing = "SW";
        }    
    }
}


void Day12::ExecuteInstructions(Point& waypoint)
{
    for(const auto instruction : m_instructions)
    {
        if(instruction.dir == "F")
        {
            m_ship.north += abs(instruction.step) * waypoint.north;
            m_ship.east += abs(instruction.step) * waypoint.east;
        }
        else if(instruction.dir == "L" || instruction.dir == "R") RotateWaypoint(waypoint, instruction);
        else MoveWaypoint(waypoint, instruction);
    }
}



int main()
{
    Day12 d;
    // d.PrintInstructions();

    // d.ExecuteInstructions();
    // std::cout << "The ship"s Manhattan distance is: " << d.GetShipsDistance() << "!\n";

    Day12::Point wp(10, 1, "NE");
    d.ExecuteInstructions(wp);
    std::cout << "The ship's Manhattan distance using the waypoint is: " << d.GetShipsDistance() << "!\n";
    return 0;
}