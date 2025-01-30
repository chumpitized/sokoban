#ifndef EDITOR_DRAW_H
#define EDITOR_DRAW_H

#include "editor_data.h"
#include <raylib.h>
#include <vector>

void draw_selected_palette_square();

RenderTexture2D draw_editor_setup(int screenWidth, int screenHeight);
Texture2D load_editor_sprite(const char* path);
void load_editor_sprites(std::vector<Texture2D>& entities, std::vector<Texture2D>& tiles);
void draw_canvas_border();
void draw_canvas(RenderTexture2D& texture, std::vector<u16>& canvas, std::vector<Texture2D>& entities, std::vector<Texture2D>& tiles, int width, int x, int y, int tileSize);
void draw_palette(std::vector<Texture2D>& palette, int width, int x, int y, int tileSize);

#endif