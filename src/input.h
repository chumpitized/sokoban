#ifndef INPUT_H
#define INPUT_H

#include "puzzles.h"
#include <raylib.h>

void create_new_puzzle();
void try_save(std::vector<u16>& puzzle, int index, bool valid_save);

void move(PuzzleInfo& puzzleInfo, std::vector<u16>& puzzle);
void go_next_puzzle(RenderTexture2D& game_texture);
void go_prev_puzzle(RenderTexture2D& game_texture);
void undo();
void restart();

void switch_to_play_mode(RenderTexture2D& game_texture);
void switch_to_edit_mode(std::vector<u16>& current_edit_puzzle, int edit_puzzle_width, int edit_puzzle_height);
void switch_to_level_menu();

#endif