#include "input.h"
#include "puzzles.h"
#include "draw.h"

#include "editor/editor_input.h"
#include "editor/editor_draw.h"

#include <vector>
#include <iostream>

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

void switch_to_play_mode() {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Play;
	}
}

void switch_to_edit_mode(std::vector<u16>& current_edit_puzzle, int edit_puzzle_width, int edit_puzzle_height) {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Edit;
		
		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}
		editor_history.clear();

		load_puzzle_into_canvas(canvas, current_edit_puzzle, edit_puzzle_width, edit_puzzle_height);
	}

}