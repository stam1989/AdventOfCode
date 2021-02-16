//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#ifndef DAY22_H
#define DAY22_H


#include <cstdlib>
#include <deque>


class Day22
{
public:
    Day22() { ReadFile(); }

    void PrintDecks();

    // returns true if player1 won, otherwise returns false
    bool PlayTheGame(std::deque<int32_t> deck1, std::deque<int32_t> deck2);
    int64_t GetScore();

    inline std::deque<int32_t> GetDeck1() { return m_deck1; }
    inline std::deque<int32_t> GetDeck2() { return m_deck2; }
private:
    std::deque<int32_t> m_deck1, m_deck2;
    static constexpr char const *FILENAME = "../src/Calendar2020/Day22/resources/Day22.txt";

    void ReadFile();
    void MoveElements(std::deque<int32_t>& d1, std::deque<int32_t>& d2);
};


#endif