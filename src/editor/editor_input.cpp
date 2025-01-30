#include "editor_input.h"
#include "editor_data.h"
#include "editor_draw.h"

#include <raylib.h>
#include <vector>
#include <iostream>

std::vector<std::vector<u16>> editor_history;

void editor_undo() {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
		if (!editor_history.empty()) {
			canvas = editor_history.back();
			editor_history.pop_back();
		}
	}
}

void reset_canvas() {
	if (IsKeyPressed(KEY_R)) {
		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}
		editor_history.clear();
	}
}

void handle_mouse_hover() {
	Vector2 mousePos = GetMousePosition();
	int index = in_canvas(mousePos);

	if (index < 0) return; 

	float y = ((index / canvasTileWidth) * tileSize) + yOffset;
	float x = ((index % canvasTileWidth) * tileSize) + xOffset;

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		DrawRectangleLinesEx(Rectangle{x, y, tileSize, tileSize}, 6, RED);
	} else {
		if (storedTile.storedIndex >= 0) {
			if (storedTile.isEntity) {
				DrawTextureEx(editor_entities[storedTile.storedIndex], Vector2{x,y}, 0, 4.0, RAYWHITE);
			} else {
				DrawTextureEx(editor_tiles[storedTile.storedIndex], Vector2{x,y}, 0, 4.0, RAYWHITE);
			}
		}
	}
}

void handle_right_mouse_click() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Vector2 mousePos = GetMousePosition();
		
		int index = in_canvas(mousePos);
		if (index >= 0) {
			editor_history.push_back(canvas);
		}
	}
}

void handle_right_mouse_held() {
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 mousePos = GetMousePosition();

		int index = in_canvas(mousePos);
		if (index >= 0) {
			canvas[index] = 0xffff;
			return;
		}	
	}
}

void handle_left_mouse_click() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		int index = in_canvas(mousePos);
		if (index >= 0) {
			editor_history.push_back(canvas);
			return;
		}

		//Entities
		index = in_palette(editor_entities, xEntitiesOffset, yEntitiesOffset, mousePos);
		if (index >= 0) {
			storedTile.storedIndex 	= index;
			storedTile.isEntity 	= true;
			return;
		}

		//Tiles
		index = in_palette(editor_tiles, xTilesOffset, yTilesOffset, mousePos);
		if (index >= 0) {
			storedTile.storedIndex 	= index;
			storedTile.isEntity		= false;
		}
	}
}

//bool is_puzzle_valid(std::vector<u16>& canvas) {
//	u8 expected_width	= 0;
//	u8 row_width		= 0;
//	u8 potential_gap 	= 0;

//	u8 players			= 0;
//	u8 keys				= 0;
//	u8 locks			= 0;

//	for (int i = 0; i < canvasTileWidth; ++i) {
//		row_width		= 0;
//		potential_gap 	= 0;

//		for (int j = 0; j < canvasTileWidth; ++j) {
//			u8 index 	= (i * canvasTileWidth) + j;
//			u16 value	= canvas[index];

//			u8 high 	= value >> 8;
//			u8 low 		= value;

//			if (high == 0x0) players++;
//			if (high == 0x1) keys++;
//			if (low == 0x04) locks++;

//			if (canvas[index] != 0xffff && potential_gap > 0) return false;
//			if (canvas[index] != 0xffff) row_width++;
//			if (row_width > 0 && low == 0xff) potential_gap++;
//		}

//		if (expected_width == 0) expected_width = row_width;
//		//have to handle empty rows by checking that row_width is greater than 0
//		if (row_width > 0 && row_width != expected_width) return false;
//	}

//	if (players != 1 || keys < locks) return false;

//	std::cout << "GOOD" << std::endl;

//	return true;
//}

//u8 get_puzzle_width(std::vector<u16>& canvas) {
//	int width = 0;
	
//	for (auto cell : canvas) {
//		if (width > 0 && cell == 0xffff) return width;
//		if (cell != 0xffff) width++;
//	}

//	return width;
//}

//std::vector<u16> get_edited_puzzle(std::vector<u16>& canvas) {
//	if (!is_puzzle_valid(canvas)) return {};

//	u8 width = get_puzzle_width(canvas);

//	std::vector<u16> trimmed_canvas;
	
//	for (auto cell : canvas) {
//		if (cell != 0xffff) trimmed_canvas.push_back(cell);
//	}
	
//	u8 height = trimmed_canvas.size() / width;	
//	u16 dimensions = width << 8 | height;
	
//	//gotta add handling for this...
//	//trimmed_canvas.push_back(dimensions);
//	//trimmed_canvas.push_back(0xffff);

//	return trimmed_canvas;
//}

void handle_left_mouse_held() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		//Canvas
		int index = in_canvas(mousePos);
		if (index >= 0) {
			u16 replacement;
			if (storedTile.isEntity) {
				u16 cell	= canvas[index];
				u16 mask 	= 0x00ff; 
				u16 masked 	= cell & mask;
				replacement	= storedTile.storedIndex << 8 | masked;
			} else {
				u16 cell	= canvas[index];
				u16 mask 	= 0xff00;
				u16 masked	= cell & mask;
				replacement = masked | storedTile.storedIndex;
			}

			canvas[index] = replacement;
		}
	}
}

void handle_left_mouse_release() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		std::cout << "released left mouse button..." << std::endl;
	}
}

int in_canvas(Vector2 mousePos) {
	int x = mousePos.x - xOffset;
	int y = mousePos.y - yOffset;

	if (x >= 0 && x < canvasWidth && y >= 0 && y < canvasHeight) {
		int xTile = x / tileSize;
		int yTile = y / tileSize;

		return (yTile * canvasTileWidth) + xTile;
	}
	return -1;
}

int in_palette(std::vector<Texture2D>& palette, int xOffset, int yOffset, Vector2 mousePos) {
	int x 				= mousePos.x - xOffset;
	int y 				= mousePos.y - yOffset;
	int fullRows 		= palette.size() / 3;
	int fullRowHeight 	= fullRows * tileSize;

	if (fullRowHeight > 0 && x >= 0 && x < paletteWidthP && y >= 0 && y < fullRowHeight) {
		int xTile = x / tileSize;
		int yTile = y / tileSize;

		return (yTile * paletteWidth) + xTile;
	}

	int partialRow 			= palette.size() % 3;
	int partialRowLength 	= partialRow * tileSize;

	y = y - fullRowHeight;

	if (x >= 0 && x < partialRowLength && y >= 0 && y < tileSize) {
		return (fullRows * paletteWidth) + (x / tileSize);
	}
	return -1;
}