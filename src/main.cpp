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
	RenderTexture2D game_texture = create_game_texture(screenWidth, screenHeight);

	while(!WindowShouldClose()) {
		std::vector<u16> currPuzzle = get_current_puzzle();
		PuzzleInfo currPuzzleInfo 	= get_current_puzzle_info();

		if (gameMode == GameMode::Play) {
			go_next_puzzle(game_texture);
			go_prev_puzzle(game_texture);
			undo();
			restart();
			move(currPuzzleInfo, currPuzzle);
		}

		//Only redraw the full puzzle when a state change occurs.
		//Otherwise just draw the texture.
		draw_puzzle_to_texture(game_texture, sprites, tileSize(), screenWidth, screenHeight, spriteScale());

		//Draw game_texture to window
		BeginDrawing();
			DrawTextureRec(game_texture.texture, (Rectangle){0, 0, (float)game_texture.texture.width, -(float)game_texture.texture.height}, (Vector2){0, 0}, RAYWHITE);
			DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();	

	return 1;
}