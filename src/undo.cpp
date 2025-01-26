//#include "puzzles.h"
//#include "data.h"

//#include <vector>

//std::vector<std::vector<u16>> history;

//void undo_last_move() {
//	std::vector<u16>& puzzle = current_puzzle; 
//	PuzzleInfo& puzzleInfo = puzzleInfos[puzzleIndex];

//	if (!history.empty()) {
//		std::vector<u16> prev = history.back();
//		history.pop_back();
	
//		for (int i = 0; i < prev.size(); ++i) {
//			u8 entity = prev[i] >> 8;

//			if (entity == 0) {
//				puzzleInfo.playerIndex = i;
//				break;
//			}
//		}
//		puzzle = prev;
//	}
//}

//void restart_level() {
//	std::vector<u16>& puzzle = current_puzzle; 
//	PuzzleInfo& puzzleInfo = puzzleInfos[puzzleIndex];

//	puzzle = puzzles[puzzleIndex];
//	for (int i = 0; i < puzzle.size(); ++i) {
//		u8 entity = puzzle[i] >> 8;

//		if (entity == 0) {
//			puzzleInfo.playerIndex = i;
//			break;
//		}
//	}
//}
