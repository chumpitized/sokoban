#ifndef LOGIC_H
#define LOGIC_H

#include "puzzles.h"

#include <vector>

bool is_possible_move(int move, std::vector<int>& puzzle);
int try_move(int input, int tile, PuzzleInfo& puzzleInfo);

#endif