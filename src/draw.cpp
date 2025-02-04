#include "draw.h"
#include "data.h"
#include "puzzles.h"

#include <iostream>

//////////
// Play //
//////////

std::vector<Texture2D> entities;
std::vector<Texture2D> tiles;

int get_sprite_scale() {
	return (screenHeight / get_current_puzzle_height()) / spriteSize;
}
int get_tile_size() {
	return get_sprite_scale() * spriteSize;
}

RenderTexture2D create_texture(int screenWidth, int screenHeight) {
	RenderTexture2D texture = LoadRenderTexture(screenWidth, screenHeight);
	BeginTextureMode(texture);
	ClearBackground(BLACK);
	EndTextureMode();
	return texture;
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

	std::vector<u16> puzzle = get_current_puzzle(); 

	int puzzle_size 	= puzzle.size();
	u8 puzzle_width 	= get_current_puzzle_width();
	u8 puzzle_height 	= get_current_puzzle_height();
	u8 player_index		= get_current_puzzle_player_index();

	BeginTextureMode(texture);
	for (int i = 0; i < puzzle_size - 3; ++i) {

		int tile_x_offset 	= i % puzzle_width;
		int tile_y_offset 	= i / puzzle_width;

		int window_x_offset = get_puzzle_draw_offset(tileSize, puzzle_width, screenWidth);
		int window_y_offset = get_puzzle_draw_offset(tileSize, puzzle_height, screenHeight);

		u8 entity 	= puzzle[i] >> 8;
		u8 tile 	= puzzle[i]; 
		
		Texture2D tile_texture;
		Texture2D entity_texture;

		if (tile < tiles.size() && tile >= 0) {
			tile_texture = tiles[tile];
			DrawTextureEx(tile_texture, Vector2{(float)(tile_x_offset * tileSize) + window_x_offset, (float)(tile_y_offset * tileSize) + window_y_offset}, 0.0, spriteScale, RAYWHITE);
		}
		if (entity < entities.size() && entity >= 0) {
			entity_texture = entities[entity];
			DrawTextureEx(entity_texture, Vector2{(float)(tile_x_offset * tileSize) + window_x_offset, (float)(tile_y_offset * tileSize) + window_y_offset}, 0.0, spriteScale, RAYWHITE);
		}
	}

	EndTextureMode();
};

////////////
// Editor //
////////////

std::vector<Texture2D> editor_entities;
std::vector<Texture2D> editor_tiles;

void draw_save_status(bool save_status) {
	if (save_status) {
		DrawText("Saved!", xTilesOffset, yTilesOffset + 200, fontSize, GREEN);
	} else {
		DrawText("Unsaved", xTilesOffset, yTilesOffset + 200, fontSize, RED);
	}
}

