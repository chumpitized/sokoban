#include "editor_input.h"
#include "editor_data.h"
#include "editor_undo.h"

#include <raylib.h>
#include <vector>
#include <iostream>

void editor_undo() {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
		if (!history.empty()) {
			canvas = history.back();
			history.pop_back();
		}
	}
}

void reset_canvas() {
	if (IsKeyPressed(KEY_R)) {
		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}
		history.clear();
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
			history.push_back(canvas);
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
			history.push_back(canvas);
		}

		//Entities
		index = in_palette(editor_entities, xEntitiesOffset, yEntitiesOffset, mousePos);
		if (index >= 0) {
			storedTile.storedIndex 	= index;
			storedTile.isEntity 	= true;
		}

		//Tiles
		index = in_palette(editor_tiles, xTilesOffset, yTilesOffset, mousePos);
		if (index >= 0) {
			storedTile.storedIndex 	= index;
			storedTile.isEntity		= false;
		}
	}
}

void handle_left_mouse_held() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		//Canvas
		int index = in_canvas(mousePos);
		if (index >= 0) {
			if (storedTile.isEntity) {
				u16 canvasTile 	= canvas[index];
				u16 mask 		= 0x00ff; 
				u16 masked 		= canvasTile & mask;
				u16 replacement	= storedTile.storedIndex << 8 | masked;
				
				canvas[index] = replacement;
			} else {
				u16 canvasTile 	= canvas[index];
				u16 mask 		= 0xff00;
				u16 masked		= canvas[index] & mask;
				u16 replacement = masked | storedTile.storedIndex;

				canvas[index] = replacement;
			}
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