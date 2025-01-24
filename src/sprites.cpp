#include "sprites.h"
#include "puzzles.h"

#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

std::vector<Texture2D> sprites;

int spriteScale() {
	return (screenHeight / get_puzzle_height()) / spriteSize;
}
int tileSize() {
	return spriteScale() * spriteSize;
}


Texture2D load_sprite(const char* path) {
	Image image = LoadImage(path);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
};

//we use this function to load sprites AFTER calling init_window
void load_sprites() {
	sprites = {
		load_sprite("data/sprites/character_transparent.png"),
		load_sprite("data/sprites/black_tile.png"),
		load_sprite("data/sprites/gray_tile.png"),
		load_sprite("data/sprites/horizontal_wall.png"),
		load_sprite("data/sprites/vertical_wall.png"),
		load_sprite("data/sprites/locked_door.png"),
		load_sprite("data/sprites/key_transparent.png")
	}; 
};