RenderTexture2D draw_menu_setup(int screenWidth, int screenHeight) {
	RenderTexture2D texture = LoadRenderTexture(screenWidth, screenHeight);
	
	BeginTextureMode(texture);
	ClearBackground(BLACK);
	EndTextureMode();

	return texture;
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
		for (int i = 0; i < puzzle.size() - 3; ++i) {
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

//////////////////
//  Level Menu  //
//////////////////

std::vector<RenderTexture2D> puzzle_previews;

std::vector<RenderTexture2D> get_puzzle_previews() {
	return puzzle_previews;
}

void draw_move_puzzle_overlay(int hover_index, bool left) {
	float y = hover_index / 12;
	float x = hover_index % 12;

	if (left) {
		DrawRectangleRec((Rectangle){x * 160, y * 160, (float)80, (float)160}, GREEN);
	} else {
		DrawRectangleRec((Rectangle){(x * 160) + 80, y * 160, (float)80, (float)160}, GREEN);
	}
}

void draw_selected_puzzle_outline(int selected_index) {
	float y = selected_index / 12;
	float x = selected_index % 12;

	DrawRectangleLinesEx((Rectangle){x * 160, y * 160, (float)160, (float)160}, 6.0, RED);
}

RenderTexture2D load_puzzle_preview(std::vector<u16> puzzle) {
	u8 texture_width 	= 160;
	u8 texture_height 	= 160;

	RenderTexture2D texture = LoadRenderTexture(texture_width, texture_height);
	
	BeginTextureMode(texture);
		ClearBackground(BLACK);
		draw_puzzle_to_preview_texture(texture, texture_width, texture_height, puzzle);
	EndTextureMode();
	
	return texture;
}

std::vector<RenderTexture2D> reload_puzzle_previews(std::vector<std::vector<u16>> puzzles) {
	for (auto preview : puzzle_previews) {
		UnloadRenderTexture(preview);
	}
	puzzle_previews.clear();

	for (auto puzzle : puzzles) {
		puzzle_previews.push_back(load_puzzle_preview(puzzle));
	}

	return puzzle_previews;
}

void draw_puzzle_to_preview_texture(RenderTexture2D& texture, int texture_width, int texture_height, std::vector<u16> puzzle) {
	int puzzle_size 	= puzzle.size();
	u8 puzzle_width 	= puzzle[puzzle_size - 3] >> 8;
	u8 puzzle_height 	= puzzle[puzzle_size - 3];

	int spriteScale = (texture_height / puzzle_height) / spriteSize;
	int tileSize	= spriteScale * spriteSize;

	BeginTextureMode(texture);
	for (int i = 0; i < puzzle_size - 3; ++i) {

		int tile_x_offset 	= i % puzzle_width;
		int tile_y_offset 	= i / puzzle_width;

		int window_x_offset = get_puzzle_draw_offset(tileSize, puzzle_width, texture_width);
		int window_y_offset = get_puzzle_draw_offset(tileSize, puzzle_height, texture_height);

		u8 entity 	= puzzle[i] >> 8;
		u8 tile 	= puzzle[i]; 
		
		Texture2D tile_texture;
		Texture2D entity_texture;

		if (tile < tiles.size() && tile >= 0) {
			tile_texture = tiles[tile];
			DrawTextureEx(tile_texture, Vector2{(float)(tile_x_offset * tileSize) + window_x_offset, (float)(tile_y_offset * tileSize) + window_y_offset}, 0.0, spriteScale, RAYWHITE);
		}
		if (entity < entities.size() && entity >= 0) {
			entity_texture = entities[entity];
			DrawTextureEx(entity_texture, Vector2{(float)(tile_x_offset * tileSize) + window_x_offset, (float)(tile_y_offset * tileSize) + window_y_offset}, 0.0, spriteScale, RAYWHITE);
		}
	}

	EndTextureMode();
};

/////////////////
//  Main Menu  //
/////////////////

RenderTexture2D draw_main_menu_setup(int screenWidth, int screenHeight) {
	RenderTexture2D texture = LoadRenderTexture(screenWidth, screenHeight);
		BeginTextureMode(texture);
		ClearBackground(BLACK);
		EndTextureMode();
	return texture;
}

void draw_game_title(RenderTexture2D& texture) {
	int x = texture.texture.width;
	int y = texture.texture.height;

	int font_size = 130;
	int textWidth = MeasureText("So-key-ban!", font_size);

	
	BeginTextureMode(texture);
		DrawText("So-key-ban!", (x / 2) - (textWidth / 2), y / 10, font_size, WHITE);
	EndTextureMode();
}

void draw_main_menu_buttons(RenderTexture2D& texture) {
	int x = texture.texture.width;
	int y = texture.texture.height;

	int y_offset = y / 20;
	int x_offset = (x / 2);

	int font_size = 80;

	int play_width = MeasureText("Play", font_size);
	int edit_width = MeasureText("Editor", font_size);
	int menu_width = MeasureText("Level Menu", font_size);

	BeginTextureMode(texture);
	DrawRectangle(x_offset - 300, y_offset * 7, 600, 100, ORANGE);
		DrawText("Play", x_offset - (play_width / 2), y_offset * 7 + (100 - font_size) / 2, font_size, BLACK); 

		DrawRectangle(x_offset - 300, y_offset * 10, 600, 100, ORANGE);
		DrawText("Editor", x_offset - (edit_width / 2), y_offset * 10 + (100 - font_size) / 2, font_size, BLACK);

		DrawRectangle(x_offset - 300,  y_offset * 13, 600, 100, ORANGE);
		DrawText("Level Menu", x_offset - (menu_width / 2), y_offset * 13 + (100 - font_size) / 2, font_size, BLACK);
	EndTextureMode();
}
