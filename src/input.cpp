#include "input.h"
#include "puzzles.h"
#include "draw.h"

#include <vector>
#include <iostream>

////////////
//  Play  //
////////////

void create_new_puzzle() {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_N)) {
		std::cout << "creating new puzzle" << std::endl;
		create_new_puzzle_and_update_vals();
	}
}

void move(std::vector<u16>& puzzle) {
	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D)) {
		//this will double count a position when you push into a wall
		//and no elements move

		int player_index = get_current_puzzle_player_index();

		//pushing to history should be api call...
		if (history.empty() || history.back() != puzzle) history.push_back(puzzle);		
		int input 					= GetKeyPressed();
		int newPos 					= try_move(input, player_index);
		//puzzle[puzzle.size() - 2] 	= (u16)newPos;
		//puzzleInfo.playerIndex 		= newPos;
	}
}

void go_next_puzzle(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_EQUAL)) {
		if (try_increment_puzzle()) {
			history.clear();
			clear_background(game_texture);
		}
	}
}

void go_prev_puzzle(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_MINUS)) {
		if (try_decrement_puzzle()) {
			history.clear();
			clear_background(game_texture);
		}
	}
}

void undo() {
	if (IsKeyPressed(KEY_Z)) {
		//can undo on hold...
		undo_last_move();
	}	
}

void restart() {
	if (IsKeyPressed(KEY_R)) {
		restart_level();
		history.clear();
	}
}

void switch_to_play_mode(RenderTexture2D& game_texture) {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Play;
		clear_background(game_texture);
		restart_level();
		history.clear();
	}
}

void switch_to_edit_mode(int edit_puzzle_width, int edit_puzzle_height) {
	if (IsKeyPressed(KEY_E)) {
		mode = Mode::Edit;
		
		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}

		restart_level();
		history.clear();

		std::vector<u16> current_puzzle = get_current_puzzle();

		//this can actually be done once when we select a puzzle,
		// then we can just display the canvas on mode switch...
		load_puzzle_into_canvas(canvas, current_puzzle, edit_puzzle_width, edit_puzzle_height);
	}

}

void switch_to_level_menu() {
	if (IsKeyPressed(KEY_L)) {
		mode = Mode::Level_Menu;
		
		std::vector<std::vector<u16>> puzzles = get_puzzles();

		reload_puzzle_previews(puzzles);
	}
}

////////////
// Editor //
////////////

std::vector<std::vector<u16>> editor_history;

void try_save(std::vector<u16>& puzzle, int index, bool valid_save) {
	if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S) && valid_save) {
		std::cout << "trying to save!" << std::endl;
		overwrite_puzzle_in_puzzles(puzzle, index);
		save_puzzles_to_file();
	}
}

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