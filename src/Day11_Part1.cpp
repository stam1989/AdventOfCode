//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>
#include <exception>
#include <sstream>
#include <map>
#include <queue>


static constexpr char FILENAME[] = "../../../resources/Day11.txt";
static constexpr int row = 500;
static constexpr int column = 500;

enum OpCode
{
    OP_ADD = 1, // adds together numbers read from two positions and stores the result in a third position
    OP_MUL = 2, // multiplies together numbers read from two positions and stores the result in a third position
    OP_IN = 3,  // takes a single integer as input and saves it to the position given by its only parameter
    OP_OUT = 4, // outputs the value of its only parameter
    OP_JUMP_IF_TRUE = 5,  // if the first parameter is non-zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
    OP_JUMP_IF_FALSE = 6, // if the first parameter is zero, it sets the instruction pointer to the value from the second parameter. Otherwise, it does nothing.
    OP_LESS_THAN = 7, // if the first parameter is less than the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
    OP_EQUALS = 8, // if the first parameter is equal to the second parameter, it stores 1 in the position given by the third parameter. Otherwise, it stores 0.
    OP_REL_MODE = 9, //adjusts the relative base by the value of its only parameter. The relative base increases (or decreases, if the value is negative) by the value of the parameter.
    OP_TERMINATE = 99 // the program is finished and should immediately halt
};
/// 2 == relative mode
/// 1 == immediate mode
/// 0 == position mode

void InitializingMemory(std::vector<long>& opcodes)
{
    opcodes.clear();
    std::ifstream input(FILENAME);
    std::string code;
    try
    {
        if (input.is_open())
        {
            while (std::getline(input, code, ','))
            {
                opcodes.push_back(stol(code, nullptr, 10));
            }
            input.close();
        }
        else
        {
            std::string exception_string =  "Could not open input file";
            throw std::runtime_error(exception_string);
        }
    }
    catch(std::string& exception_string)
    {
        std::cout << exception_string << std::endl;
    }
}

void InitializePanel(std::string panel[][500])
{
    for (int x = 0; x < column; x++)
    {
        for  (int y = 0; y < row; y++)
        {
            panel[x][y] = ".";
        }
    }

}

void FillWithZeros(std::vector<int>& param_modes)
{
    while (param_modes.size() < 3)
    {
        param_modes.emplace_back(0);
    }
}

void SetMode(std::vector<long>& opcodes, std::vector<int>& param_modes, long& opcode, int ip)
{
    int temp;
    opcode = opcodes[ip] % 500;
    temp = opcodes[ip] / 500;

    while (temp)
    {
        param_modes.emplace_back(temp % 10);
        temp /= 10;
    }
}

void SetArgs(long &arg1, long& arg2, std::vector<long> &opcodes, int& ip, std::vector<int>& param_modes, int& relative_base)
{

    arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] :
    ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

    arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] :
    ((param_modes[1] == 1) ? opcodes[ip + 2] : opcodes[opcodes[ip + 2] + relative_base]);

    // 	std::cout << "arg1: " << arg1 << std::endl;

    // 	std::cout << "SetArgs:: arg1: " << arg1 << ", arg2: " << arg2<< ", relative base: " << relative_base << std::endl;
}


enum Face
{
    UP = 1,
    DOWN,
    RIGHT,
    LEFT
};

struct HullRobot
{
    HullRobot() : x(column / 2), y(row / 2), face(Face::UP) {}
    HullRobot(int pos_x, int pos_y) : x(pos_x), y(pos_y), face(Face::UP) {}

    int x, y;
    Face face;
};

enum Color
{
    BLACK = 0,
    WHITE
};

enum Direction
{
    MOVE_LEFT = 0,   // 90 degrees left
    MOVE_RIGHT       // 90 degrees right
};

void PaintAndMoveRobot(HullRobot& robot, std::string panel[][500], std::queue<long>& output)
{
    panel[robot.x][robot.y] = (output.front() == 0) ? "." : "#";
    output.pop();

    if (output.front() == static_cast<long>(Direction::MOVE_LEFT))
    {
        switch(static_cast<int>(robot.face))
        {
            case Face::UP :
            {
                robot.face = Face::LEFT;
                robot.x--;
                break;
            }
            case Face::DOWN :
            {
                robot.face = Face::RIGHT;
                robot.x++;
                break;
            }
            case Face::RIGHT :
            {
                robot.face = Face::UP;
                robot.y++;
                break;
            }
            case Face::LEFT :
            {
                robot.face = Face::DOWN;
                robot.y--;
                break;
            }
            default :
            {
               std:: cout << "Wrong facing!\n\n";
            }
        }
    }
    else
    {
        switch(static_cast<int>(robot.face))
        {
            case Face::UP :
            {
                robot.face = Face::RIGHT;
                robot.x++;
                break;
            }
            case Face::DOWN :
            {
                robot.face = Face::LEFT;
                robot.x--;
                break;
            }
            case Face::RIGHT :
            {
                robot.face = Face::DOWN;
                robot.y--;
                break;
            }
            case Face::LEFT :
            {
                robot.face = Face::UP;
                robot.y++;
                break;
            }
            default :
            {
                std:: cout << "Wrong facing!\n\n";
            }
        }
    }
    output.pop();

    auto color = (panel[robot.x][robot.y] == ".") ? 0 : 1;
    output.emplace(color);
}


