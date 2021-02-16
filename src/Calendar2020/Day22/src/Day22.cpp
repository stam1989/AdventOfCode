//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day22.h"
#include "Timer.h"

#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <set>


void Day22::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;

    if (inputFile.is_open()) {
        std::regex r("([a-z]+ [1-2]+[:])");
        while (std::getline(inputFile, s_input)) {
            std::smatch match;
            if (std::regex_search(s_input, match, r)) {
                std::deque<int32_t> temp_deck;
                while(std::getline(inputFile, s_input)) {
                    if (s_input.empty()) break;
                    temp_deck.emplace_back(stol(s_input));
                }
                if (m_deck1.empty()) m_deck1 = temp_deck;
                else m_deck2 = temp_deck;
            }
        }
        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day22::MoveElements(std::deque<int32_t>& d1, std::deque<int32_t>& d2) {
    std::rotate(d1.begin(), d1.begin() + 1, d1.end());
    d1.emplace_back(d2.front());
    d2.pop_front();
}


void Day22::PrintDecks() {
    std::cout << "Deck1: ";
    for (const auto d1 : m_deck1)
        std::cout << d1 << ", ";
    std::cout << "\nDeck2: ";
    for (const auto d2 : m_deck2)
        std::cout << d2 << ", ";
    std::cout << "\n";
}


bool Day22::PlayTheGame(std::deque<int32_t> deck1, std::deque<int32_t> deck2) {
    std::set<std::pair<std::deque<int32_t>, std::deque<int32_t>>> prevDecks;

    while(!(deck1.empty() || deck2.empty())) {
        std::pair<std::deque<int32_t>, std::deque<int32_t>> currentDeck(std::make_pair(deck1, deck2));
        auto it_deck = prevDecks.find(currentDeck);
        // if decks are exactly the same as in any previous round, the game instantly ends in a win for player 1
        if (it_deck != prevDecks.end()) return true;
        prevDecks.emplace(currentDeck);

        if(deck1.size() - 1 >= deck1.front() && deck2.size() - 1 >= deck2.front()) {
            std::deque<int32_t> temp_d1, temp_d2;
            temp_d1.assign(deck1.begin() + 1, deck1.begin() + 1 + deck1.front());
            temp_d2.assign(deck2.begin() + 1, deck2.begin() + 1 + deck2.front());
            if (PlayTheGame(temp_d1, temp_d2)) MoveElements(deck1, deck2);
            else MoveElements(deck2, deck1);
        }
        else if (deck1.front() > deck2.front()) {
            MoveElements(deck1, deck2);
        }
        else if (deck2.front() > deck1.front()) {
            MoveElements(deck2, deck1);
        }
    }

    m_deck1 = deck1;
    m_deck2 = deck2;
    bool winner = (deck1.empty()) ? false : true;
    return winner;
}


int64_t Day22::GetScore() {
    auto deck = (m_deck1.empty()) ? m_deck2 : m_deck1;
    int64_t score = 0;
    for (int16_t i = 0; i < deck.size(); i++) {
        score += (deck.size() - i) * deck[i];
    }

    return score;
}


int main() {
    Day22 d;

    {
        Timer t;
        auto d1 = d.GetDeck1();
        auto d2 = d.GetDeck2();
        d.PlayTheGame(d1, d2);
        d.PrintDecks();
        auto deck = (d1.empty()) ? d2 : d1;
        std::cout << "The score  is " << d.GetScore() << "!\n";
    }

    {
        Timer t;

    }
    
    return 0;
}