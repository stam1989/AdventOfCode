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
#include <iterator>
#include <algorithm>
#include <exception>
#include <sstream>
#include <csignal>
#include <cstdint>
#include <vector>
#include <array>
#include <map>
#include <utility>


static constexpr int ROW = 23;
static constexpr int COLUMN = 50;
using Panel = std::array<std::array<std::string, COLUMN>, ROW>;
using Tiles = std::map<std::pair<size_t, size_t>, std::string>;


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


enum TileId
{
    Empty = 0,          // No game object appears in this tile ('  ')
    Wall,               // Walls are indestructible barriers ('##')
    Block,              // Blocks can be broken by the ball ('**')
    HorizontalPaddle,   // The paddle is indestructible ('==')
    Ball                // The ball moves diagonally and bounces off objects ('()')
};

enum Joystick
{
    Left = -1,
    Neutral = 0,
    Right = 1
};


void InitializingMemory(std::vector<int64_t>& opcodes, const char* filename)
{
    std::cout << "InitializingMemory starts\n";

    opcodes.clear();
    std::ifstream input(filename);
    std::string code;

    if (input.is_open())
    {
        while (std::getline(input, code, ','))
        {
            opcodes.emplace_back(stoll(code, nullptr, 10));
        }
        input.close();
    }
    else
    {
        std::string exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "InitializingMemory finished\n";
}


void SetArgs(long &arg1, long& arg2, std::vector<int64_t> &opcodes, int& ip, std::vector<int>& param_modes, int& relative_base)
{
    arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] :
    ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

    arg2 = (param_modes[1] == 0) ? opcodes[opcodes[ip + 2]] :
    ((param_modes[1] == 1) ? opcodes[ip + 2] : opcodes[opcodes[ip + 2] + relative_base]);
}


void FillWithZeros(std::vector<int>& param_modes)
{
    while (param_modes.size() < 3)
    {
        param_modes.emplace_back(0);
    }
}


void SetMode(std::vector<int64_t>& opcodes, std::vector<int>& param_modes, int64_t& opcode, int ip)
{
    param_modes.clear();
    int temp;
    opcode = opcodes[ip] % 100;
    temp = opcodes[ip] / 100;

    while (temp)
    {
        param_modes.emplace_back(temp % 10);
        temp /= 10;
    }
}


void DrawTile(std::vector<int>& output, Tiles& tiles)
{
    std::string id;
    switch(output[2])
    {
        case Empty:
        {
            id = "  ";
            break;
        }
        case Wall:
        {
            id = "##";
            break;
        }
        case Block:
        {
            id = "**";
            break;
        }
        case HorizontalPaddle:
        {
            id = "==";
            break;
        }
        case Ball:
        {
            id = "()";
            break;
        }
        default:
        {
            throw std::runtime_error("Wrong tile id!!!!\n ");
        }
    }

    auto ret = tiles.insert(std::make_pair(std::make_pair(output[1], output[0]), id));

     if (ret.second == false)
     {
         throw std::runtime_error("DrawTile:: Could not add in tiles...\n");
     }

    output.clear();
}


void PrintPanel(const Panel &panel)
{
    // std::cout << "PrintPanel starts \n";

    for(auto& p : panel)
    {
        for (auto& spot : p)
        {
            std::cout << spot;
        }
        std::cout << std::endl;
    }
    // std::cout << "PrintPanel finished \n";
}


void DrawPanel(Panel &panel, const Tiles& tiles)
{
    for (const auto& t : tiles)
    {
        panel[t.first.first][t.first.second] = t.second;
    }
}


int MoveJoystick(const Tiles& tiles)
{
    // std::cout << "MoveJoystick starts!" << std::endl;

    auto it_ball = tiles.begin();
    for(it_ball; it_ball != tiles.end(); it_ball++)
    {
        if(it_ball->second == "()")
        {
            break;
        }
    }

    auto it_paddle = tiles.begin();
    for(it_paddle; it_paddle != tiles.end(); it_paddle++)
    {
        if(it_paddle->second == "==")
        {
            break;
        }
    }


    if (it_ball->first.first < it_paddle->first.first)
    {
        return -1;
    }
    else if (it_ball->first.first > it_paddle->first.first)
    {
        return 1;
    }
    else if (it_ball->first.first == it_paddle->first.first)
    {
        return 0;
    }
    else
    {
        throw std::runtime_error("MoveJoystick::Undefined behavior...");
    }
    

}


