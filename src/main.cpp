#include "sprites.h"

#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

int getOffset(int tileSize, int puzzleWidth, int windowSize) {
	return (windowSize - (tileSize * puzzleWidth)) / 2;
}

int main() {
	//must always respect sprite dimensions
	int screenWidth		= 1920;
	int screenHeight 	= 1088;

	//tileSize should scale with screenHeight
	int tileSize 		= 192;

	SetTargetFPS(60);

	InitWindow(screenWidth, screenHeight, "Sokoban!");
	load_sprites();

	RenderTexture2D game = LoadRenderTexture(screenWidth, screenHeight);
		BeginTextureMode(game);
		ClearBackground(BLACK);
	EndTextureMode();

	std::vector<int> first{
		4,3,3,3,4,
		4,1,2,5,4,
		4,0,3,6,4,
		4,1,2,1,4,
		3,3,3,3,3
	};

	while(!WindowShouldClose()) {

		//Draw game screen to Texture2D
		BeginTextureMode(game);
			for (int i = 0; i < first.size(); ++i) { 
				int xOffset = (i % 5);
				int yOffset = (i) / 5;

				int windowXOffset = getOffset(tileSize, 5, screenWidth);
				int windowYOffset = getOffset(tileSize, 5, screenHeight);

				//Draw texture with extended parameters (scale, rotation, etc.)
				DrawTextureEx(sprites[first[i]], Vector2{(float)(xOffset * tileSize) + windowXOffset, (float)(yOffset * tileSize) + windowYOffset}, 0.0, 12.0, RAYWHITE); 
			}
		EndTextureMode();


		//Draw to window
		BeginDrawing();
			DrawTextureRec(game.texture, (Rectangle){0, 0, (float)game.texture.width, -(float)game.texture.height}, (Vector2){0, 0}, RAYWHITE);
		EndDrawing();

	}

	CloseWindow();	

	return 1;
}