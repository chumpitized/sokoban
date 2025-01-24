#ifndef PUZZLES_H
#define PUZZLES_H

#include <vector>
#include "raylib.h"

enum Tiles {
	player,
	black_tile,
	gray_tile,
	horizontal_wall,
	vertical_wall,
	locked_door,
	key
};

struct PuzzleInfo {
	int width;
	int height;
	int index;

	int playerIndex;

	PuzzleInfo(int width, int height, int index);
};

extern std::vector<PuzzleInfo> puzzleInfos;
extern std::vector<std::vector<int>> puzzles;
extern std::vector<int> players;
extern std::vector<std::vector<int>> boxes;

void increment_puzzle_index();
void decrement_puzzle_index();

#endif