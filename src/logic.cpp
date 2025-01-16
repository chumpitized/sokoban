#include "logic.h"
#include "puzzles.h"

#include <iostream>
#include <vector>

bool is_possible_move(int move, std::vector<int>& puzzle) {
	return (move >= 0 && move < puzzle.size() && puzzle[move] != Tiles::horizontal_wall && puzzle[move] != Tiles::vertical_wall);
}

int try_move(std::vector<int>& puzzle, int input, int currTile, PuzzleInfo& puzzleInfo) {
	int width			= puzzleInfo.width;
	int height			= puzzleInfo.height;
	int index			= puzzleInfo.index;

	const std::vector<int>& const_puzzle = puzzles[index];

	int move = currTile;
	if (input == KEY_W) move += -width;
	if (input == KEY_A)	move += -1;
	if (input == KEY_S) move += width;
	if (input == KEY_D) move += 1;

	if (is_possible_move(move, puzzle)) {

		if (puzzle[move] == Tiles::key && puzzle[currTile] != Tiles::key) {
			try_move(puzzle, input, move, puzzleInfo);
		}

		if (puzzle[move] == Tiles::black_tile || puzzle[move] == Tiles::locked_door) {
			puzzle[move] = puzzle[currTile];
			if (const_puzzle[currTile] == Tiles::player || const_puzzle[currTile] == Tiles::key) {
				puzzle[currTile] = Tiles::black_tile;
			} else {
				puzzle[currTile] = const_puzzle[currTile];
			}
			return move;
		}
	}

	return currTile;
}