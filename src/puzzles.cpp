#include "puzzles.h"
#include "data.h"

#include <raylib.h>
#include <fstream>
#include <iostream>
#include <vector>

//Data
std::vector<std::vector<u16>> history;
std::vector<std::vector<u16>> puzzles;
std::vector<PuzzleInfo> puzzleInfos;

int puzzle_index = 0;
std::vector<u16> current_puzzle;
PuzzleInfo current_puzzle_info;

//Methods
std::vector<u16> get_current_puzzle() {
	return current_puzzle;
}

PuzzleInfo get_current_puzzle_info() {
	return current_puzzle_info;
}

void load_puzzles_from_file() {
	std::fstream file;
	file.open("data/puzzles/new_puzzle", std::ios::in | std::ios::binary);
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
	int player_index = 0;

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
				puzzle.pop_back();
				puzzles.push_back(puzzle);

				u8 width 	= last >> 8;
				u8 height 	= last;

				puzzleInfos.push_back(PuzzleInfo{width, height, puzzle_count++, player_index});
				player_index = 0;
				puzzle.clear();
			}
		} else {
			if (left == 0x00) player_index = puzzle.size();
			puzzle.push_back(tile);
		}
	}

	current_puzzle = puzzles[puzzle_index];
	current_puzzle_info = puzzleInfos[puzzle_index]; 
}


bool try_increment_puzzle() {
	if (puzzle_index + 1 < puzzles.size()) {
		puzzle_index++;
		current_puzzle = puzzles[puzzle_index];
		current_puzzle_info	= puzzleInfos[puzzle_index];
		return true;
	} else {
		std::cout << "INCREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}
bool try_decrement_puzzle() {
	if (puzzle_index - 1 >= 0) {
		puzzle_index--;
		current_puzzle = puzzles[puzzle_index];
		current_puzzle_info	= puzzleInfos[puzzle_index];
		return true;
	} else {
		std::cout << "DECREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}

void undo_last_move() {
	if (!history.empty()) {
		std::vector<u16> prev = history.back();
		history.pop_back();
	
		for (int i = 0; i < prev.size(); ++i) {
			u8 entity = prev[i] >> 8;

			if (entity == 0) {
				current_puzzle_info.playerIndex = i;
				break;
			}
		}
		current_puzzle = prev;
	}
}

void restart_level() {
	current_puzzle 		= puzzles[puzzle_index];
	current_puzzle_info = puzzleInfos[puzzle_index];
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
	int width	= current_puzzle_info.width;
	int height	= current_puzzle_info.height;
	int index	= current_puzzle_info.index;

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
			current_puzzle_info.playerIndex 	= newPos;
			return newPos;
		}
	}

	return currentCellIndex;
}