#ifndef LOGIC_H
#define LOGIC_H

#include "puzzles.h"

#include <vector>

bool is_valid_move(int move, std::vector<int>& puzzle);
void move(int input, PuzzleInfo& puzzleInfo);

#endif