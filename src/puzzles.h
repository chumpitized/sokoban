#ifndef PUZZLES_H
#define PUZZLES_H

#include "data.h"

#include <vector>
#include <raylib.h>

//Data
enum Entities {
	player,
	key
};

enum Tiles {
	black_tile,
	gray_tile,
	horizontal_wall,
	vertical_wall,
	locked_door
};

struct PuzzleInfo {
	int width;
	int height;
	int index;

	int playerIndex;

	PuzzleInfo(int width, int height, int index);
};

extern std::vector<std::vector<u16>> history;
extern std::vector<std::vector<u16>> puzzles;
extern std::vector<PuzzleInfo> puzzleInfos;

extern int puzzle_index;
extern std::vector<u16> current_puzzle;
extern PuzzleInfo current_puzzle_info;

//Methods
std::vector<u16> get_current_puzzle();
PuzzleInfo get_current_puzzle_info();

bool try_increment_puzzle();
bool try_decrement_puzzle();

void undo_last_move();
void restart_level();

bool is_possible_move(int move);
int try_move(int input, int currentCellIndex);

#endif