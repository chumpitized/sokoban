#ifndef PUZZLES_H
#define PUZZLES_H

#include <vector>
#include "raylib.h"

struct PuzzleInfo {
	int width;
	int height;
	int index;
	
	PuzzleInfo(int width, int height, int index) {
		this->width 	= width;
		this->height 	= height;		
		this->index 	= index;
	};
};

extern std::vector<PuzzleInfo> puzzlesInfo;
extern std::vector<std::vector<int>> puzzles;

RenderTexture2D create_game_texture(int screenWidth, int screenHeight);
int get_puzzle_draw_offset(int tileSize, int axisWidth, int windowSize);
void draw_puzzle_to_texture(PuzzleInfo& puzzleInfo, RenderTexture2D& texture, std::vector<Texture2D>& sprites, int tileSize, int screenWidth, int screenHeight);

#endif