#ifndef EDITOR_UNDO_H
#define EDITOR_UNDO_H

#include "editor_data.h"

#include <vector>

extern std::vector<std::vector<u16>> history;

void undo();

#endif