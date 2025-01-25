#include "puzzles.h"
#include "data.h"

#include <raylib.h>
#include <iostream>
#include <vector>

PuzzleInfo::PuzzleInfo(int width, int height, int index) {
	this->width 	= width;
	this->height 	= height;
	this->index 	= index;

	for(int i = 0; i < puzzles[index].size(); ++i) {
		if (puzzles[index][i] == 0) playerIndex = i;
	}
};


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

int get_puzzle_height() {
	return puzzleInfos[puzzleIndex].height;
}

bool try_increment_puzzle() {
	if (puzzleIndex + 1 < puzzles.size()) {
		puzzleIndex++;
		return true;
	} else {
		std::cout << "INCREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}
bool try_decrement_puzzle() {
	if (puzzleIndex - 1 >= 0) {
		puzzleIndex--;
		return true;
	} else {
		std::cout << "INCREMENTED INDEX OUT OF RANGE!" << std::endl;
		return false;
	}
}