void Operation(std::vector<int64_t> opcodes, std::vector<int>& output, Tiles& tiles, size_t& score)
{
    int ip = 0, relative_base = 0;
    bool cont = true;
    std::vector<int> param_modes;
    while (ip < opcodes.size() && cont)
    {
        int64_t opcode = opcodes[ip];
        SetMode(opcodes, param_modes, opcode, ip);
        FillWithZeros(param_modes);

        switch (opcode)
        {
            case OP_ADD:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);

                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : opcodes[ip + 3] + relative_base);

                opcodes[pos] = arg1 + arg2;
                ip += 4;
                break;
            }
            case OP_MUL:
            {
                long arg1, arg2, pos;

                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : opcodes[ip + 3] + relative_base);

                opcodes[pos] = arg1 * arg2;

                ip += 4;
                break;
            }
            case OP_IN:
            {
                long pos;
                pos = (param_modes[0] == 0) ? opcodes[ip + 1] : ((param_modes[0] == 1) ? ip + 1 : opcodes[ip + 1] + relative_base);

                opcodes[pos] = MoveJoystick(tiles);
                ip += 2;
                break;
            }
            case OP_OUT:
            {

                long arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

                output.emplace_back(arg1);

                if (output.size() == 3)
                {
                    if (output[0] == -1 && output[1] == 0)
                    {
                        score = output[2];
                        ip += 2;
                        break;
                    }
                    DrawTile(output, tiles);
                }

                ip += 2;
                break;
            }
            case OP_JUMP_IF_TRUE:
            {
                long arg1, arg2;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);

                if (arg1 != 0)
                {
                    ip = arg2;
                    break;
                }

                ip += 3;
                break;
            }
            case OP_JUMP_IF_FALSE:
            {
                long arg1, arg2;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                if (arg1 == 0)
                {
                    ip = arg2;
                    break;
                }

                ip += 3;
                break;
            }
            case OP_LESS_THAN:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : opcodes[ip + 3] + relative_base);

                opcodes[pos] = (arg1 < arg2) ? 1 : 0;
                ip += 4;
                break;
            }
            case OP_EQUALS:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : opcodes[ip + 3] + relative_base);

                opcodes[pos] = (arg1 == arg2) ? 1 : 0;
                ip += 4;
                break;
            }
            case OP_REL_MODE:
            {
                long arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

                relative_base += arg1;

                ip += 2;
                break;
            }
            case OP_TERMINATE:
            {
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


void PrintOpcodes(std::vector<int64_t>& opcodes)
{
    std::cout << "PrintOpcodes starts \n";
    for (auto& opcode : opcodes)
    {
        std::cout << opcode << ",";
    }
    std::cout << "PrintOpcodes finished \n\n";
}


int main(int argc, char* argv[])
{
    try
    {
        std::vector<int64_t> opcodes;
        const char* filename("../resources/Day13.txt");

        InitializingMemory(opcodes, filename);
        opcodes.resize(3946333, 0);  // fill the rest of theopcode vector with zeros
        opcodes[0] = 2; // set first mem address to 2 to play for free

        // Panel panel(ROW, std::vector<std::string>(COLUMN, "  "));

        Panel panel;
        for (size_t col = 0; col < COLUMN; col++)
        {
            for (size_t row = 0; row< ROW; row++)
            {
                panel[row][col] = "  ";
            }
        }

        Tiles tiles;
        std::vector<int> output;
        size_t score = 0;

        while(1)
        {

            Operation(opcodes, output, tiles, score);
            DrawPanel(panel, tiles);
            PrintPanel(panel);

            std::cout << "-----00" << score << "-----\n\n\n";

            size_t count_blocks = 0;
            for (auto& tile : tiles)
            {
                if (tile.second == "**")
                {
                    count_blocks++;
                }
            }

            if (count_blocks == 0)
            {
                break;
            }
        }


    }
    catch (std::string& exception_string)
    {
        std::cout << exception_string << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}





