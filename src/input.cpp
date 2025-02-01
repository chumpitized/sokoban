#include "input.h"
#include "puzzles.h"
#include "draw.h"

#include "editor/editor_input.h"
#include "editor/editor_draw.h"

#include <vector>
#include <iostream>

void create_new_puzzle() {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_N)) {
		std::cout << "creating new puzzle" << std::endl;
		create_new_puzzle_and_update_vals();
	}
}



void try_save(std::vector<u16>& puzzle, int index, bool valid_save) {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S) && valid_save) {
		std::cout << "trying to save!" << std::endl;
		overwrite_puzzle_in_puzzles(puzzle, index);
		save_puzzles_to_file();
	}
}

void move(PuzzleInfo& puzzleInfo, std::vector<u16>& puzzle) {
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
		//this will double count a position when you push into a wall
		//and no elements move

		//pushing to history should be api call...
		if (history.empty() || history.back() != puzzle) history.push_back(puzzle);		
		int input 					= GetKeyPressed();
		int newPos 					= try_move(input, puzzleInfo.playerIndex);
		puzzleInfo.playerIndex 		= newPos;
	}
}

void go_next_puzzle(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_EQUAL)) {
		if (try_increment_puzzle()) {
			history.clear();
			clear_background(game_texture);
		}
	}
}

void go_prev_puzzle(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_MINUS)) {
		if (try_decrement_puzzle()) {
			history.clear();
			clear_background(game_texture);
		}
	}
}

void undo() {
	if (IsKeyPressed(KEY_Z)) {
		//can undo on hold...
		undo_last_move();
	}	
}

void restart() {
	if (IsKeyPressed(KEY_R)) {
		restart_level();
		history.clear();
	}
}

void switch_to_play_mode(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Play;
		clear_background(game_texture);
		restart_level();
		history.clear();
	}
}

void switch_to_edit_mode(std::vector<u16>& current_edit_puzzle, int edit_puzzle_width, int edit_puzzle_height) {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Edit;
		
		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}

		//this can actually be done once when we select a puzzle,
		// then we can just display the canvas on mode switch...
		load_puzzle_into_canvas(canvas, current_edit_puzzle, edit_puzzle_width, edit_puzzle_height);
	}

}

void switch_to_level_menu() {
	if (IsKeyPressed(KEY_L)) {
		mode = Mode::Level_Menu;
		
		//std::vector<Texture2D> puzzle_previews;
		//std::vector<u16> first_puzzle = get_puzzles()[0];

		//int xOffset = screenWidth / 10;
		//int yOffset = screenHeight / 10;

		//DrawRectangle(xOffset, yOffset, 100, 100, RED);
	}
}