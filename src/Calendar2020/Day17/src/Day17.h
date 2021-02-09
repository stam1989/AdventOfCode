//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY17_H
#define DAY17_H


#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>

using CubeMap3D = std::vector<std::vector<std::vector<char>>>;
using CubeMap4D = std::vector<std::vector<std::vector<std::vector<char>>>>;

class Day17
{
public:
    Day17() { ReadFile(); }

    void PrintCubeMap3D();
    void PrintCubeMap4D();
    void ExecuteCycle3D();
    void ExecuteCycle4D();
    int32_t GetActiveCubes3D(const CubeMap3D& cubeMap);
    int32_t GetActiveCubes4D(const CubeMap4D& cubeMap);

    inline const CubeMap3D Get3DMap() { return m_cubeMap3D; }
    inline const CubeMap4D Get4DMap() { return m_cubeMap4D; }
    
    template <typename T>
    int32_t GetActiveCubes3D(T&& cubeMap3D) {
        int32_t countActiveCubes = 0;
        for (const auto& cm : cubeMap3D) {
            for (const auto el : cm) {
                countActiveCubes += std::count(el.begin(), el.end(), '#');
            }
        }

        return countActiveCubes;
    }

    template <typename T>
    int32_t GetActiveCubes4D(T&& cubeMap4D) {
        int32_t countActiveCubes = 0;
        for (const auto& cubeMaps : cubeMap4D) {
            for (const auto& cm : cubeMaps) {
                for (const auto el : cm) {
                    countActiveCubes += std::count(el.begin(), el.end(), '#');
                }
            }
        }

        return countActiveCubes;
    }

private:
    CubeMap3D m_cubeMap3D;
    CubeMap4D m_cubeMap4D;

    static constexpr int32_t wSize = 13;
    static constexpr int32_t zSize = 13;
    static constexpr int32_t ySize = 23;
    static constexpr int32_t xSize = 23;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day17/resources/Day17.txt";

    void ReadFile();
    void InitCubeMap();
    bool IsValid(const int16_t z, const int16_t y, const int16_t x, const int16_t w = 0);
    int8_t GetActiveNeighbours3D(const int16_t m, const int16_t l, const int16_t k);
    int8_t GetActiveNeighbours4D(const int16_t n, const int16_t m, const int16_t l, const int16_t k);
};


#endif