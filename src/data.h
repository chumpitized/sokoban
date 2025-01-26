#ifndef DATA_H
#define DATA_H

#include <cstdint>
#include <raylib.h>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;

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

//extern int puzzleIndex;

#endif