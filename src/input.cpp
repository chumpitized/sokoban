#include "input.h"
#include "puzzles.h"
#include "draw.h"

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