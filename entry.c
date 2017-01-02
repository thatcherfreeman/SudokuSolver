#include "entry.h"

void set_entry_value(entry_t *entry, int value)
{
	//zero out all the possible values other than the given value.
	int *possible_values = entry->possible_values;
	for (int i = 0; i < board_size; i++)
	{
		//should be slightly faster when compiler uses DMA for this operation.
		possible_values[i] = 0;
	}
	possible_values[value] = 1;

	//set set_value to be equal to the value
	entry->set_value = value;

	//set remaining_value_count equal to 1.
	entry->remaining_value_count = 1;
}



int remove_possible_entry_value(entry_t *entry, int value)
{
	//if the value is already zeroed out in entry, then do not decrement the
	//remaining_value_count.
	entry->remaining_value_count -= entry->possible_values[value];
	entry->possible_values[value] = 0;
	return entry->remaining_value_count;
}

entry_t *init_entry()
{
	entry_t* entry = (entry_t*)calloc(sizeof(entry_t), 1);
	//instead use the function that allocates them all as 1s.
	int* possible_values = (int*)calloc(sizeof(int), board_size);
	entry->possible_values = possible_values;
	entry->remaining_value_count = board_size;
	entry->set_value = board_size;
	return entry;
}

void free_entry(entry_t *entry)
{
	free(entry->possible_values);
	free(entry);
}