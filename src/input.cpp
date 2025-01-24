#include "input.h"
#include "puzzles.h"
#include "draw.h"
#include "undo.h"

//if (IsKeyPressed(KEY_EQUAL)) {
//	increment_puzzle_index();
//	//adjust_puzzle_dimensions(currPuzzleInfo.height, spriteScale(), tileSize(), spriteSize);
//	clear_background(gameRenderTexture2D);
//	history.clear();
//}

//if (IsKeyPressed(KEY_MINUS)) {
//	decrement_puzzle_index();
//	//adjust_puzzle_dimensions(currPuzzleInfo.height, spriteScale(), tileSize(), spriteSize);
//	clear_background(gameRenderTexture2D);
//	history.clear();
//}

//if (IsKeyPressed(KEY_Z)) {
//	//can use currTime and deltaTime to rewind on press-and-hold
//	undo();
//}
		
//if (IsKeyPressed(KEY_R)) {
//	restart();
//	history.clear();
//}








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
		//can use currTime and deltaTime to rewind on press-and-hold
		undo_last_move();
	}	
}

void restart() {
	if (IsKeyPressed(KEY_R)) {
		restart_level();
		history.clear();
	}
}