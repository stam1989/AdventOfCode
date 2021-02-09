//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day17.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>


void Day17::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        InitCubeMap();
        int32_t y = 0, z = 0, w = 0;
        while (std::getline(inputFile, s_input)) {
            int32_t x = 0;
            std::vector<char> temp_line;
            for (const auto c : s_input) {
                int64_t offset_x = xSize / 2, offset_y = ySize / 2, offset_z = zSize / 2, offset_w = wSize / 2;
                m_cubeMap3D[z + offset_z][y + offset_y][x + offset_x] = c;
                m_cubeMap4D[w + offset_w][z + offset_z][y + offset_y][x + offset_x] = c;
                x++;
            }
            y++;
        }

        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day17::InitCubeMap() {
    std::vector<char> d(xSize, '.');
    std::vector<std::vector<char>> dd(ySize, d);
    CubeMap3D ddd(zSize, dd) ;
    CubeMap4D dddd(wSize, ddd);

    m_cubeMap3D = ddd;
    m_cubeMap4D = dddd;
}


void Day17::PrintCubeMap3D() {
    for (const auto& cube : m_cubeMap3D) {
        for (const auto el : cube) {
            for (const auto c : el) {
                std::cout << c;
            }
        std::cout << "\n";
        }
    std::cout << "\n";
    }
}

void Day17::PrintCubeMap4D() {
    int w = 0;
    for (const auto& cubeMap3D : m_cubeMap4D) {
        int z = 0;
        for (const auto& cube : cubeMap3D) {
            std::cout << "z=" << z << ", w=" << w << "\n";
            for (const auto el : cube) {
                for (const auto c : el) {
                    std::cout << c;
                }
            std::cout << "\n";
            }
            std::cout << "\n";
            z++;
        }
        w++;
        std::cout << "\n\n----------------------------------------------\n\n";
    }
}


bool Day17::IsValid(const int16_t z, const int16_t y, const int16_t x, const int16_t w) {
    return (x >= 0 && x < xSize && y >= 0 && y < ySize && z >= 0 && z < zSize && w >= 0 && w < wSize);
}


int8_t Day17::GetActiveNeighbours3D(const int16_t m, const int16_t l, const int16_t k) {
    int8_t sum = 0;
    for (int z = -1; z < 2; z++) {
        for (int y = -1; y < 2; y++) {
            for (int x = -1; x < 2; x++) {
                if (z == 0 && y == 0 && x == 0) continue;
                if (IsValid(m + z, l + y, k + x) && m_cubeMap3D[m + z][l + y][k + x] == '#') {
                    sum++;
                }
            }
        }
    }

    return sum;
}


int8_t Day17::GetActiveNeighbours4D(const int16_t n, const int16_t m, const int16_t l, const int16_t k) {
    int8_t sum = 0;
    for (int w = -1; w < 2; w++) {
        for (int z = -1; z < 2; z++) {
            for (int y = -1; y < 2; y++) {
                for (int x = -1; x < 2; x++) {
                    if (z == 0 && y == 0 && x == 0 && w == 0) continue;
                    if (IsValid(m + z, l + y, k + x, n + w) && m_cubeMap4D[n + w][m + z][l + y][k + x] == '#') {
                        sum++;
                    }
                }
            }
        }
    }

    return sum;
}


void Day17::ExecuteCycle3D() {
    CubeMap3D temp_cubeMap(m_cubeMap3D);

    for (int16_t z = 0; z < zSize; z++) {
        for (int16_t y = 0; y < ySize; y++) {
            for (int16_t x = 0; x < xSize; x++) {
                auto activeNeighbours = GetActiveNeighbours3D(z, y, x);

                if (m_cubeMap3D[z][y][x] == '#' && (!(activeNeighbours == 2 || activeNeighbours == 3))) {
                    temp_cubeMap[z][y][x] = '.';
                }

                if (m_cubeMap3D[z][y][x] == '.' && activeNeighbours == 3) {
                    temp_cubeMap[z][y][x] = '#';
                }
            }
        }
    }
    m_cubeMap3D = temp_cubeMap;
}


void Day17::ExecuteCycle4D() {
    CubeMap4D temp_cubeMap(m_cubeMap4D);

    for (int16_t w = 0; w < wSize; w++) {
        for (int16_t z = 0; z < zSize; z++) {
            for (int16_t y = 0; y < ySize; y++) {
                for (int16_t x = 0; x < xSize; x++) {
                    auto activeNeighbours = GetActiveNeighbours4D(w, z, y, x);

                    if (m_cubeMap4D[w][z][y][x] == '#' && (!(activeNeighbours == 2 || activeNeighbours == 3))) {
                        temp_cubeMap[w][z][y][x] = '.';
                    }

                    if (m_cubeMap4D[w][z][y][x] == '.' && activeNeighbours == 3) {
                        temp_cubeMap[w][z][y][x] = '#';
                    }
                }
            }
        }
    }
    m_cubeMap4D = temp_cubeMap;
}


int main() {
    Day17 d;

    int8_t sixCycleBootProcess = 6;
    {
        Timer t;
        for (int8_t i = 0; i < sixCycleBootProcess; i++) {
            d.ExecuteCycle3D();
        }

        std::cout << "There are " << d.GetActiveCubes3D(d.Get3DMap()) << " cubes left in active state!\n";
        // d.PrintCubeMap3D();
        
    }

    {
        Timer t;
        for (int8_t i = 0; i < sixCycleBootProcess; i++) {
            d.ExecuteCycle4D();
        }

        std::cout << "There are " << d.GetActiveCubes4D(d.Get4DMap()) << " cubes left in active state!\n";
    }
    
    return 0;
}