#ifndef INPUT_H
#define INPUT_H

#include <raylib.h>

void go_next_puzzle(RenderTexture2D& game_texture);
void go_prev_puzzle(RenderTexture2D& game_texture);
void undo();
void restart();



#endif