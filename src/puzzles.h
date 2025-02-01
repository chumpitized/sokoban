#ifndef PUZZLES_H
#define PUZZLES_H

#include "data.h"

#include <vector>
#include <raylib.h>

//Data
//synced with sprite arrays for the same elements...
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
};

extern std::vector<std::vector<u16>> history;
extern std::vector<std::vector<u16>> puzzles;
extern std::vector<PuzzleInfo> puzzleInfos;

extern int puzzle_index;
extern std::vector<u16> current_puzzle;
extern std::vector<u16> current_edit_puzzle;
extern PuzzleInfo current_puzzle_info;
extern PuzzleInfo current_edit_puzzle_info;

//Methods
u8 get_edit_puzzle_width(std::vector<u16>& canvas);
void set_current_puzzle_to_edit_puzzle(std::vector<u16>& canvas, int canvas_tile_width);

std::vector<std::vector<u16>> get_puzzles();
std::vector<u16> get_const_puzzle();
std::vector<u16> get_current_puzzle();
void set_current_puzzle(std::vector<u16> new_puzzle);
std::vector<u16> get_current_edit_puzzle();
PuzzleInfo get_current_puzzle_info();
PuzzleInfo get_current_edit_puzzle_info();

bool is_edit_puzzle_same_as_saved_puzzle();
bool is_edit_puzzle_valid(std::vector<u16>& canvas, int canvas_tile_width);

void overwrite_puzzle_in_puzzles(std::vector<u16>& puzzle, int index);
void load_puzzles_from_file();
void save_puzzles_to_file();

bool try_increment_puzzle();
bool try_decrement_puzzle();

void undo_last_move();
void restart_level();

bool is_possible_move(int move);
int try_move(int input, int currentCellIndex);

#endif