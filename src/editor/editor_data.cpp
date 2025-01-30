#include "editor_data.h"

#include <vector>

//Draw
StoredTile storedTile = StoredTile(false, 0);

//Canvas
float tileSize		= 64;
float canvasWidth	= 1024;
float canvasHeight 	= 1024;
float xOffset 		= 25;
float yOffset 		= 20;
int canvasTileWidth = canvasWidth / tileSize;

//Fonts
int fontSize		= 35;

//Palettes
int paletteWidth 	= 3;
int paletteWidthP	= 3 * tileSize;

//Entities
int xEntitiesFont	= xOffset + canvasWidth + 25;
int yEntitiesFont	= yOffset;
int xEntitiesOffset = xEntitiesFont;
int yEntitiesOffset = yEntitiesFont + fontSize + 10;

//Tiles
int xTilesFont		= xOffset + canvasWidth + 25;
int yTilesFont		= yOffset + 300;
int xTilesOffset	= xTilesFont;
int yTilesOffset	= yTilesFont + fontSize + 10;

//Arrays
std::vector<Texture2D> editor_entities;
std::vector<Texture2D> editor_tiles;
std::vector<u16> canvas(canvasTileWidth * canvasTileWidth, 0xffff);