#include "sprites.h"
#include "puzzles.h"

#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

int main() {
	//must always respect sprite dimensions
	int screenWidth		= 1920;
	int screenHeight 	= 1088;

	//tileSize should scale with screenHeight
	int tileSize 		= 176;

	SetTargetFPS(60);

	InitWindow(screenWidth, screenHeight, "Sokoban!");
	load_sprites();

	RenderTexture2D gameTexture = create_game_texture(screenWidth, screenHeight);

	while(!WindowShouldClose()) {
		PuzzleInfo first = PuzzleInfo(5, 5, 0);

		draw_puzzle(first, gameTexture, sprites, tileSize, screenWidth, screenHeight); 

		//Draw gameTexture to window
		BeginDrawing();
			DrawTextureRec(gameTexture.texture, (Rectangle){0, 0, (float)gameTexture.texture.width, -(float)gameTexture.texture.height}, (Vector2){0, 0}, RAYWHITE);
		EndDrawing();

	}

	CloseWindow();	

	return 1;
}