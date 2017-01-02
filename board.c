#include <stdio>
#include "board.h"

/**
 * in a 9x9 sudoku board, the boxes will be arranged like this:
 *  --- --- ---
 * | 0 | 1 | 2 |
 *  --- --- ---
 * | 3 | 4 | 5 |
 *  --- --- ---
 * | 6 | 7 | 8 |
 *  --- --- ---
 * Each box would be a 3x3 set of entries.
 */

#define BOX_NUMBER(r,c) ((box_count) * ((r) / (box_count)) + ((c) / (box_count)))
#define BOX_START_ROW(box_num) ((box_num) - ((box_num) % (box_count))
#define BOX_START_COL(box_num) (((box_num) % (box_count)) * (box_count))

#define COLUMN_START_ENTRY(r,c) (board[0][(c)])
#define ROW_START_ENTRY(r,c) (board[(r)][0])

entry_t *get_next_box_entry(int r, int c);
void update_possible_values_row(int r, int c, int value);
void update_possible_values_col(int r, int c, int value);
void update_possible_values_box(int r, int c, int value);

static int box_count;

int init_board(int size)
{
	//validate size. If int(sqrt(size))^2 == size, then it's a square number.
	int box_count_temp = (int)sqrt(size);
	if (box_count_temp * box_count_temp != size)
	{
		//size is not a square number.
		return 1;
	}
	else
	{
		board_size = size;
		box_count = box_count_temp;

		//allocate the board
		board = (entry_t***)malloc(sizeof(entry_t**) * board_size);

		//initialize each row.
		for (int i = 0; i < board_size; i++)
		{
			board[i] = (entry_t**)malloc(sizeof(entry_t*) * board_size);
			//initialize each entry in each row.
			for (int j = 0; j < board_size; j++)
			{
				board[i][j] = init_entry();
			}
		}

		//set each entry_t's next pointers
		for (int r = 0; r < board_size; r++)
		{
			for (int c = 0; c < board_size; c++)
			{
				entry_t* curr_entry = board[r][c];

				//set this equal to entry at (r+1, c) or NULL.
				curr_entry->next_col = (r < board_size - 1) ? board[r + 1][c] : NULL;

				//set this equal to entry at (r, c+1) or NULL
				curr_entry->next_row = (c < board_size - 1) ? board[r][c + 1] : NULL;

				//set this equal to the next entry within (r,c)'s box
				curr_entry->next_box = get_next_box_entry(r, c);
			}
		}
	return 0;
	}
}


void free_board()
{
	for (int r = 0; r < board_size; r++)
	{
		for (int c = 0; c < board_size; c++)
		{
			free_entry(board[r][c]);
		}
		free(board[r]);
	}
	free(board);
	board = NULL;
}

void set_board_value(int r, int c, int value)
{
	set_entry_value(board[r][c], value);
	update_possible_values_row(r, c, value);
	update_possible_values_col(r, c, value);
	update_possible_values_box(r, c, value);
}

void update_possible_values_row(int r, int c, int value)
{
	entry_t *skip = board[r][c];
	entry_t *runner = ROW_START_ENTRY(r,c);
	while(runner)
	{
		if (runner != skip)
		{
			remove_possible_entry_value(runner, value);
		}
		runner = runner->next_row;
	}
}

void update_possible_values_col(int r, int c, int value)
{
	entry_t *skip = board[r][c];
	entry_t *runner = COLUMN_START_ENTRY(r,c);
	while (runner)
	{
		if (runner != skip)
		{
			remove_possible_entry_value(runner, value);
		}
		runner = runner->next_col;
	}
}

void update_possible_values_box(int r, int c, int value)
{
	entry_t *skip = board[r][c];
	int box_num = BOX_NUMBER(r,c);
	entry_t *runner = board[BOX_START_ROW(box_num)][BOX_START_COL(box_num)];
	while (runner)
	{
		if (runner != skip)
		{
			remove_possible_entry_value(runner, value);
		}
		runner = runner->next_box;
	}
}


entry_t *get_next_box_entry(int r, int c)
{
	int result_row;
	int result_col;
	int box_num = BOX_NUMBER(r,c);

	int row_index = (r - BOX_START_ROW(box_num)) //value between 0 and box_count - 1 inclusive
	int col_index = (c - BOX_START_COL(box_num)) //value between 0 and box_count - 1 inclusive

	if (row_index + 1 == box_count && col_index + 1 == box_count) {
		return NULL;
	} else {
		result_row = row_index + (col_index + 1 == box_count); //increment row_index if at the right end of the box
		result_col = (col_index + 1) % box_count;
		return board[result_row][result_col];
	}
}