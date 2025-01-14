#include "logic.h"
#include "puzzles.h"

#include <iostream>
#include <vector>

bool is_valid_move(int move, std::vector<int>& puzzle) {
	return (move >= 0 || move < puzzle.size() || puzzle[move] != Tiles::horizontal_wall || puzzle[move] != Tiles::vertical_wall);
}

void move(int input, PuzzleInfo& puzzleInfo) {
	int width			= puzzleInfo.width;
	int height			= puzzleInfo.height;
	int index			= puzzleInfo.index;
	int playerIndex		= puzzleInfo.playerIndex;

	std::vector<int>& puzzle = puzzles[index];

	int move = playerIndex;
	if (input == KEY_W) move += -width;
	if (input == KEY_A)	move += -1;
	if (input == KEY_S) move += width;
	if (input == KEY_D) move += 1;

	if (is_valid_move(move, puzzle)) {
		std::cout << puzzleInfo.playerIndex << std::endl;
		puzzleInfo.playerIndex = move;
		std::cout << puzzleInfo.playerIndex << std::endl;
		puzzle[move]		= player;
		puzzle[playerIndex] = black_tile;
	}
}