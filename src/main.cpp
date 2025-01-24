#include "sprites.h"
#include "puzzles.h"
#include "logic.h"
#include "undo.h"
#include "data.h"
#include "draw.h"
#include "input.h"

#include <vector>
#include <iostream>
#include <raylib.h>

int main() {
	SetTargetFPS(60);

	//We can make the window resizable with this flag, but it's
	//probably only useful for testing...
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(screenWidth, screenHeight, "Sokoban!");
	load_sprites();
	RenderTexture2D gameRenderTexture2D = create_game_texture(screenWidth, screenHeight);

	while(!WindowShouldClose()) {
		PuzzleInfo& currPuzzleInfo = puzzleInfos[puzzleIndex];
		std::vector<int>& currPuzzle = puzzles[puzzleIndex];

		if (gameMode == GameMode::Play) {
			go_next_puzzle(gameRenderTexture2D);
			go_prev_puzzle(gameRenderTexture2D);
			undo();
		
			if (IsKeyPressed(KEY_R)) {
				restart();
				history.clear();
			}

			if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
				//this will double count a position when you push into a wall
				//and no elements move
				//PuzzleInfo& currPuzzleInfo = puzzleInfos[puzzleIndex];
				//std::vector<int>& currPuzzle = puzzles[puzzleIndex];

				if (history.empty() || history.back() != currPuzzle) history.push_back(currPuzzle);		
				int input 					= GetKeyPressed();
				int newPos 					= try_move(currPuzzle, input, currPuzzleInfo.playerIndex, currPuzzleInfo);
				currPuzzleInfo.playerIndex 	= newPos;
			}
		}

		//Only redraw the full puzzle when a state change occurs.
		//Otherwise just draw the texture.
		draw_puzzle_to_texture(gameRenderTexture2D, sprites, tileSize(), screenWidth, screenHeight, spriteScale());

		//Draw gameRenderTexture2D to window
		BeginDrawing();
			DrawTextureRec(gameRenderTexture2D.texture, (Rectangle){0, 0, (float)gameRenderTexture2D.texture.width, -(float)gameRenderTexture2D.texture.height}, (Vector2){0, 0}, RAYWHITE);
			DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();	

	return 1;
}