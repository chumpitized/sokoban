#ifndef EDITOR_DATA_H
#define EDITOR_DATA_H

#include <cstdint>
#include <raylib.h>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;

struct StoredTile {
	bool isEntity;
	u8 storedIndex;

	StoredTile(bool isEntity, u8 storedIndex) {
		this->isEntity 		= isEntity;
		this->storedIndex 	= storedIndex;
	}
};

//Draw
extern StoredTile storedTile;

//Window
//extern int screenWidth;
//extern int screenHeight;

//Canvas
extern float tileSize;
extern float canvasWidth;
extern float canvasHeight;
extern float xOffset;
extern float yOffset;
extern int canvasTileWidth;

//Palettes
extern int paletteWidthP;
extern int paletteWidth;

//Font
extern int fontSize;

//Entities
extern int xEntitiesFont;
extern int yEntitiesFont;
extern int xEntitiesOffset;
extern int yEntitiesOffset;

//Tiles
extern int xTilesFont;
extern int yTilesFont;
extern int xTilesOffset;
extern int yTilesOffset;

//Arrays
extern std::vector<Texture2D> editor_entities;
extern std::vector<Texture2D> editor_tiles;
extern std::vector<u16> canvas;

#endif