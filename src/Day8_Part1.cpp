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
#include <exception>


using Layers = std::vector<std::vector<std::vector<char>>>;
using Layer = std::vector<std::vector<char>>;
static constexpr size_t WIDE = 3;
static constexpr size_t TALL = 2;
static constexpr char FILENAME[] = "../../../resources/Day8.txt";

Layers ReadFile()
{
	Layers layers;
	Layer layer;
	std::vector<char> row;
	char ch;
	std::ifstream input(FILENAME);
	
	input.seekg (0, input.end);
	int length = input.tellg();
	input.seekg(0, input.beg);
	int counter = 0;

	if (input.is_open())
	{
		while(1)
		{
		
		for (int tall = 0; tall < TALL; tall++)
		{
			for (int wide = 0; wide < WIDE; wide++)
			{
				if(length == counter)
				{
					break;
				}
				input >> std::skipws >> ch;
				row.emplace_back(ch);
				++counter;
			}
			layer.emplace_back(row);
			if(length == counter)
			{
				break;
			}
		}
		if(length == counter)
		{
			break;
		}
		}
		layers.emplace_back(layer);
		input.close();
	}
		
// 		input.seekg (0, input.end);
// 		int length = input.tellg();
// 		input.seekg(0, input.beg);
// 		int counter = 0;
// 		std::cout << "before" <<std::endl;
// 		for (int tall = 0; tall < TALL; tall++)
// 		{
// 			std::cout << "in first" <<std::endl;
// 			for (int wide = 0; wide < WIDE; wide++)
// 			{		
// 				
// 				
// 				
// 				input.read(ch, 1);
// 				std::cout << "in second" <<std::endl;
// 				row.emplace_back(ch);
// 				++counter;
// 			}
// 			layer.emplace_back(row);
// 			if (counter == length)
// 			{
// 				break;
// 			}
// 		}
// 		input.close();
// 	}
	else
	{
		std::string exception_string =  "Could not open input file";
		throw std::runtime_error(exception_string);
	}
	return layers;
}

void PrintLayers(Layers layers)
{
	for(auto& layer : layers)
	{
		std::cout << "Layers: ";
		for(auto& row : layer)
		{
			std::cout << "Row 1: ";
			for (auto& ch : row)
			{	
				std::cout << ch;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

int main()
{
	
	Layers layers;
	try
	{	
		layers = ReadFile();
	}
	catch(std::string& exception_string)
	{
		std::cout << exception_string << std::endl;
	}
	
	PrintLayers(layers);
	
	
	return 0;
}
