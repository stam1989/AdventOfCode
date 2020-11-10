//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Day17.h"

#include <iostream>

// void ASCII::InializePanel()
// {
//     for (size_t col = 0; col < COLUMN; col++)
//     {
//         for (size_t row = 0; row< ROW; row++)
//         {
//             if(col == m_Vacuum.x && row == m_Vacuum.x)
//             {
//                 if (m_Panel[col][row] == ".")
//                     std::cout << "X";   // vacuum robot tumbling through space uncontrollably
//                 else
//                 {
//                     std::cout << m_Vacuum.facing;    // vacuum robot on a scaffold
//                 }
                
//             }
//             m_Panel[col][row] = ".";
//         }
//     }
// }


// void ASCII::PrintPanel()
// {
//     for (size_t col = 0; col < COLUMN; col++)
//     {
//         for (size_t row = 0; row< ROW; row++)
//         {
//             std::cout << m_Panel[col][row];
//         }
//         std::cout << "\n";
//     }
// }


void ASCII::PrintView()
{
    std::cout << "Print View:\n";
    for (const auto& v : m_View)
        std::cout << v;
}


int64_t ASCII::OpInput()
{

    return 1;
}

bool ASCII::OpOutput(int64_t output)
{
    switch (output)
    {
        case 35:
            m_View.emplace_back('#');
            break;
        case 46:
            m_View.emplace_back('.');
            break;
        case 10:
            m_View.emplace_back('\n');
            break;
        default:
            std::cout << "View size: " << m_View.size() << std::endl;
            
            PrintView();
            throw std::invalid_argument("ASCII::OpOutput invalid view arg...");
            break;
    }
    
    return false;
}