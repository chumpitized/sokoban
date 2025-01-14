#include "sprites.h"
#include "puzzles.h"
#include "logic.h"

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

	RenderTexture2D gameRenderTexture2D = create_game_texture(screenWidth, screenHeight);

	int puzzleIndex = 0;

	PuzzleInfo currPuzzle = puzzleInfos[puzzleIndex];

	while(!WindowShouldClose()) {		

		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
			int input 			= GetKeyPressed();
			int newPos 				= try_move(input, currPuzzle.playerIndex, currPuzzle);
			currPuzzle.playerIndex 	= newPos;
		}
		//Only redraw when a state change occurs
		draw_puzzle_to_texture(currPuzzle, gameRenderTexture2D, sprites, tileSize, screenWidth, screenHeight); 

		//Draw gameRenderTexture2D to window
		BeginDrawing();
			DrawTextureRec(gameRenderTexture2D.texture, (Rectangle){0, 0, (float)gameRenderTexture2D.texture.width, -(float)gameRenderTexture2D.texture.height}, (Vector2){0, 0}, RAYWHITE);
		EndDrawing();
	}

	CloseWindow();	

	return 1;
}