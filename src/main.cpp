#include "puzzles.h"
#include "data.h"
#include "draw.h"
#include "input.h"

#include "editor/editor_draw.h"
#include "editor/editor_input.h"
#include "editor/editor_data.h"
#include "editor/editor_save.h"

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
	load_editor_sprites(editor_entities, editor_tiles);
	RenderTexture2D game_texture = create_texture(screenWidth, screenHeight);
	RenderTexture2D edit_texture = draw_editor_setup(screenWidth, screenHeight);
	load_puzzles_from_file();

	while(!WindowShouldClose()) {
		std::vector<u16> currPuzzle = get_current_puzzle();
		PuzzleInfo currPuzzleInfo 	= get_current_puzzle_info();

		if (gameMode == GameMode::Play) {
			switchMode();

			go_next_puzzle(game_texture);
			go_prev_puzzle(game_texture);
			undo();
			restart();
			move(currPuzzleInfo, currPuzzle);
			
			draw_puzzle_to_texture(game_texture, screenWidth, screenHeight);

			//Draw game_texture to window
			BeginDrawing();
				DrawTextureRec(game_texture.texture, (Rectangle){0, 0, (float)game_texture.texture.width, -(float)game_texture.texture.height}, (Vector2){0, 0}, RAYWHITE);
				DrawFPS(0, 0);
			EndDrawing();

		}

		if (gameMode == GameMode::Edit) {
			switchMode();

			//Input
			handle_left_mouse_click();
			handle_left_mouse_held();
			handle_left_mouse_release();
			handle_right_mouse_click();
			handle_right_mouse_held();
			reset_canvas();
			editor_undo();
			
			//Draw
			if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
				save();
			}

			//if we want, we can call this only when update...
			draw_canvas(edit_texture, canvas, entities, tiles, canvasTileWidth, xOffset, yOffset, tileSize);

			BeginDrawing();
				DrawTextureRec(edit_texture.texture, (Rectangle){0, 0, (float)edit_texture.texture.width, -(float)edit_texture.texture.height}, (Vector2){0, 0}, RAYWHITE);
				DrawFPS(0, 0);
				//handle_mouse_hover();
				draw_selected_palette_tile();
			EndDrawing();

		}

	}

	CloseWindow();	

	return 1;
}