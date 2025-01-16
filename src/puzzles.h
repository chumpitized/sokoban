#ifndef PUZZLES_H
#define PUZZLES_H

#include <vector>
#include "raylib.h"

enum Tiles {
	player,
	black_tile,
	gray_tile,
	horizontal_wall,
	vertical_wall,
	locked_door,
	key
};

struct PuzzleInfo {
	int width;
	int height;
	int index;

	int playerIndex;

	PuzzleInfo(int width, int height, int index);
};

extern std::vector<PuzzleInfo> puzzleInfos;
extern std::vector<std::vector<int>> puzzles;
extern std::vector<int> players;
extern std::vector<std::vector<int>> boxes;

RenderTexture2D create_game_texture(int screenWidth, int screenHeight);
int get_puzzle_draw_offset(int tileSize, int axisWidth, int windowSize);
void draw_puzzle_to_texture(std::vector<int>& puzzle, PuzzleInfo& puzzleInfo, RenderTexture2D& texture, std::vector<Texture2D>& sprites, int tileSize, int screenWidth, int screenHeight, int spriteScale);

#endif