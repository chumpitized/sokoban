#ifndef UNDO_H
#define UNDO_H

#include <vector>

extern std::vector<std::vector<u16>> history;

void undo_last_move();
void restart_level();

#endif