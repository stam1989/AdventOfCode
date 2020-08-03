//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Intcode.cpp"

#include <memory>
#include <iostream>


int main(int argc, char* argv[])
{
    try
    {
        std::vector<uint8_t> output;
        std::vector<int64_t> opcodes;


        std::string filename("../../../resources/Day13.txt");
        Intcode::InitializingMemory(opcodes, filename);
        opcodes.resize(39463339, 0);  // fill the rest of theopcode vector with zeros

        Intcode::Operation(opcodes, output);
        std::cout << "Day13\n\n";
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




