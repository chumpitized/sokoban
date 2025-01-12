#include "sprites.h"

#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

Texture2D horizontal_wall;
Texture2D vertical_wall;
Texture2D black_tile;
Texture2D gray_tile;
Texture2D player;
Texture2D key;
Texture2D locked_door;
std::vector<Texture2D> sprites;

Texture2D load_sprite(const char* path) {
	cout << path << endl;
	Image image = LoadImage(path);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
};

//we use this function to load sprites AFTER calling init_window
void load_sprites() {
	player 			= load_sprite("data/sprites/character.png");
	black_tile 		= load_sprite("data/sprites/black_tile.png");
	gray_tile 		= load_sprite("data/sprites/gray_tile.png");
	horizontal_wall = load_sprite("data/sprites/horizontal_wall.png");
	vertical_wall 	= load_sprite("data/sprites/vertical_wall.png");
	locked_door 	= load_sprite("data/sprites/locked_door.png");
	key 			= load_sprite("data/sprites/key.png");

	sprites = {
		player,
		black_tile,
		gray_tile,
		horizontal_wall,
		vertical_wall,
		locked_door,
		key
	}; 
};