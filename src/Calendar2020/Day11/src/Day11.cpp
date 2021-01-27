//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day11.h"

#include <fstream>
#include <Color.h>
#include <iostream>


void Day11::ReadFile()
{
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
	
    if (inputFile.is_open())
    {
        m_row = 0;
        while (std::getline(inputFile, s_input))
        {
            m_col = 0;
            std::vector<char> seats;
            for(const auto s : s_input)
            {
                seats.emplace_back(s);
                m_col++;
            }
            m_row++;
            m_seats.emplace_back(seats);
            seats.clear();
        }
        inputFile.close();
    }
    else
    {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day11::PrintSeatLayout()
{
    for(const auto seats : m_seats) {
        for(const auto s : seats) {
            if(s == '#') std::cout << BOLDMAGENTA << s << RESET;
            if(s == '.') std::cout << BOLDGREEN << s << RESET;
            if(s == 'L') std::cout << BOLDYELLOW << s << RESET; }
        std::cout << "\n"; }
}

int8_t Day11::GetNumOfOccupiedAdjacent(const SeatLayout& seats, const int32_t col, const int32_t row)
{
    int8_t occupied = 0;

    if(col + 1 < m_col && seats[row][col + 1] == '#') occupied++;
    if(col - 1 >= 0 && seats[row][col - 1] == '#') occupied++;
    if(row + 1 < m_row && seats[row + 1][col] == '#') occupied++;
    if(row - 1 >= 0 && seats[row - 1][col] == '#') occupied++;
    if(col + 1 < m_col && row + 1 < m_row && seats[row + 1][col + 1] == '#') occupied++;
    if(col + 1 < m_col && row - 1 >= 0 && seats[row - 1][col + 1] == '#') occupied++;
    if(col - 1 >= 0 && row + 1 < m_row && seats[row + 1][col - 1] == '#') occupied++;
    if(col - 1 >= 0 && row - 1 >= 0 && seats[row - 1][col - 1] == '#') occupied++;

    return occupied;
}


int8_t Day11::GetNumOfOccupiedAll(const SeatLayout& seats, const int32_t col, const int32_t row)
{
    int8_t occupied = 0;

    for(int32_t c = col + 1; c < m_col; c++) {
        if(seats[row][c] == '.') continue;
        if(seats[row][c] == 'L') break;
        if(seats[row][c] == '#') { occupied++; break; } }

    for(int32_t c = col - 1; c >= 0; c--) {
        if(seats[row][c] == '.') continue;
        if(seats[row][c] == 'L') break;
        if(seats[row][c] == '#') { occupied++; break; } }

    for(int32_t r = row + 1; r < m_row; r++) {
        if(seats[r][col] == '.') continue;
        if(seats[r][col] == 'L') break;
        if(seats[r][col] == '#') { occupied++; break; } }

    for(int32_t r = row - 1; r >= 0; r--) {
        if(seats[r][col] == '.') continue;
        if(seats[r][col] == 'L') break;
        if(seats[r][col] == '#') { occupied++; break; } }

    for(int32_t r = row + 1; r < m_row; r++) {
        int32_t c = col + (r - row);
        if(c >= m_col) break;
        if(seats[r][c] == '.') continue;
        if(seats[r][c] == 'L') break;
        if(seats[r][c] == '#') { occupied++; break; } }

    for(int32_t r = row - 1; r >= 0; r--) {
        int32_t c = col + (row - r);    
        if(c >= m_col) break;
        if(seats[r][c] == 'L') break;
        if(seats[r][c] == '.') continue;
        if(seats[r][c] == '#') { occupied++; break; } }

    for(int32_t r = row + 1; r < m_row; r++) {
        int32_t c = col - (r - row);
        if(c < 0) break;
        if(seats[r][c] == 'L') break;
        if(seats[r][c] == '.') continue;
        if(seats[r][c] == '#') { occupied++; break; } }

    for(int32_t r = row - 1; r >= 0; r--) {
        int32_t c = col - (row - r);    
        if(c < 0) break;
        if(seats[r][c] == 'L') break;
        if(seats[r][c] == '.') continue;
        if(seats[r][c] == '#') { occupied++; break; } }

    return occupied;
}


bool Day11::ApplyRules()
{
    SeatLayout temp_seats(m_seats);
    bool seatsChanged = false;

    for(auto row = 0; row < m_row; row++) {
        for(auto col = 0; col < m_col; col++) {
            if(temp_seats[row][col] == 'L' && GetNumOfOccupiedAdjacent(temp_seats, col, row) == 0) {
                m_seats[row][col] = '#';
                seatsChanged = true; }

            if(temp_seats[row][col] == '#' && GetNumOfOccupiedAdjacent(temp_seats, col, row) >= 4) {
                m_seats[row][col] = 'L';
                seatsChanged = true; } } }

    return seatsChanged;
}


bool Day11::ApplyRulesSecond()
{
    SeatLayout temp_seats(m_seats);
    bool seatsChanged = false;
    for(auto row = 0; row < m_row; row++)
    {
        for(auto col = 0; col < m_col; col++)
        {
            if(temp_seats[row][col] == 'L' && GetNumOfOccupiedAll(temp_seats, col, row) == 0)
            {
                m_seats[row][col] = '#';
                seatsChanged = true;
            }

            if(temp_seats[row][col] == '#' && GetNumOfOccupiedAll(temp_seats, col, row) >= 5)
            {
                m_seats[row][col] = 'L';
                seatsChanged = true;
            }
        }
    }

    return seatsChanged;
}


int32_t Day11::CountOccupied()
{
    int32_t countOccupied = 0;
    
    for(const auto& s : m_seats)
    {
        countOccupied += std::count_if(s.begin(), s.end(), [](const char c) { return c == '#'; });
    }

    return countOccupied;
}


int main()
{
    Day11 d;
    // d.PrintSeatLayout();

    // Day 1
    // while(d.ApplyRules());
    // std::cout << "Occupied seats are: " << d.CountOccupied() << "!\n";

    // Day 2
    while(d.ApplyRulesSecond());
    std::cout << "Occupied seats with second criteria applied are: " << d.CountOccupied() << "!\n";

    return 0;
}