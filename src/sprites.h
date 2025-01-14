#ifndef SPRITES_H
#define SPRITES_H

#include <raylib.h>
#include <vector>

Texture2D load_sprite(const char* path);
void load_sprites();

//Sprite Array
extern std::vector<Texture2D> sprites;

#endif