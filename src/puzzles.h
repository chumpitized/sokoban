#ifndef PUZZLES_H
#define PUZZLES_H

#include "data.h"

#include <vector>
#include <raylib.h>

struct PuzzleInfo {
	int width;
	int height;
	int index;

	int playerIndex;

	PuzzleInfo(int width, int height, int index);
};

enum Tiles {
	player,
	black_tile,
	gray_tile,
	horizontal_wall,
	vertical_wall,
	locked_door,
	key
};

extern int get_puzzle_height();
extern std::vector<PuzzleInfo> puzzleInfos;
extern std::vector<std::vector<int>> puzzles;
extern std::vector<int> players;
extern std::vector<std::vector<int>> boxes;

bool try_increment_puzzle();
bool try_decrement_puzzle();

#endif