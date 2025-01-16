#include "sprites.h"
#include "puzzles.h"
#include "logic.h"
#include "undo.h"

#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

int main() {
	//we need to make sure we offset the art by the right amount
	//in order to make things pixel-perfect
	int spriteSize 		= 16;
	int screenWidth		= 1920;
	int screenHeight 	= 1088;
	int yPadding 		= (screenHeight % spriteSize) / 2;
	int xPadding		= (screenWidth % spriteSize) / 2;

	SetTargetFPS(60);

	//We can make the window resizable with this flag, but it's
	//probably only useful for testing...
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(screenWidth, screenHeight, "Sokoban!");
	load_sprites();
	RenderTexture2D gameRenderTexture2D = create_game_texture(screenWidth, screenHeight);

	int puzzleIndex = 0;

	//need to be able to change the puzzle
	PuzzleInfo currPuzzleInfo 	= puzzleInfos[puzzleIndex];
	std::vector<int> currPuzzle = puzzles[puzzleIndex];
	//we can divide screenHeight by puzzle height + 2 to add 1-tile padding
	//on the top and bottom... then black bars above and below for
	//pixel-perfect padding
	int spriteScale		= (screenHeight / currPuzzleInfo.height) / spriteSize;
	int tileSize 		= spriteScale * spriteSize;

	while(!WindowShouldClose()) {		

		if (IsKeyPressed(KEY_EQUAL)) {
			go_next_puzzle(puzzleIndex, currPuzzleInfo, currPuzzle);
		}

		if (IsKeyPressed(KEY_MINUS)) {
			go_prev_puzzle(puzzleIndex, currPuzzleInfo, currPuzzle);
		}

		if (IsKeyPressed(KEY_Z)) {
			//can use currTime and deltaTime to rewind on press-and-hold
			undo(currPuzzle, currPuzzleInfo);
		}
		
		if (IsKeyPressed(KEY_R)) {
			restart(currPuzzleInfo, currPuzzle);
			history.clear();
		}

		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
			//this will double count a position when you push into a wall
			//and no elements move
			if (history.empty() || history.back() != currPuzzle) history.push_back(currPuzzle);
			std::cout << history.size() << std::endl;
			int input 					= GetKeyPressed();
			int newPos 					= try_move(currPuzzle, input, currPuzzleInfo.playerIndex, currPuzzleInfo);
			currPuzzleInfo.playerIndex 	= newPos;
		}
		//Only redraw the full puzzle when a state change occurs.
		//Otherwise just draw the texture.
		draw_puzzle_to_texture(currPuzzle, currPuzzleInfo, gameRenderTexture2D, sprites, tileSize, screenWidth, screenHeight, spriteScale);

		//Draw gameRenderTexture2D to window
		BeginDrawing();
			DrawTextureRec(gameRenderTexture2D.texture, (Rectangle){0, 0, (float)gameRenderTexture2D.texture.width, -(float)gameRenderTexture2D.texture.height}, (Vector2){0, 0}, RAYWHITE);
		EndDrawing();
	}

	CloseWindow();	

	return 1;
}