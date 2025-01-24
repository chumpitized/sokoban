#include "draw.h"
#include "data.h"
#include "puzzles.h"

void adjust_puzzle_dimensions(int screenHeight, int puzzleHeight, int& spriteScale, int& tileSize, int spriteSize) {
	spriteScale	= (screenHeight / puzzleHeight) / spriteSize;
	tileSize 	= spriteScale * spriteSize;
}

RenderTexture2D create_game_texture(int screenWidth, int screenHeight) {
	RenderTexture2D gameTexture = LoadRenderTexture(screenWidth, screenHeight);
	BeginTextureMode(gameTexture);
	ClearBackground(BLACK);
	EndTextureMode();
	return gameTexture;
}

int get_puzzle_draw_offset(int tileSize, int axisWidth, int axisScreenWidth) {
	return (axisScreenWidth - (tileSize * axisWidth)) / 2;
}

void clear_background(RenderTexture2D& texture) {
	BeginTextureMode(texture);
	ClearBackground(BLACK);
	EndTextureMode();
}

void draw_puzzle_to_texture(RenderTexture2D& texture, std::vector<Texture2D>& sprites, int tileSize, int screenWidth, int screenHeight, int spriteScale) {
	//std::vector<int> puzzle = puzzles[puzzleInfo.index];
	PuzzleInfo puzzleInfo 	= puzzleInfos[puzzleIndex];
	std::vector<int> puzzle = puzzles[puzzleIndex];

	int puzzleSize 			= puzzle.size();
	int puzzleWidth 		= puzzleInfo.width;
	int puzzleHeight 		= puzzleInfo.height;
	const std::vector<int> const_puzzle = puzzles[puzzleIndex];

	BeginTextureMode(texture);
	for (int i = 0; i < puzzleSize; ++i) { 
		int tileXOffset 	= i % puzzleWidth;
		int tileYOffset 	= i / puzzleWidth;

		int windowXOffset 	= get_puzzle_draw_offset(tileSize, puzzleWidth, screenWidth);
		int windowYOffset 	= get_puzzle_draw_offset(tileSize, puzzleHeight, screenHeight);

		//In order to draw each tile properly without creating a ton of additional sprites, 
		//we just redraw the const_puzzle's tiles, which are original to the puzzle,
		//beneath the moving elements (which also have transparency). This means we need
		//to ignore the original locations of the keys (boxes) and player, otherwise we will
		//draw them again.
		if ((puzzle[i] == 0 || puzzle[i] == 6) && (const_puzzle[i] == Tiles::key || const_puzzle[i] == Tiles::player)) {
			DrawTextureEx(sprites[1], Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, spriteScale, RAYWHITE);
		} else {
			DrawTextureEx(sprites[const_puzzle[i]], Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, spriteScale, RAYWHITE);
		}

		DrawTextureEx(sprites[puzzle[i]], Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, spriteScale, RAYWHITE); 
	}
	EndTextureMode();
};