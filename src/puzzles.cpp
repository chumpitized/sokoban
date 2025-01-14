#include "puzzles.h"
#include "raylib.h"

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
	//example
	{
		4,3,3,3,4,
		4,1,1,1,4,
		4,0,3,1,4,
		4,1,1,1,4,
		3,3,3,3,3
	}
};

std::vector<PuzzleInfo> puzzleInfos = {
	PuzzleInfo(5, 5, 0)
};

RenderTexture2D create_game_texture(int screenWidth, int screenHeight) {
	RenderTexture2D gameTexture = LoadRenderTexture(screenWidth, screenHeight);
		BeginTextureMode(gameTexture);
		ClearBackground(BLACK);
	EndTextureMode();
	return gameTexture;
}

int get_puzzle_draw_offset(int tileSize, int axisWidth, int windowSize) {
	return (windowSize - (tileSize * axisWidth)) / 2;
}

void draw_puzzle_to_texture(PuzzleInfo& puzzleInfo, RenderTexture2D& texture, std::vector<Texture2D>& sprites, int tileSize, int screenWidth, int screenHeight) {
	std::vector<int> puzzle = puzzles[puzzleInfo.index];
	int puzzleSize 			= puzzle.size();
	int puzzleWidth 		= puzzleInfo.width;
	int puzzleHeight 		= puzzleInfo.height;

	//need to do the math to scale the sprites
	//hardcoded for now

	BeginTextureMode(texture);
	for (int i = 0; i < puzzleSize; ++i) { 
		int tileXOffset 	= (i % puzzleWidth);
		int tileYOffset 	= (i) / puzzleHeight;

		int windowXOffset 	= get_puzzle_draw_offset(tileSize, puzzleWidth, screenWidth);
		int windowYOffset 	= get_puzzle_draw_offset(tileSize, puzzleHeight, screenHeight);

		//Draw texture with extended parameters (scale, rotation, etc.)
		DrawTextureEx(sprites[puzzle[i]], Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, 11.0, RAYWHITE); 
	}
	EndTextureMode();
};