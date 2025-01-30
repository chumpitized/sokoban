#ifndef EDITOR_INPUT_H
#define EDITOR_INPUT_H

#include "editor_data.h"

#include <vector>
#include <raylib.h>

extern std::vector<std::vector<u16>> editor_history;

void editor_undo();
void reset_canvas();

bool is_puzzle_valid(std::vector<u16>& canvas);
u8 get_puzzle_width(std::vector<u16>& canvas);
std::vector<u16> get_edited_puzzle(std::vector<u16>& canvas, std::vector<u16>& current_edit_puzzle);

void handle_mouse_hover();
void handle_left_mouse_click();
void handle_left_mouse_held();
void handle_left_mouse_release();

void handle_right_mouse_click();
void handle_right_mouse_held();

int in_canvas(Vector2 mousePos);
int in_palette(std::vector<Texture2D>& palette, int xOffset, int yOffset, Vector2 mousePos);

#endif