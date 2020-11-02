#include "Intcode.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <exception>


void IntcodeProgram::InitializeMemory()
{
    std::cout << "InitializingMemory starts\n";

    m_opcodes.clear();
    std::ifstream input(m_filename);
    std::string code;

    if (input.is_open())
    {
        while (std::getline(input, code, ','))
        {
            m_opcodes.emplace_back(stoll(code, nullptr, 10));
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


void IntcodeProgram::SetArgs(long &arg1, long& arg2, int& ip, std::vector<int>& param_modes, int& relative_base)
{
    arg1 = (param_modes[0] == 0) ? m_opcodes[m_opcodes[ip + 1]] :
    ((param_modes[0] == 1) ? m_opcodes[ip + 1] : m_opcodes[m_opcodes[ip + 1] + relative_base]);

    arg2 = (param_modes[1] == 0) ? m_opcodes[m_opcodes[ip + 2]] :
    ((param_modes[1] == 1) ? m_opcodes[ip + 2] : m_opcodes[m_opcodes[ip + 2] + relative_base]);
}


void IntcodeProgram::FillWithZeros(std::vector<int>& param_modes)
{
    while (param_modes.size() < 3)
    {
        param_modes.emplace_back(0);
    }
}


void IntcodeProgram::SetMode(std::vector<int>& param_modes, int64_t& opcode, int ip)
{
    param_modes.clear();
    int temp;
    opcode = m_opcodes[ip] % 100;
    temp = m_opcodes[ip] / 100;

    while (temp)
    {
        param_modes.emplace_back(temp % 10);
        temp /= 10;
    }
}


void IntcodeProgram::Operation()
{
    int ip = 0, relative_base = 0;
    bool cont = true;
    std::vector<int> param_modes;
    while (ip < m_opcodes.size() && cont)
    {
        //         if (ip == 324)
        //         {
        //             std::raise(SIGINT);
        //         }
        int64_t opcode = m_opcodes[ip];
        SetMode(param_modes, opcode, ip);
        FillWithZeros(param_modes);

        switch (opcode)
        {
            case OpCode::OP_ADD:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, ip, param_modes, relative_base);

                pos = (param_modes[2] == 0) ? m_opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : m_opcodes[ip + 3] + 		relative_base);

                m_opcodes[pos] = arg1 + arg2;
                ip += 4;
                break;
            }
            case OpCode::OP_MUL:
            {
                long arg1, arg2, pos;

                SetArgs(arg1, arg2, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? m_opcodes[ip + 3] : ((param_modes[2] == 1) ? (ip + 3) : m_opcodes[ip + 3] + relative_base);

                m_opcodes[pos] = arg1 * arg2;

                ip += 4;
                break;
            }
            case OpCode::OP_IN:
            {
                long pos;
                pos = (param_modes[0] == 0) ? m_opcodes[ip + 1] : ((param_modes[0] == 1) ? ip + 1 : m_opcodes[ip + 1] + relative_base);

                m_opcodes[pos] = OpInput();

                ip += 2;
                break;
            }
            case OpCode::OP_OUT:
            {
                long arg1 = (param_modes[0] == 0) ? m_opcodes[m_opcodes[ip + 1]] : ((param_modes[0] == 1) ? m_opcodes[ip + 1] : m_opcodes[m_opcodes[ip + 1] + relative_base]);

                if(OpOutput(arg1))
                {
                    return;
                }
                
                ip += 2;
                break;
            }
            case OpCode::OP_JUMP_IF_TRUE:
            {
                long arg1, arg2;
                SetArgs(arg1, arg2, ip, param_modes, relative_base);

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
                SetArgs(arg1, arg2, ip, param_modes, relative_base);
                if (arg1 == 0)
                {
                    ip = arg2;
                    break;
                }

                ip += 3;
                break;
            }
            case OpCode::OP_LESS_THAN:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? m_opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : m_opcodes[ip + 3] + relative_base);

                m_opcodes[pos] = (arg1 < arg2) ? 1 : 0;
                ip += 4;
                break;
            }
            case OpCode::OP_EQUALS:
            {
                long arg1, arg2, pos;
                SetArgs(arg1, arg2, ip, param_modes, relative_base);
                pos = (param_modes[2] == 0) ? m_opcodes[ip + 3] : ((param_modes[2] == 1) ? ip + 3 : m_opcodes[ip + 3] + relative_base);

                m_opcodes[pos] = (arg1 == arg2) ? 1 : 0;
                ip += 4;
                break;
            }
            case OpCode::OP_REL_MODE:
            {
                long arg1 = (param_modes[0] == 0) ? m_opcodes[m_opcodes[ip + 1]] : ((param_modes[0] == 1) ? m_opcodes[ip + 1] : m_opcodes[m_opcodes[ip + 1] + relative_base]);

                relative_base += arg1;

                ip += 2;
                break;
            }
            case OpCode::OP_TERMINATE:
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


void IntcodeProgram::PrintOpcodes()
{
    std::cout << "Printm_opcodes starts \n";
    for (auto& opcode : m_opcodes)
    {
        std::cout << opcode << ",";
    }
    std::cout << "Printm_opcodes finished \n\n";
}