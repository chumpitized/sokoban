#ifndef INPUT_H
#define INPUT_H

#include "puzzles.h"
#include <raylib.h>

void move(PuzzleInfo& puzzleInfo, std::vector<u16>& puzzle);
void go_next_puzzle(RenderTexture2D& game_texture);
void go_prev_puzzle(RenderTexture2D& game_texture);
void undo();
void restart();



void switchMode();

#endif