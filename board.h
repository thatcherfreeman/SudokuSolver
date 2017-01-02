#include <stdio.h>
#include "entry.h"

int board_size;	//needs to be a square number, like 9 on most sudoku boards.

entry_t ***board;

int init_board(int size);
void free_board();
void set_board_value(int r, int c, int value);