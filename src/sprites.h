#ifndef SPRITES_H
#define SPRITES_H

#include <raylib.h>
#include <vector>

Texture2D load_sprite(const char* path);
void load_sprites();

//Sprites
extern Texture2D player;
extern Texture2D black_tile;
extern Texture2D gray_tile;
extern Texture2D horizontal_wall;
extern Texture2D vertical_wall;
extern Texture2D locked_door;
extern Texture2D key;

//Sprite Array
extern std::vector<Texture2D> sprites;

#endif