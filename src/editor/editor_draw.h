#ifndef EDITOR_DRAW_H
#define EDITOR_DRAW_H

#include "editor_data.h"
#include <raylib.h>
#include <vector>

extern std::vector<Texture2D> editor_entities;
extern std::vector<Texture2D> editor_tiles;

RenderTexture2D draw_editor_setup(int screenWidth, int screenHeight);

void draw_selected_palette_square();
Texture2D load_editor_sprite(const char* path);
void load_editor_sprites();
void draw_canvas_border();
void load_puzzle_into_canvas(std::vector<u16>& canvas, std::vector<u16>& puzzle, int puzzleWidth, int puzzleHeight);
void draw_canvas(RenderTexture2D& texture, std::vector<u16>& canvas, int width, int x, int y, int tileSize);
void draw_palette(std::vector<Texture2D>& palette, int width, int x, int y, int tileSize);

#endif