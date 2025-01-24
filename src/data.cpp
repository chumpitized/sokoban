#include "data.h"

GameMode gameMode = GameMode::Play;

//we need to make sure we offset the art by the right amount
//in order to make things pixel-perfect
int spriteSize 		= 16;
int screenWidth		= 1920;
int screenHeight 	= 1088;
int yPadding 		= (screenHeight % spriteSize) / 2;
int xPadding		= (screenWidth % spriteSize) / 2;

int puzzleIndex = 0;