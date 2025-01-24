//#include "input.h"

//#include <vector>
//#include <iostream>
//#include <raylib.h>

//void handle_input(int input) {
//	if (IsKeyPressed(KEY_EQUAL)) {
//		go_next_puzzle(puzzleIndex, currPuzzleInfo, currPuzzle);
//		adjust_puzzle_dimensions(screenHeight, currPuzzleInfo.height, spriteScale, tileSize, spriteSize);
//		clear_background(gameRenderTexture2D);
//		history.clear();
//	}

//	if (IsKeyPressed(KEY_MINUS)) {
//		go_prev_puzzle(puzzleIndex, currPuzzleInfo, currPuzzle);
//		adjust_puzzle_dimensions(screenHeight, currPuzzleInfo.height, spriteScale, tileSize, spriteSize);
//		clear_background(gameRenderTexture2D);
//		history.clear();
//	}

//	if (IsKeyPressed(KEY_Z)) {
//		//can use currTime and deltaTime to rewind on press-and-hold
//		undo(currPuzzle, currPuzzleInfo);
//	}
		
//	if (IsKeyPressed(KEY_R)) {
//		restart(currPuzzleInfo, currPuzzle);
//		history.clear();
//	}

//	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
//		//this will double count a position when you push into a wall
//		//and no elements move
//		if (history.empty() || history.back() != currPuzzle) history.push_back(currPuzzle);
//		std::cout << history.size() << std::endl;
//		int input 					= GetKeyPressed();
//		int newPos 					= try_move(currPuzzle, input, currPuzzleInfo.playerIndex, currPuzzleInfo);
//		currPuzzleInfo.playerIndex 	= newPos;
//	}
//}

//void handle_editor_input(int input) {
//	return;
//}