#include "draw.h"
#include "data.h"
#include "puzzles.h"

//void adjust_puzzle_dimensions(int puzzleHeight, int& spriteScale, int& tileSize, int spriteSize) {
//	spriteScale	= (screenHeight / puzzleHeight) / spriteSize;
//	tileSize 	= spriteScale * spriteSize;
//}

std::vector<Texture2D> entities;
std::vector<Texture2D> tiles;

int get_sprite_scale() {
	return (screenHeight / get_current_puzzle_info().height) / spriteSize;
}
int get_tile_size() {
	return get_sprite_scale() * spriteSize;
}

RenderTexture2D create_game_texture(int screenWidth, int screenHeight) {
	RenderTexture2D gameTexture = LoadRenderTexture(screenWidth, screenHeight);
	BeginTextureMode(gameTexture);
	ClearBackground(BLACK);
	EndTextureMode();
	return gameTexture;
}

Texture2D load_sprite(const char* path) {
	Image image = LoadImage(path);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
};

void load_sprites() {
	entities = {
		load_sprite("data/sprites/character_transparent.png"),
		load_sprite("data/sprites/key_transparent.png")
	};

	tiles = {
		load_sprite("data/sprites/black_tile.png"),
		load_sprite("data/sprites/gray_tile.png"),
		load_sprite("data/sprites/horizontal_wall.png"),
		load_sprite("data/sprites/vertical_wall.png"),
		load_sprite("data/sprites/locked_door.png")
	};
};

int get_puzzle_draw_offset(int tileSize, int axisWidth, int axisScreenWidth) {
	return (axisScreenWidth - (tileSize * axisWidth)) / 2;
}

void clear_background(RenderTexture2D& texture) {
	BeginTextureMode(texture);
	ClearBackground(BLACK);
	EndTextureMode();
}

void draw_puzzle_to_texture(RenderTexture2D& texture, int screenWidth, int screenHeight) {
	int spriteScale = get_sprite_scale();
	int tileSize	= get_tile_size();

	PuzzleInfo puzzleInfo 	= get_current_puzzle_info();
	std::vector<u16> puzzle = get_current_puzzle();

	int puzzleSize 			= puzzle.size();
	int puzzleWidth 		= puzzleInfo.width;
	int puzzleHeight 		= puzzleInfo.height;
	const std::vector<u16> const_puzzle = puzzles[puzzle_index];

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