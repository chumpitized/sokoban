#include "puzzles.h"
#include "data.h"

#include <raylib.h>
#include <iostream>
#include <vector>

//Data
PuzzleInfo::PuzzleInfo(int width, int height, int index) {
	this->width 	= width;
	this->height 	= height;
	this->index 	= index;

	for(int i = 0; i < puzzles[index].size(); ++i) {
		if (puzzles[index][i] == 0) playerIndex = i;
	}
};

std::vector<std::vector<u16>> history;
std::vector<std::vector<u16>> puzzles = {
	{
		0xff03,0xff02,0xff02, 0xff03, 0xff00, 0xff00,
		0xff03,0xff01,0xff04, 0xff03, 0xff00, 0xff00,
		0xff03,0xff00,0xff01, 0xff02, 0xff02, 0xff03,
		0xff03,0x0104,0x0000, 0xff01, 0xff00, 0xff03,
		0xff03,0xff00,0xff01, 0x0100, 0xff01, 0xff03,
		0xff03,0xff01,0xff00, 0xff03, 0xff02, 0xff02,
		0xff02,0xff02,0xff02, 0xff02, 0xff00, 0xff00
	}
};
std::vector<PuzzleInfo> puzzleInfos = {
	PuzzleInfo(6, 7, 0)
};

int puzzle_index 				= 0;
std::vector<u16> current_puzzle = puzzles[puzzle_index];
PuzzleInfo current_puzzle_info	= puzzleInfos[puzzle_index];

//Methods
std::vector<u16> get_current_puzzle() {
	return current_puzzle;
}

PuzzleInfo get_current_puzzle_info() {
	return current_puzzle_info;
}

bool try_increment_puzzle() {
	if (puzzle_index + 1 < puzzles.size()) {
		puzzle_index++;
		return true;
	} else {
		std::cout << "INCREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}
bool try_decrement_puzzle() {
	if (puzzle_index - 1 >= 0) {
		puzzle_index--;
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