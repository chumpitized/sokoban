#include "data.h"

GameMode gameMode = GameMode::Play;

int spriteSize 		= 16;
int screenWidth		= 1920;
int screenHeight 	= 1088;
int yPadding 		= (screenHeight % spriteSize) / 2;
int xPadding		= (screenWidth % spriteSize) / 2;

//int puzzleIndex = 0;