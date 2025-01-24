#include "puzzles.h"
#include "raylib.h"

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

std::vector<std::vector<int>> puzzles = {
	//Microban 1
	{
		4,3,3,4,1,1,
		4,1,5,4,1,1,
		4,1,1,3,3,4,
		4,6,0,1,1,4,
		4,5,1,6,1,4,
		4,1,1,4,3,3,
		3,3,3,3,1,1
	},
	{
		4,4,4,4,4,1,
		4,3,3,3,4,1,
		4,5,1,1,3,4,
		4,0,6,6,1,4,
		3,4,1,1,1,4,
		1,3,4,1,1,4,
		1,1,3,4,5,4,
		1,1,1,3,3,3
	}
};

std::vector<PuzzleInfo> puzzleInfos = {
	PuzzleInfo(6, 7, 0),
	PuzzleInfo(6, 8, 1)
};

void go_next_puzzle(int& index, PuzzleInfo& puzzleInfo, std::vector<int>& puzzle) {
	if (index + 1< puzzles.size()) {
		index++;
		puzzle 		= puzzles[index];
		puzzleInfo 	= puzzleInfos[index];
	} else {
		std::cout << "LAST PUZZLE" << std::endl;
	}
}
void go_prev_puzzle(int& index, PuzzleInfo& puzzleInfo, std::vector<int>& puzzle) {
	if (index - 1 >= 0) {
		index--;
		puzzle 		= puzzles[index];
		puzzleInfo 	= puzzleInfos[index];
	} else {
		std::cout << "FIRST PUZZLE" << std::endl;
	}
}