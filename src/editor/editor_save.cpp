#include "editor_save.h"
//#include "editor_data.h"
#include "editor_input.h"

#include <fstream>
#include <iostream>
#include <vector>

//draw error message when invalid...
void save(std::vector<u16>& canvas) {
	std::vector<u16> trimmedCanvas;
	u8 rowWidth 		= 0;
	u8 expectedWidth 	= 0;

	for (auto val : canvas) {
		if (val != 0xffff) {
			rowWidth++;
			trimmedCanvas.push_back(val);
		}
		
		if (val == 0xffff && rowWidth > 0) {
			//BUGGED!!! If you draw two disconnected 2x2 squares and save, it will work!
			//there must be canvasTileWidth cells between each row of filled cells!
			if (expectedWidth > 0 && rowWidth != expectedWidth) {
				std::cout << "SAVE FAILED" << std::endl;
				std::cout << "ERROR: PUZZLE IS NOT A RECTANGLE" << std::endl;
				return;
			}
			expectedWidth = rowWidth;
			rowWidth = 0;
		}
	}

	u8 height = (trimmedCanvas.size() / expectedWidth);
	u16 widthAndHeight = expectedWidth << 8 | height;
	trimmedCanvas.push_back(widthAndHeight);
	trimmedCanvas.push_back(0xffff);

	std::fstream file;
    file.open("save/new_puzzle", std::ios::app | std::ios::binary);
 
	//save puzzle to file
	if (file) {
		int length = (trimmedCanvas.size() * 2);
		u8 buffer[length];

		int bufferIndex = 0;
		for (int i = 0; i < trimmedCanvas.size(); ++i) {
			bufferIndex = i * 2;
			buffer[bufferIndex] 	= (u8)(trimmedCanvas[i] >> 8);
			buffer[bufferIndex + 1] = (u8)(trimmedCanvas[i]); 
		}
 
		std::cout << "buffer length: " << length << std::endl;
		for (auto num : buffer) {
			std::cout << "buffer contents: " << +num << std::endl;
		}

		file.write(reinterpret_cast<char*>(buffer), length);
		file.close();
	}

	std::cout << "~~~SAVING~~~" << std::endl;
	std::cout << "WIDTH: " << +expectedWidth << std::endl;
	std::cout << "HEIGHT: " << +height << std::endl;

	read();
}

void read() {
	std::fstream file;
    file.open("save/new_puzzle", std::ios::in | std::ios::binary);
 	std::vector<u16> puzzle;

	//save puzzle to file
	if (file) {
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);

		u8 buffer[length];
 
		file.read(reinterpret_cast<char*>(buffer), length);
		file.close();

		for (int i = 0; i < length; ++i) {
			std::cout << i << ": " << +buffer[i] << std::endl;
		}

		for (int i = 0; i < length; i+=2) {
			u16 left = buffer[i] << 8;
			u16 tile = left | buffer[i + 1];
			puzzle.push_back(tile);
			if (tile == 0xffff) break;
		}

		for (int i = 0; i < canvas.size(); ++i) {
			canvas[i] = 0xffff;
		}

		//ideally we would center the level...
		u8 width = puzzle[puzzle.size() - 2] >> 8;
		u8 height = buffer[puzzle.size() - 2];

		for (int i = 0; i < puzzle.size() - 2; ++i) {
			int row = i / width;
			int col = i % width;

			int index = (row * canvasTileWidth) + col;

			canvas[index] = puzzle[i];
		}

	}

}
