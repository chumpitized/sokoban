#ifndef INPUT_H
#define INPUT_H

#include "puzzles.h"
#include <raylib.h>

////////////
//  Play  //
////////////

void create_new_puzzle();
void try_save(std::vector<u16>& puzzle, int index, bool valid_save);

void move(std::vector<u16>& puzzle);
void go_next_puzzle(RenderTexture2D& game_texture);
void go_prev_puzzle(RenderTexture2D& game_texture);
void undo();
void restart();

void switch_to_play_mode(RenderTexture2D& game_texture);
void switch_to_edit_mode(std::vector<u16>& current_edit_puzzle, int edit_puzzle_width, int edit_puzzle_height);
void switch_to_level_menu();

////////////
// Editor //
////////////

extern std::vector<std::vector<u16>> editor_history;

void editor_undo();
void reset_canvas();

void handle_mouse_hover();
void handle_left_mouse_click();
void handle_left_mouse_held();
void handle_left_mouse_release();

void handle_right_mouse_click();
void handle_right_mouse_held();

int in_canvas(Vector2 mousePos);
int in_palette(std::vector<Texture2D>& palette, int xOffset, int yOffset, Vector2 mousePos);

#endif