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
#include <exception>
#include <algorithm>

using Layers = std::vector <std::string>;
static constexpr size_t WIDE = 25;
static constexpr size_t TALL = 6;
static constexpr char FILENAME[] = "../../../resources/Day8.txt";


static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

Layers ReadFile()
{
    Layers layers;
    std::ifstream input(FILENAME);

    if (input.is_open())
    {
        std::string content( (std::istreambuf_iterator<char>(input) ),
                             (std::istreambuf_iterator<char>()    ) );

        for (int i = 0; i < content.size(); i += WIDE * TALL)
        {
            std::string line = content.substr(i, WIDE * TALL);
            ltrim(line);

            if(!line.empty())
            {
                layers.emplace_back(line);
            }
        }
        input.close();
    }
    else
    {
        std::string exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    return layers;
}

void PrintLayers(Layers layers)
{
    int counter = 0;
    for (auto x : layers)
    {
        std::cout << "Layer " << counter << ": " << x << std::endl;
        counter++;
    }
}

int CountZeros(Layers &layers)
{
    int count_zeros = 10000, res;

    for (auto& layer : layers)
    {
        int temp = std::count(layer.begin(), layer.end(), '0');
        if (count_zeros > temp)
        {
            count_zeros = temp;
            res = std::count(layer.begin(), layer.end(), '1') * std::count(layer.begin(), layer.end(), '2');
        }
    }
    return res;
}

void DecodeLayers(Layers layers, std::string& decoded_image)
{
    for (auto &layer : layers)
    {
        int pos = 0;
        for (char& ch : layer)
        {
            if (ch != '2' && decoded_image.at(pos) == '2')
            {
                decoded_image.at(pos) = ch;
            }
            ++pos;
        }
    }
}

void PrintImage(std::string &decoded_image)
{
    int counter = 1;
    for (auto c : decoded_image)
    {
        std::cout << ((c == '0')? "  ": ((c == '1')? "##": "??"));
        if (counter % 25 == 0)
        {std::cout << std::endl;}
        counter++;
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

    std::string decoded_image(WIDE * TALL, '2');
    DecodeLayers(layers, decoded_image);
    PrintImage(decoded_image);

    std::cout << "Length: " << decoded_image.size() << std::endl;

    return 0;
}

