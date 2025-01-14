#include "logic.h"
#include "puzzles.h"

#include <iostream>
#include <vector>

bool is_possible_move(int move, std::vector<int>& puzzle) {
	return (move >= 0 && move < puzzle.size() && puzzle[move] != Tiles::horizontal_wall && puzzle[move] != Tiles::vertical_wall);
}

int try_move(int input, int tile, PuzzleInfo& puzzleInfo) {
	int width			= puzzleInfo.width;
	int height			= puzzleInfo.height;
	int index			= puzzleInfo.index;

	std::vector<int>& puzzle = puzzles[index];

	int move = tile;
	if (input == KEY_W) move += -width;
	if (input == KEY_A)	move += -1;
	if (input == KEY_S) move += width;
	if (input == KEY_D) move += 1;

	if (is_possible_move(move, puzzle)) {

		if (puzzle[move] == Tiles::key && puzzle[tile] != Tiles::key) {
			try_move(input, move, puzzleInfo);
		}

		if (puzzle[move] == Tiles::black_tile) {
			puzzle[move] = puzzle[tile];
			puzzle[tile] = Tiles::black_tile;
			return move;
		}
	}
	//return original tile index
	return tile;
}