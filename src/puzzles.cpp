#include "puzzles.h"
#include "data.h"

#include <raylib.h>
#include <fstream>
#include <iostream>
#include <vector>

//Data
std::vector<std::vector<u16>> history;
std::vector<std::vector<u16>> puzzles;;

int puzzle_index = 0;

std::vector<u16> current_puzzle;

//Methods
std::vector<std::vector<u16>> get_puzzles() {
	return puzzles;
}

int get_puzzle_index() {
	return puzzle_index;
}

std::vector<u16> get_const_puzzle() {
	return puzzles[puzzle_index];
}

std::vector<u16> get_current_puzzle() {
	return current_puzzle;
}

u8 get_current_puzzle_width() {
	return current_puzzle[current_puzzle.size() - 3] >> 8;
}

u8 get_current_puzzle_height() {
	return current_puzzle[current_puzzle.size() - 3];
}

u8 get_current_puzzle_player_index() {
	return current_puzzle[current_puzzle.size() - 2];
}

//this doesn't update the puzzle index...
void set_current_puzzle_and_index(int index) {
	if (index < puzzles.size() && index >= 0) {
		puzzle_index = index;
		current_puzzle = puzzles[puzzle_index];
		std::cout << "selected puzzle index: " << index << std::endl;
	}
}

bool is_edit_puzzle_same_as_saved_puzzle() {
	return current_puzzle == puzzles[puzzle_index];
}

//this DOES NOT save
void create_new_puzzle_and_update_vals() {
	puzzles.push_back(current_puzzle);
	puzzle_index = puzzles.size() - 1;
}

bool is_edit_puzzle_valid(std::vector<u16>& canvas, int canvas_tile_width) {
	u8 expected_width	= 0;
	u8 row_width		= 0;
	u8 potential_gap 	= 0;

	u8 players			= 0;
	u8 keys				= 0;
	u8 locks			= 0;

	for (int i = 0; i < canvas_tile_width; ++i) {
		row_width		= 0;
		potential_gap 	= 0;

		for (int j = 0; j < canvas_tile_width; ++j) {
			u8 index 	= (i * canvas_tile_width) + j;
			u16 value	= canvas[index];

			u8 high 	= value >> 8;
			u8 low 		= value;

			if (high == 0x0) players++;
			if (high == 0x1) keys++;
			if (low == 0x04) locks++;

			if (canvas[index] != 0xffff && potential_gap > 0) return false;
			if (canvas[index] != 0xffff) row_width++;
			if (row_width > 0 && low == 0xff) potential_gap++;
		}

		if (expected_width == 0) expected_width = row_width;
		//have to handle empty rows by checking that row_width is greater than 0
		if (row_width > 0 && row_width != expected_width) return false;
	}

	if (players != 1 || keys < locks) return false;

	return true;
}

u8 get_edit_puzzle_width(std::vector<u16>& canvas) {
	int width = 0;
	
	for (auto cell : canvas) {
		if (width > 0 && cell == 0xffff) return width;
		if (cell != 0xffff) width++;
	}

	return width;
}

void set_current_puzzle_to_edit_puzzle(std::vector<u16>& canvas, int canvas_tile_width) {
	if (!is_edit_puzzle_valid(canvas, canvas_tile_width)) return;

	u8 player_index = 0;
	u8 width = get_edit_puzzle_width(canvas);

	std::vector<u16> puzzle_cutout;
	
	for (int i = 0; i < canvas.size(); ++i) {
		if ((u8)(canvas[i] >> 8) == 0x0) player_index = puzzle_cutout.size();
		if (canvas[i] != 0xffff) puzzle_cutout.push_back(canvas[i]);
	}
	
	u8 height = puzzle_cutout.size() / width;	
	u16 dimensions = width << 8 | height;

	puzzle_cutout.push_back(dimensions);
	puzzle_cutout.push_back((u16)player_index);
	puzzle_cutout.push_back(0xffff);

	current_puzzle = puzzle_cutout;
}

void overwrite_puzzle_in_puzzles(std::vector<u16>& puzzle, int index) {
	puzzles[index] = puzzle;
}

