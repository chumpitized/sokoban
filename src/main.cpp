#include <vector>
#include <iostream>
#include <cstdint>
#include <raylib.h>

int main() {
	//must always respect sprite dimensions
	int windowX = 1920;
	int windowY = 1088;

	int tileSize = 64;

	//replace with Images for sprites
	//will need to add handling to scale sprites according to screen size
	std::vector<Color> tileColors {
		PINK,
		PURPLE,
		RED,
		RAYWHITE,
		GREEN,
		BLUE,
		DARKBROWN
	};

	std::vector<int> first{
		4,5,3,3,4,
		4,1,1,1,4,
		4,1,3,1,4,
		4,1,1,1,4,
		3,3,3,3,3
	};

	SetTargetFPS(60);
	InitWindow(windowX, windowY, "Sokoban!");

	while(!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(BLACK);

		//Draw everything in a grid
		for (int i = 0; i < first.size(); ++i) {
			int xOffset = (i % 5);
			int yOffset = (i) / 5;

			std::cout << "X OFFSET: " << xOffset << " || Y OFFSET: " << yOffset << std::endl;

			DrawRectangle(xOffset * tileSize, yOffset * tileSize, tileSize, tileSize, tileColors[first[i]]);
		}

		EndDrawing();
	}

	CloseWindow();	

	return 1;
}