#include "draw.h"
#include "data.h"
#include "sprites.h"

//void adjust_puzzle_dimensions(int puzzleHeight, int& spriteScale, int& tileSize, int spriteSize) {
//	spriteScale	= (screenHeight / puzzleHeight) / spriteSize;
//	tileSize 	= spriteScale * spriteSize;
//}

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
	PuzzleInfo puzzleInfo 	= puzzleInfos[puzzleIndex];
	std::vector<u16> puzzle = current_puzzle;

	int puzzleSize 			= puzzle.size();
	int puzzleWidth 		= puzzleInfo.width;
	int puzzleHeight 		= puzzleInfo.height;
	const std::vector<u16> const_puzzle = puzzles[puzzleIndex];

	BeginTextureMode(texture);
	for (int i = 0; i < puzzleSize; ++i) { 
		int tileXOffset 	= i % puzzleWidth;
		int tileYOffset 	= i / puzzleWidth;

		int windowXOffset 	= get_puzzle_draw_offset(tileSize, puzzleWidth, screenWidth);
		int windowYOffset 	= get_puzzle_draw_offset(tileSize, puzzleHeight, screenHeight);

		u8 entity 	= puzzle[i] >> 8;
		u8 tile 	= puzzle[i]; 
		
		Texture2D tile_texture;
		Texture2D entity_texture;

		if (tile < tiles.size() && tile >= 0) {
			tile_texture 	= tiles[tile];
			DrawTextureEx(tile_texture, Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, spriteScale, RAYWHITE);
		}
		if (entity < tiles.size() && entity >= 0) {
			entity_texture	= entities[entity];
			DrawTextureEx(entity_texture, Vector2{(float)(tileXOffset * tileSize) + windowXOffset, (float)(tileYOffset * tileSize) + windowYOffset}, 0.0, spriteScale, RAYWHITE);
		}
	}
	EndTextureMode();
};