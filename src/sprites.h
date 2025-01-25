#ifndef SPRITES_H
#define SPRITES_H

#include <raylib.h>
#include <vector>

int spriteScale();
int tileSize();

Texture2D load_sprite(const char* path);
void load_sprites();

//Sprite Array
extern std::vector<Texture2D> entities;
extern std::vector<Texture2D> tiles;

extern std::vector<Texture2D> sprites;

#endif