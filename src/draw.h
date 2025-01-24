#ifndef DRAW_H
#define DRAW_H

#include "puzzles.h"

#include <raylib.h>
#include <vector>

RenderTexture2D create_game_texture(int screenWidth, int screenHeight);
void draw_puzzle_to_texture(RenderTexture2D& texture, std::vector<Texture2D>& sprites, int tileSize, int screenWidth, int screenHeight, int spriteScale);

//void adjust_puzzle_dimensions(int puzzleHeight, int& spriteScale, int& tileSize, int spriteSize);
int get_puzzle_draw_offset(int tileSize, int axisWidth, int axisScreenWidth);
void clear_background(RenderTexture2D& texture);

#endif