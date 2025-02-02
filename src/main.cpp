#include "puzzles.h"
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
	//SetExitKey(KEY_NULL);

	load_sprites();
	load_editor_sprites();
	load_puzzles_from_file();
	RenderTexture2D game_texture = create_texture(screenWidth, screenHeight);
	RenderTexture2D edit_texture = draw_editor_setup(screenWidth, screenHeight);
	RenderTexture2D menu_texture = draw_menu_setup(screenWidth, screenHeight);	

	while(!WindowShouldClose()) {
		std::vector<u16> currPuzzle 	= get_current_puzzle();
		std::vector<u16> currEditPuzzle	= get_current_edit_puzzle();

		u8 current_puzzle_width = get_current_puzzle_width();
		u8 current_puzzle_height = get_current_puzzle_height();

		std::vector<u16> constPuzzle 	= get_const_puzzle();
		PuzzleInfo currPuzzleInfo 		= get_current_puzzle_info();

		//Play
		if (mode == Mode::Play) {
			switch_to_edit_mode(currEditPuzzle, current_puzzle_width, current_puzzle_height);
			//switch_to_edit_mode(currEditPuzzle, currPuzzleInfo.width, currPuzzleInfo.height);


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

				int puzzleidx = get_puzzle_index(); // Example integer
				char numStr[10]; // Buffer to hold the converted number
				sprintf(numStr, "%d", puzzleidx);

				DrawText(numStr, 100, 100, 60, RED);
			EndDrawing();
		}

		//Puzzle Editor
		if (mode == Mode::Edit) {
			//Input
			switch_to_play_mode(game_texture);
			switch_to_level_menu();

			handle_left_mouse_click();
			handle_left_mouse_held();
			handle_left_mouse_release();
			handle_right_mouse_click();
			handle_right_mouse_held();
			reset_canvas();
			editor_undo();

			bool is_edit_valid = is_edit_puzzle_valid(canvas, canvasTileWidth);
			bool save_status = is_edit_valid && is_edit_puzzle_same_as_saved_puzzle();
			try_save(currEditPuzzle, currPuzzleInfo.index, is_edit_valid);

			create_new_puzzle();

			//update the edit puzzle
			set_current_puzzle_to_edit_puzzle(canvas, canvasTileWidth);

			//if we want, we can call this only when update...
			draw_canvas(edit_texture, canvas, canvasTileWidth, xOffset, yOffset, tileSize);

			BeginDrawing();
				DrawTextureRec(edit_texture.texture, (Rectangle){0, 0, (float)edit_texture.texture.width, -(float)edit_texture.texture.height}, (Vector2){0, 0}, RAYWHITE);

				draw_save_status(save_status);

				if (is_edit_valid) {
					DrawCircle(xOffset + (tileSize / 2), yOffset + (tileSize / 2), 15, GREEN);
				} else {
					DrawCircle(xOffset + (tileSize / 2), yOffset + (tileSize / 2), 15, RED);
				}

				DrawFPS(0, 0);
				
				handle_mouse_hover();
				draw_selected_palette_square();
			EndDrawing();
		}

		//Puzzle Selection Menu -- UNFINISHED
		if (mode == Mode::Level_Menu) {
			switch_to_edit_mode(currEditPuzzle, currPuzzleInfo.width, currPuzzleInfo.height);

			std::vector<std::vector<u16>> puzzles = get_puzzles();

			int xOffset = screenWidth / 10;
			int yOffset = screenHeight / 10;

			BeginDrawing();
				DrawTextureRec(menu_texture.texture, (Rectangle){0, 0, (float)menu_texture.texture.width, -(float)menu_texture.texture.height}, (Vector2){0, 0}, RAYWHITE);

				for (int i = 0; i < puzzles.size(); i++) {
					DrawRectangle(xOffset + (100 * i), yOffset, 100, 100, RED);
				}
			EndDrawing();
		}

	}

	CloseWindow();	

	return 1;
}