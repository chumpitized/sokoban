#ifndef UNDO_H
#define UNDO_H

#include <vector>

extern std::vector<std::vector<int>> history;

void undo_last_move();
void restart();

#endif