#include "logic.h"
#include "puzzles.h"
#include "data.h"

#include <iostream>
#include <vector>

bool is_possible_move(int move, std::vector<u16>& puzzle) {
	if (move >= 0 && move < puzzle.size()) {
		u8 tileAtMove = puzzle[move];
		if (tileAtMove != Tiles::horizontal_wall && tileAtMove != Tiles::vertical_wall) {
			return true;
		}
	}
	return false;
}

int try_move(std::vector<u16>& puzzle, int input, int currTile, PuzzleInfo& puzzleInfo) {
	int width			= puzzleInfo.width;
	int height			= puzzleInfo.height;
	int index			= puzzleInfo.index;

	const std::vector<u16>& const_puzzle = puzzles[index];

	int move = currTile;
	if (input == KEY_W) move += -width;
	if (input == KEY_A)	move += -1;
	if (input == KEY_S) move += width;
	if (input == KEY_D) move += 1;

	if (is_possible_move(move, puzzle)) {
		u8 entityAtMove = puzzle[move] >> 8;
		u8 tileAtMove 	= puzzle[move]; 

		u8 entityAtCurr = puzzle[currTile] >> 8;
		u8 tileAtCurr	= puzzle[currTile];

		//we have to check that the entity on the current tile isn't a key
		//because the recursive call will try to move a key and we don't
		//want keys pushing keys...
		if (entityAtMove == Entities::key && entityAtCurr != Entities::key) {
			try_move(puzzle, input, move, puzzleInfo);
		}

		//check that all movable entities have moved
		entityAtMove = puzzle[move] >> 8;

		if (entityAtMove == 0xff && tileAtMove != Tiles::horizontal_wall && tileAtMove != Tiles::vertical_wall) {
			puzzle[move] 			= entityAtCurr << 8 | tileAtMove;
			puzzle[currTile] 		= 0xff00 | tileAtCurr;
			puzzleInfo.playerIndex 	= move;
			return move;
		}
	}

	return currTile;
}