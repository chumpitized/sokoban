#include "draw.h"
#include "input.h"
#include "data.h"
#include "save.h"

#include <raylib.h>

//SetWindowIcon to change... window icon
int main() {
	InitWindow(screenWidth, screenHeight, "Tilemap Editor");
	load_sprites(entities, tiles);
	RenderTexture2D texture = draw_setup(screenWidth, screenHeight);

	while (!WindowShouldClose()) {
		//Input
		handle_left_mouse_click();
		handle_left_mouse_held();
		handle_left_mouse_release();
		handle_right_mouse_click();
		handle_right_mouse_held();
		reset_canvas();
		undo();
		//Draw
		
		if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
			save();
		}

		//if we want, we can call this only when update...
		draw_canvas(texture, canvas, entities, tiles, canvasTileWidth, xOffset, yOffset, tileSize);

		BeginDrawing();
			DrawTextureRec(texture.texture, (Rectangle){0, 0, (float)texture.texture.width, -(float)texture.texture.height}, (Vector2){0, 0}, RAYWHITE);
			DrawFPS(0, 0);
			handle_mouse_hover();
			draw_selected_palette_tile();
		EndDrawing();
	}
}