void Operation(std::vector<long> opcodes, std::queue<long>& output, HullRobot& robot, std::string panel[][500], int& res)
{
    int op_in_counter = 0, ip = 0, relative_base = 0;
    bool cont = true;
    while (ip < opcodes.size() && cont)
    {
        long opcode = opcodes[ip];
        std::vector<int> param_modes;
        SetMode(opcodes, param_modes, opcode, ip);
        FillWithZeros(param_modes);
        // 		std::cout << "opcode: " << opcode << std::endl;
        switch (opcode)
        {
            case OpCode::OP_ADD:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);

                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : opcodes[ip + 3] + 		relative_base);


                opcodes[pos] = arg1 + arg2;
                // 				std::cout << "OP_ADD:: Opcode: " << opcode << ", opcodes[opcodes[ip + 3]]: " << opcodes[opcodes[ip + 3]] << ", arg1:" << arg1 << ", arg2: " << arg2 << ", pos: " << pos << std::endl;
                ip += 4;
                break;
            }
            case OpCode::OP_MUL:
            {
                long arg1, arg2, pos;

                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : opcodes[ip + 3] + relative_base);

                opcodes[pos] = arg1 * arg2;
                // 				std::cout << "OP_MUL:: para modes: " << param_modes.size() << ", Opcode: " << opcode << ", opcodes[opcodes[ip + 3]]: " << opcodes[pos] << ", arg1:" << arg1 << ", arg2: " << arg2 << ", pos: " << pos << std::endl;

                ip += 4;
                break;
            }
            case OpCode::OP_IN:
            {
                long temp, pos;
                pos = (param_modes[0] == 0) ? opcodes[ip + 1] : ((param_modes[0] == 1) ? ip + 1 : opcodes[ip + 1] + relative_base);

                if (output.empty())
                {
                    throw std::range_error("Empty output queue!");
                }
                opcodes[pos] = output.front();
                output.pop();
                ip += 2;
                break;
            }
            case OpCode::OP_OUT:
            {

                long arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

                int pos = (param_modes[0] == 0) ? opcodes[ip + 1] : ((param_modes[0] == 1) ? (ip + 1) : relative_base + opcodes[ip + 1]);

                output.emplace(arg1);
//                 std::cout << "OP_OUT:: Position " << pos << ", num: " << arg1 << std::endl;
                if (output.size() == 2)
                {
                    res++;
                    PaintAndMoveRobot(robot, panel, output);
                }
                ip += 2;
                break;
            }
            case OpCode::OP_JUMP_IF_TRUE:
            {
                long arg1, arg2;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                // 				std::cout << "OP_JUMP_IF_TRUE:: Opcode: " << opcode << ", param[0]" << param_modes[0] << ", arg1:" << arg1 << ", arg2: " << arg2 << std::endl;
                if (arg1 != 0)
                {
                    ip = arg2;
                    break;
                }

                ip += 3;
                break;
            }
            case OpCode::OP_JUMP_IF_FALSE:
            {
                long arg1, arg2;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                if (arg1 == 0)
                {
                    ip = arg2;
                    break;
                }
                // 				std::cout << "OP_JUMP_IF_FALSE:: Opcode: " << opcode  << ", arg1:" << arg1 << ", arg2: " << arg2 << std::endl;
                ip += 3;
                break;
            }
            case OpCode::OP_LESS_THAN:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : opcodes[ip + 3] + relative_base);

                // 				std::cout << "OP_LESS_THAN:: pos: " << pos << ", arg1:" << arg1 << ", arg2: " << arg2 << std::endl;
                opcodes[pos] = (arg1 < arg2) ? 1 : 0;
                ip += 4;
                break;
            }
            case OpCode::OP_EQUALS:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : opcodes[ip + 3] + relative_base);

                opcodes[pos] = (arg1 == arg2) ? 1 : 0;
                // 				std::cout << "OP_EQUALS:: Opcode: " << opcode<< ", pos: " << pos   << ", arg1:" << arg1 << ", arg2: " << arg2 << std::endl;
                ip += 4;
                break;
            }
            case OpCode::OP_REL_MODE:
            {
                long arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

                relative_base += arg1;

                // 				std::cout << "OP_REL_MODE:: Opcode: " << opcode  << ", arg1:" << arg1 << ", relative_base: " << relative_base << std::endl;
                ip += 2;
                break;
            }
            case OpCode::OP_TERMINATE:
            {
                // 			std::cout << "Terminate!!\n";
                cont = false;
                break;
            }
            default:
            {
                std::stringstream ss;
                ss << "wrong opcode!!!!\n ";
                ss << "OPCODE: " << opcode << "\n";
                ss << "Program counter: " << ip << "\n";
                throw std::runtime_error(ss.str());
            }
        }
    }
}

void PrintOpcodes(std::vector<long>& opcodes)
{
    for (auto& opcode : opcodes)
    {
        std::cout << opcode << ",";
    }
    std::cout << std::endl;
}

void PrintPanel(std::string panel[][500])
{
    std::cout << "\n\n\n";
    for (int x = 0; x < column; x++)
    {
        for  (int y = 0; y < row; y++)
        {
            std::cout << panel[x][y];
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::cout << "opcodes\n\n";
    std::vector<long> opcodes(344633390, 0);

    std::cout << "output\n\n";
    std::queue<long> output;

    std::cout << "InitializingMemory\n\n";
    InitializingMemory(opcodes);
//     PrintOpcodes(opcodes);

    std::cout << "panel\n\n";
    std::string panel[column][row];

    std::cout << "InitializePanel\n\n";
    InitializePanel(panel);

    int res = 0;
    std::cout << "asdsasd\n\n";
//     PrintPanel(panel);
    HullRobot robot;

    auto color = (panel[robot.x][robot.y] == ".") ? 0 : 1;
    output.emplace(color);
    std::cout << output.front() << std::endl;
    Operation(opcodes, output, robot, panel, res);

    std::cout << "Result is: " << res;

    return 0;
}



