//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Day20_Part2.h"
#include "Timer.h"

#include <bits/stdc++.h>


void Day20_Part2::ReadFile() {
    std::cout << "ReadFile starts\n";

    std::ifstream inputFile(FILENAME);
    std::string s_input;
    
    if (inputFile.is_open()) {
        std::regex regex_tileId("([0-9]+)");
        while (std::getline(inputFile, s_input)) {
            Tile t;
            std::smatch match_tileId;
            if (std::regex_search(s_input, match_tileId, regex_tileId)) {
                t.id = stol(match_tileId.str(1));
            }
            
            while(std::getline(inputFile, s_input)) {
                if (s_input.empty()) break;
                
                t.cells.emplace_back(s_input);
            }

            // add all possible tiles, in terms of flipping and orientation
            for(int16_t f = 0; f < 2; ++f) {
                for(int16_t r = 0; r < 4; ++r) {
                    m_tiles.emplace_back(t);
                    Rotate(t.cells);
                }
                Flip(t.cells);
		    }
        }
        GRID_SIZE = llround(sqrt(m_tiles.size() / 8));

        inputFile.close();
    }
    else {
        const char* exception_string =  "Could not open input file";
        throw std::runtime_error(exception_string);
    }

    std::cout << "ReadFile finished\n";
}


void Day20_Part2::Rotate(std::vector<std::string>& a) {
	int16_t n = a.size();
	std::vector<std::string> b(n, std::string(n, '?'));
	for(int16_t row = 0; row < n; ++row) {
		for(int16_t col = 0; col < n; ++col) {
			b[row][col] = a[col][n-1-row];
		}
	}
	a = b;
}


void Day20_Part2::Flip(std::vector<std::string>& a) {
	int16_t n = a.size();
	for(int16_t row = 0; row < n; ++row) {
		for(int16_t col = 0; col < n / 2; ++col) {
			std::swap(a[row][col], a[row][n-1-col]);
		}
	}
}


void Day20_Part2::PrintTiles() {
    for (const auto& tiles : m_tiles) {
        std::cout << "\nTile " << tiles.id << ":\n";
        for (const auto t : tiles.cells) {
            std::cout << t << "\n";
        }
    }
}


void Day20_Part2::RemoveFrames() {
	std::vector<std::string> sea;
	for(int16_t row = 0; row < GRID_SIZE * S; ++row) {
		if(row % S == 0 || row % S == S - 1) {
			continue;
		}
		std::string new_row;
		for(int16_t col = 0; col < GRID_SIZE * S; ++col) {
			if(col % S == 0 || col % S == S - 1) {
				continue;
			}
			char cell = m_grid[row/S][col/S].cells[row%S][col%S];
			new_row += cell;
		}
		sea.push_back(new_row);
	}
	FindMonsters(sea);
}


void Day20_Part2::FindMonsters(std::vector<std::string> sea) {
	const int16_t h = 3;
	const int16_t w = monster[0].length();
	const int16_t n = sea.size();
	for(int16_t ro = 0; ro < 4; ++ro) {
		Rotate(sea);
		for(int16_t f = 0; f < 2; ++f) {
			Flip(sea);
			for(int16_t row = 0; row + h - 1 < n; ++row) {
				for(int16_t col = 0; col + w - 1 < n; ++col) {
					// consider a monster with top-left corner at (row, col)
					bool can_be = true;
					for(int16_t r = 0; r < h; ++r) {
						for(int16_t c = 0; c < w; ++c) {
							if(monster[r][c] == '#' && sea[row+r][col+c] == '.') {
								can_be = false;
							}
						}
					}
					if(!can_be) {
						continue;
					}
					for(int16_t r = 0; r < h; ++r) {
						for(int16_t c = 0; c < w; ++c) {
							if(monster[r][c] == '#') {
								sea[row+r][col+c] = 'O';
							}
						}
					}
				}
			}
		}
	}
	int16_t roughness = 0;
	for(std::string s : sea) {
		for(const char c : s) {
			if(c == '#') {
				roughness++;
			}
			std::cout << (c == 'O' ? 'O' : '.');
		}
		std::cout << "\n";
	}
	std::cout << "\nThe habitat's water roughness is " << roughness << "!\n";
}


void Day20_Part2::Search(int16_t row, int16_t col, std::set<int16_t>& visited) {
	if(row == GRID_SIZE) {
        RemoveFrames();
		exit(0);
		return;
	}
	for(const Tile& tile : m_tiles) {
		if(!visited.count(tile.id)) {
			// check if this new tile matches adjacent tiles above and on the left
			if(row > 0 && !m_grid[row - 1][col].can_below(tile)) {
				continue;
			}
			if(col > 0 && !m_grid[row][col - 1].can_right(tile)) {
				continue;
			}
			m_grid[row][col] = tile;
			visited.insert(tile.id);
			if(col == GRID_SIZE - 1) {
				Search(row + 1, 0, visited);
			}
			else {
				Search(row, col + 1, visited);
			}
			visited.erase(tile.id);
		}
	}
}



int main() {
    Day20_Part2 d;
    // d.PrintTiles();
    {
        Timer t;

	    std::set<int16_t> visited;
	    d.Search(0, 0, visited);
    }
    
    return 0;
}