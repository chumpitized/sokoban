#include "puzzles.h"
#include "data.h"

#include <vector>

std::vector<std::vector<int>> history;

void undo() {
	std::vector<int>& puzzle = puzzles[puzzleIndex]; 
	PuzzleInfo& puzzleInfo = puzzleInfos[puzzleIndex];

	if (!history.empty()) {
		std::vector<int> prev = history.back();
		history.pop_back();
	
		for (int i = 0; i < prev.size(); ++i) {
			if (prev[i] == 0) {
				puzzleInfo.playerIndex = i;
				break;
			}
		}
		puzzle = prev;
	}
}

void restart() {
	std::vector<int>& puzzle = puzzles[puzzleIndex]; 
	PuzzleInfo& puzzleInfo = puzzleInfos[puzzleIndex];

	puzzle = puzzles[puzzleInfo.index];
	for (int i = 0; i < puzzle.size(); ++i) {
		if (puzzle[i] == 0) {
			puzzleInfo.playerIndex = i;
			break;
		}
	}
}
