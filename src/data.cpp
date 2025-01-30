#include "data.h"

Mode mode = Mode::Play;

const int spriteSize 	= 16;
const int screenWidth	= 1920;
const int screenHeight 	= 1088;
const int yPadding 		= (screenHeight % spriteSize) / 2;
const int xPadding		= (screenWidth % spriteSize) / 2;