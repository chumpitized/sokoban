#ifndef UNDO_H
#define UNDO_H

#include <vector>

extern std::vector<std::vector<int>> history;

void undo(std::vector<int>& puzzle, PuzzleInfo& puzzleInfo);
void restart(PuzzleInfo& puzzleInfo, std::vector<int>& puzzle);

#endif