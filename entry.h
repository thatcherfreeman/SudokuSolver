#include <stdio.h>
#include "board.h"

typedef struct _entry_t
{
	_entry_t *next_col;		//pointer to the next entry in this entry's collumn
	_entry_t *next_row; 	//pointer to the next entry in this entry's row
	_entry_t *next_box; 	//pointer to the next entry in this entry's box.
	int* possible_values;	//Array size board_size with a 1 at index i if i
							//is still a potential value for this entry.
	int remaining_value_count;
	int set_value;

} entry_t;

void set_entry_value(entry_t *entry, int value);
int remove_possible_entry_value(entry_t *entry, int value);
entry_t *init_entry();
void free_entry(entry_t *entry);