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

extern const int spriteSize; 
extern const int screenWidth;
extern const int screenHeight;
extern const int yPadding;
extern const int xPadding;

#endif