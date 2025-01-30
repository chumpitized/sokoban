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

	//PuzzleInfo(int width, int height, int index);
};

extern std::vector<std::vector<u16>> history;
extern std::vector<std::vector<u16>> puzzles;
extern std::vector<PuzzleInfo> puzzleInfos;

extern int puzzle_index;
extern std::vector<u16> current_puzzle;
extern PuzzleInfo current_puzzle_info;

//Methods
//void set_play_puzzle_to_edit_puzzle(std::vector<u16>& playPuzzle, std::vector<u16>& editPuzzle);

std::vector<u16> get_const_puzzle();
std::vector<u16> get_current_puzzle();
void set_current_puzzle(std::vector<u16> new_puzzle);
std::vector<u16> get_current_edit_puzzle();
void set_current_edit_puzzle(std::vector<u16> new_edit_puzzle);
PuzzleInfo get_current_puzzle_info();

void load_puzzles_from_file();

bool try_increment_puzzle();
bool try_decrement_puzzle();

void undo_last_move();
void restart_level();

bool is_possible_move(int move);
int try_move(int input, int currentCellIndex);

#endif