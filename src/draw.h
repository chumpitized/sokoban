#ifndef DRAW_H
#define DRAW_H

#include "puzzles.h"

#include <raylib.h>
#include <vector>

//Sprite Array
extern std::vector<Texture2D> entities;
extern std::vector<Texture2D> tiles;
extern std::vector<Texture2D> sprites;

int get_sprite_scale();
int get_tile_size();

RenderTexture2D create_game_texture(int screenWidth, int screenHeight);

Texture2D load_sprite(const char* path);
void load_sprites();

void draw_puzzle_to_texture(RenderTexture2D& texture, int screenWidth, int screenHeight);

int get_puzzle_draw_offset(int tileSize, int axisWidth, int axisScreenWidth);
void clear_background(RenderTexture2D& texture);

#endif