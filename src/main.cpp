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
	SetExitKey(KEY_NULL);

	load_sprites();
	load_editor_sprites();
	load_puzzles_from_file();
	RenderTexture2D game_texture = create_texture(screenWidth, screenHeight);
	RenderTexture2D edit_texture = draw_editor_setup(screenWidth, screenHeight);
	RenderTexture2D menu_texture = draw_menu_setup(screenWidth, screenHeight);	

	while(!WindowShouldClose()) {
		int current_puzzle_index 		= get_puzzle_index();

		std::vector<u16> current_puzzle = get_current_puzzle();
		u8 current_puzzle_width 		= get_current_puzzle_width();
		u8 current_puzzle_height 		= get_current_puzzle_height();

		////////////
		//  Play  //
		////////////

		switch_to_edit_mode(current_puzzle_width, current_puzzle_height);
		switch_to_play_mode(game_texture);
		switch_to_level_menu();
		
		if (mode == Mode::Play) {
			go_next_puzzle(game_texture);
			go_prev_puzzle(game_texture);
			undo();
			restart();
			move(current_puzzle);
			
			draw_puzzle_to_texture(game_texture, screenWidth, screenHeight);

			BeginDrawing();
				DrawTextureRec(game_texture.texture, (Rectangle){0, 0, (float)game_texture.texture.width, -(float)game_texture.texture.height}, (Vector2){0, 0}, WHITE);
				DrawFPS(0, 0);

				int puzzleidx = get_puzzle_index();
				char numStr[10];
				sprintf(numStr, "%d", puzzleidx);

				DrawText(numStr, 100, 100, 60, RED);
			EndDrawing();
		}

		////////////
		// Editor //
		////////////

		if (mode == Mode::Edit) {
			//Input
			handle_left_mouse_click();
			handle_left_mouse_held();
			handle_left_mouse_release();
			handle_right_mouse_click();
			handle_right_mouse_held();
			reset_canvas();
			editor_undo();

			bool is_edit_valid = is_edit_puzzle_valid(canvas, canvasTileWidth);
			bool save_status = is_edit_valid && is_edit_puzzle_same_as_saved_puzzle();
			try_save(current_puzzle, current_puzzle_index, is_edit_valid);

			create_new_puzzle();

			set_current_puzzle_to_edit_puzzle(canvas, canvasTileWidth);

			//if we want, we can call this only when update...
			draw_canvas(edit_texture, canvas, canvasTileWidth, xOffset, yOffset, tileSize);

			BeginDrawing();
				DrawTextureRec(edit_texture.texture, (Rectangle){0, 0, (float)edit_texture.texture.width, -(float)edit_texture.texture.height}, (Vector2){0, 0}, WHITE);

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

		//////////////////
		//  Level Menu  //
		//////////////////

		if (mode == Mode::Level_Menu) {
			//int xOffset = screenWidth / 10;
			//int yOffset = screenHeight / 10;

			Vector2 mouse_position = GetMousePosition();

			int x_coord = mouse_position.x / 160;
			int y_coord = mouse_position.y / 160;
			int index 	= (y_coord * 12) + x_coord;

			int x_offset = 0;
			int y_offset = 0;
			int texture_size = 160;

			select_puzzle(index);
			//select_puzzle_and_move();

			std::vector<RenderTexture2D> puzzle_previews = get_puzzle_previews();

			BeginDrawing();
				ClearBackground(WHITE);
			
				for (int i = 0; i < puzzle_previews.size(); ++i) {
					int y_additional_offset = (y_offset + (texture_size * i) / screenWidth) * texture_size;
					int x_additional_offset = x_offset + (texture_size * i) % screenWidth;

					DrawTextureRec(puzzle_previews[i].texture, (Rectangle){0, 0, (float)puzzle_previews[i].texture.width, -(float)puzzle_previews[i].texture.height}, (Vector2){(float)x_additional_offset, (float)y_additional_offset}, WHITE);
				}

				draw_selected_puzzle_outline(get_puzzle_index());
				select_puzzle_and_move(index);
			EndDrawing();

			move_puzzle(index);
		}

	}

	CloseWindow();	

	return 1;
}