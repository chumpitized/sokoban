#include "sprites.h"
#include "puzzles.h"
#include "logic.h"
#include "undo.h"


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

	//need to be able to change the puzzle
	PuzzleInfo currPuzzleInfo 	= puzzleInfos[puzzleIndex];
	std::vector<int> currPuzzle = puzzles[currPuzzleInfo.index];
	//history.push_back(currPuzzle);

	while(!WindowShouldClose()) {		

		if (IsKeyPressed(KEY_Z)) {
			//can use currTime and deltaTime to rewind on press-and-hold
			undo(currPuzzle, currPuzzleInfo);
		}
		
		if (IsKeyPressed(KEY_R)) {
			restart(currPuzzleInfo, currPuzzle);
			history.clear();
		}

		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
			history.push_back(currPuzzle);
			int input 					= GetKeyPressed();
			int newPos 					= try_move(currPuzzle, input, currPuzzleInfo.playerIndex, currPuzzleInfo);
			currPuzzleInfo.playerIndex 	= newPos;
		}
		//Only redraw the full puzzle when a state change occurs.
		//Otherwise just draw the texture.
		draw_puzzle_to_texture(currPuzzle, currPuzzleInfo, gameRenderTexture2D, sprites, tileSize, screenWidth, screenHeight);

		//Draw gameRenderTexture2D to window
		BeginDrawing();
			DrawTextureRec(gameRenderTexture2D.texture, (Rectangle){0, 0, (float)gameRenderTexture2D.texture.width, -(float)gameRenderTexture2D.texture.height}, (Vector2){0, 0}, RAYWHITE);
		EndDrawing();
	}

	CloseWindow();	

	return 1;
}