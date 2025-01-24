#ifndef DATA_H
#define DATA_H

#include <raylib.h>
#include <vector>

enum GameMode {
	Play,
	Editor
};

extern GameMode gameMode;

extern int spriteSize; 
extern int screenWidth;
extern int screenHeight;
extern int yPadding;
extern int xPadding;

extern int puzzleIndex;

#endif