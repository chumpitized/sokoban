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

extern std::vector<std::vector<u16>> history;
extern std::vector<std::vector<u16>> puzzles;

extern int puzzle_index;
extern std::vector<u16> current_puzzle;

//Methods
int get_puzzle_index();
u8 get_edit_puzzle_width(std::vector<u16>& canvas);
void set_current_puzzle_to_edit_puzzle(std::vector<u16>& canvas, int canvas_tile_width);

std::vector<std::vector<u16>> get_puzzles();
std::vector<u16> get_const_puzzle();
std::vector<u16> get_current_puzzle();

u8 get_current_puzzle_width();
u8 get_current_puzzle_height();
u8 get_current_puzzle_player_index();

void set_current_puzzle_and_index(int index);

void create_new_puzzle_and_update_vals();

bool is_edit_puzzle_same_as_saved_puzzle();
bool is_edit_puzzle_valid(std::vector<u16>& canvas, int canvas_tile_width);

void overwrite_puzzle_in_puzzles(std::vector<u16>& puzzle, int index);
void load_puzzles_from_file();
void save_puzzles_to_file();
void load_progress();
void save_progress();

bool try_increment_puzzle();
bool try_decrement_puzzle();

void undo_last_move();
void restart_level();

bool is_possible_move(int move);
int try_move(int input, int currentCellIndex);

bool complete_puzzle();

#endif