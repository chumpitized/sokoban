#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

Texture2D load_sprites(const char* path) {
	Image image = LoadImage(path);
	Texture2D texture = LoadTextureFromImage(image);
	UnloadImage(image);
	return texture;
};

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

	RenderTexture2D game = LoadRenderTexture(screenWidth, screenHeight);
		BeginTextureMode(game);
		ClearBackground(BLACK);
	EndTextureMode();

	std::vector<int> first{
		4,5,3,3,4,
		4,1,1,1,4,
		4,1,3,1,4,
		4,1,1,1,4,
		3,3,3,3,3
	};

	Texture2D texture = load_sprites("data/sprites/wall_horizontal.png");

	while(!WindowShouldClose()) {

		//Draw game screen to Texture2D
		BeginTextureMode(game);
			for (int i = 0; i < first.size(); ++i) { 
				int xOffset = (i % 5);
				int yOffset = (i) / 5;

				int windowXOffset = getOffset(tileSize, 5, screenWidth);
				int windowYOffset = getOffset(tileSize, 5, screenHeight);

				//Texture2D texture = load_sprites("data/sprites/wall.png");

				//Draw texture with extended parameters (scale, rotation, etc.)
				DrawTextureEx(texture, Vector2{(float)(xOffset * tileSize) + windowXOffset, (float)(yOffset * tileSize) + windowYOffset}, 0.0, 12.0, RAYWHITE); 
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