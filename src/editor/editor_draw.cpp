#include "editor_data.h"
#include "editor_draw.h"

#include <raylib.h>
#include <vector>

std::vector<Texture2D> editor_entities;
std::vector<Texture2D> editor_tiles;

void draw_save_status() {
	bool save_status = false;

	if (save_status) {
		DrawText("Saved!", xTilesOffset, yTilesOffset + 200, fontSize, GREEN);
	} else {
		DrawText("Unsaved", xTilesOffset, yTilesOffset + 200, fontSize, RED);
	}
}

RenderTexture2D draw_editor_setup(int screenWidth, int screenHeight) {
	RenderTexture2D texture = LoadRenderTexture(screenWidth, screenHeight);
	
	BeginTextureMode(texture);
		ClearBackground(GRAY);
		draw_canvas_border();

		//Draw Entity Palette
		DrawText("Entities", xEntitiesFont, yEntitiesFont, fontSize, BLACK);
		draw_palette(editor_entities, paletteWidth, xEntitiesOffset, yEntitiesOffset, tileSize);

		//Draw Tile Palette
		DrawText("Tiles", xTilesFont, yTilesFont, fontSize, BLACK);
		draw_palette(editor_tiles, paletteWidth, xTilesOffset, yTilesOffset, tileSize);
	EndTextureMode();
	
	return texture;
}

void draw_selected_palette_square() {
	if (storedTile.isEntity) {
		int index = storedTile.storedIndex;
		float y = ((index / paletteWidth) * tileSize) + yEntitiesOffset;
		float x = ((index % paletteWidth) * tileSize) + xEntitiesOffset;

		DrawRectangleLinesEx(Rectangle{x, y, 64, 64}, 4, RED);
	} else {
		int index = storedTile.storedIndex;
		float y = ((index / paletteWidth) * tileSize) + yTilesOffset;
		float x = ((index % paletteWidth) * tileSize) + xTilesOffset;

		DrawRectangleLinesEx(Rectangle{x, y, 64, 64}, 4, RED);
	}
}

Texture2D load_editor_sprite(const char* path) {
	Image image = LoadImage(path);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
};

void load_editor_sprites() {
	editor_entities = {
		load_editor_sprite("data/sprites/character_transparent.png"),
		load_editor_sprite("data/sprites/key_transparent.png")
	};

	editor_tiles = {
		load_editor_sprite("data/sprites/black_tile.png"),
		load_editor_sprite("data/sprites/gray_tile.png"),
		load_editor_sprite("data/sprites/horizontal_wall.png"),
		load_editor_sprite("data/sprites/vertical_wall.png"),
		load_editor_sprite("data/sprites/locked_door.png")
	};
}

void draw_canvas_border() {
	float thickness = 3.0;
	float width		= canvasWidth + (thickness * 2);
	DrawRectangleLinesEx(Rectangle{xOffset - thickness, yOffset - thickness, width, width}, 3.0, BLACK);
}


void load_puzzle_into_canvas(std::vector<u16>& canvas, std::vector<u16>& puzzle, int puzzleWidth, int puzzleHeight) {
	if (puzzle.size() <= canvas.size()) {
		for (int i = 0; i < puzzle.size(); ++i) {
			int row = (i / puzzleWidth) + ((canvasTileWidth - puzzleHeight) / 2);
			int col = (i % puzzleWidth) + ((canvasTileWidth - puzzleWidth) / 2);

			int index = (row * canvasTileWidth) + col;

			canvas[index] = puzzle[i];
		}
	}	
}

void draw_canvas(RenderTexture2D& texture, std::vector<u16>& canvas, int width, int x, int y, int tileSize) {
	BeginTextureMode(texture);
	for (int i = 0; i < canvas.size(); ++i) {
		int row = i / width;
		int col = i - (row * width);

		float xTileOffset = x + (col * tileSize);
		float yTileOffset = y + (row * tileSize);
		
		Rectangle tile = Rectangle{xTileOffset, yTileOffset, (float)tileSize, (float)tileSize};

		if (row + col & 1) DrawRectangleRec(tile, RAYWHITE);
		else DrawRectangleRec(tile, LIGHTGRAY);

		u16 canvasTile 	= canvas[i];
		u8 tileByte 	= canvasTile;
		u8 entityByte 	= canvasTile >> 8;

		if (tileByte != 0xff) DrawTextureEx(editor_tiles[tileByte], Vector2{xTileOffset, yTileOffset}, (float)0, (float)4, RAYWHITE);
		if (entityByte != 0xff) DrawTextureEx(editor_entities[entityByte], Vector2{xTileOffset, yTileOffset}, (float)0, (float)4, RAYWHITE);
	}
	EndTextureMode();
}

void draw_palette(std::vector<Texture2D>& palette, int width, int x, int y, int tileSize) {
	for (int i = 0; i < palette.size(); ++i) {
		int row = i / width;
		int col = i - (row * width);

		float xTileOffset = x + (col * tileSize);
		float yTileOffset = y + (row * tileSize);

		Rectangle tile = Rectangle{xTileOffset, yTileOffset, (float)tileSize, (float)tileSize};
		DrawRectangleRec(tile, BLACK);
		DrawTextureEx(palette[i], Vector2{xTileOffset, yTileOffset}, (float)0, (float)4, RAYWHITE);
	}	
}