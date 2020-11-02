#include "Intcode2.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <exception>

typedef std::vector<Intcode::Tile> Tiles;


namespace Intcode
{


void InitializingMemory(std::vector<int64_t>& opcodes, std::string& filename)
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


void DrawTile(std::vector<uint8_t>& output, Tiles& tiles)
{
//     auto it = std::find_if(tiles.begin(), tiles.end(), [output](const Intcode::Tile& t) {
//         return t.x == output[0] && t.y == output[1];
//     });


    int id;
    switch(output[2])
    {
        case Empty:
        {
            id = 46;
            break;
        }
        case Wall:
        {
            id = 35;
            break;
        }
        case Block:
        {
            id = 42;
            break;
        }
        case HorizontalPaddle:
        {
            id = 80;
            break;
        }
        case Ball:
        {
            id = 66;
            break;
        }
        default:
        {
            throw std::runtime_error("Wrong tile id!!!!\n ");
        }
    }

    Tile temp_tile(output[0], output[1], id);
    tiles.emplace_back(temp_tile);

    output.clear();
}

void Operation(std::vector<int64_t> opcodes, std::vector<uint8_t>& output, Tiles& tiles)
{
    int ip = 0, relative_base = 0;
    bool cont = true;
    std::vector<int> param_modes;
    while (ip < opcodes.size() && cont)
    {
        //         if (ip == 324)
        //         {
        //             std::raise(SIGINT);
        //         }
        int64_t opcode = opcodes[ip];
        SetMode(opcodes, param_modes, opcode, ip);
        FillWithZeros(param_modes);

        switch (opcode)
        {
            case OP_ADD:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, opcodes, ip, param_modes, relative_base);

                pos = (param_modes[2] == 0) ? opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : opcodes[ip + 3] + 		relative_base);

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

                if (output.empty())
                {
                    throw std::range_error("Empty output queue!");
                }

                opcodes[pos] = output.front();
                output.erase(output.begin());
                ip += 2;
                break;
            }
            case OP_OUT:
            {

                long arg1 = (param_modes[0] == 0) ? opcodes[opcodes[ip + 1]] : ((param_modes[0] == 1) ? opcodes[ip + 1] : opcodes[opcodes[ip + 1] + relative_base]);

                output.emplace_back(arg1);

                if (output.size() == 3)
                {
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

} // namespace Intcode