void load_puzzles_from_file() {
	std::fstream file;
	file.open("data/puzzles/saved_puzzles", std::ios::in | std::ios::binary);
	std::vector<u16> puzzle;

	if (!file) {
		std::cerr << "Failed to open file!" << std::endl;
		return;
	}

	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);

	if (length & 1) {
		std::cerr << "File length is not even!" << std::endl;
		return;
	}

	int puzzle_count = 0;
	u16 player_index = 0;

	u8 buffer[length];

	file.read(reinterpret_cast<char*>(buffer), length);
	file.close();

	for (int i = 0; i < length; i+=2) {
		u16 left = buffer[i] << 8;
		u16 right = buffer[i + 1];
		u16 tile = left | right;

		if (tile == 0xffff) {
			if (!puzzle.empty()) {
				u16 last = puzzle.back();

				//this is gonna go!
				puzzle.push_back(0xffff);

				puzzles.push_back(puzzle);

				u8 width 	= last >> 8;
				u8 height 	= last;

				player_index = 0;
				puzzle.clear();
			}
		} else {
			if (left == 0x00) player_index = puzzle.size();
			puzzle.push_back(tile);
		}
	}

	current_puzzle = puzzles[puzzle_index];
}

void save_puzzles_to_file() {
	std::fstream file;
    file.open("data/puzzles/saved_puzzles", std::ios::out | std::ios::binary);
 
	if (!file) {
		std::cerr << "ERROR: FAILED TO OPEN FILE" << std::endl;
		return;
	}

	for (int i = 0; i < puzzles.size(); ++i) {
		std::vector<u16> puzzle = puzzles[i];
		
		int length = (puzzle.size() * 2);
		u8 buffer[length];
	
		int bufferIndex = 0;
		for (int i = 0; i < puzzle.size(); ++i) {
			bufferIndex = i * 2;
			buffer[bufferIndex] 	= (u8)(puzzle[i] >> 8);
			buffer[bufferIndex + 1] = (u8)(puzzle[i]); 
		}
	
		file.write(reinterpret_cast<char*>(buffer), length);
	}		
	
	file.close();
}

//save the current puzzle index to file
//read from the file on startup
//void save_progress() {
	

//}

bool try_increment_puzzle() {
	if (puzzle_index + 1 < puzzles.size()) {
		puzzle_index++;
		current_puzzle 				= puzzles[puzzle_index];
		return true;
	} else {
		std::cerr << "INCREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}

bool try_decrement_puzzle() {
	if (puzzle_index - 1 >= 0) {
		puzzle_index--;
		current_puzzle 				= puzzles[puzzle_index];
		return true;
	} else {
		std::cerr << "DECREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}

void undo_last_move() {
	if (!history.empty()) {
		std::vector<u16> prev = history.back();
		history.pop_back();
	
		current_puzzle = prev;
	}
}

void restart_level() {
	if (!history.empty()) {
		std::cout << "restarting without edit puzzle" << std::endl;
		current_puzzle = history[0];
	}
	history.clear();
}

bool is_possible_move(int newPos) {
	if (newPos >= 0 && newPos < current_puzzle.size()) {
		u8 tileAtNewPos = current_puzzle[newPos];
		if (tileAtNewPos != Tiles::horizontal_wall && tileAtNewPos != Tiles::vertical_wall) {
			return true;
		}
	}
	return false;
}

int try_move(int input, int currentCellIndex) {
	u8 width = get_current_puzzle_width();
	u8 height = get_current_puzzle_height();
	u8 index = get_puzzle_index();

	int newPos = currentCellIndex;
	if (input == KEY_W) newPos += -width;
	if (input == KEY_A)	newPos += -1;
	if (input == KEY_S) newPos += width;
	if (input == KEY_D) newPos += 1;

	if (is_possible_move(newPos)) {
		u8 entityAtCurrPos 	= current_puzzle[currentCellIndex] >> 8;
		u8 tileAtCurrPos	= current_puzzle[currentCellIndex];

		u8 entityAtNewPos 	= current_puzzle[newPos] >> 8;
		u8 tileAtNewPos 	= current_puzzle[newPos]; 

		if (entityAtCurrPos != Entities::key && entityAtNewPos == Entities::key) {
			//recursive for keys
			try_move(input, newPos);
		}

		//check that all movable entities have moved
		entityAtNewPos = current_puzzle[newPos] >> 8;

		if (entityAtNewPos == 0xff) {
			current_puzzle[newPos] 				= entityAtCurrPos << 8 | tileAtNewPos;
			current_puzzle[currentCellIndex] 	= 0xff00 | tileAtCurrPos;
			current_puzzle[current_puzzle.size() - 2] = (u16)newPos;
			return newPos;
		}
	}

	return currentCellIndex;
}