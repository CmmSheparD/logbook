#include "logbook.h"

#include <stdbool.h>
#include <stdlib.h>

#define EDA_INIT_SIZE 10

int _eda_reallocInnerArray(struct _Entry_DA *arr, size_t delta)
{
	if (!arr) return -1;
	arr->max += delta == 0 ? EDA_INIT_SIZE :
		(delta / EDA_INIT_SIZE + !(delta % EDA_INIT_SIZE == 0))
		* EDA_INIT_SIZE;
	arr->array = realloc(arr->array, arr->max * sizeof(*arr->array));
	return 0;
}

struct _Entry_DA *eda_createArray()
{
	struct _Entry_DA *arr = malloc(sizeof(*arr));
	arr->size = 0;
	arr->max = EDA_INIT_SIZE;
	arr->array = calloc(arr->max, sizeof(*arr->array));
	return arr;
}

void eda_freeArray(struct _Entry_DA *arr)
{
	if (arr) {
		if (arr->array) {
			for (size_t i = 0; i < arr->size; ++i) {
				if (arr->array[i])
					free(arr->array[i]);
			}
			free(arr->array);
		}
		free(arr);
	}
}

bool eda_isEmpty(const struct _Entry_DA *arr)
{
	if (arr->size == 0)
		return true;
	else
		return false;
}

int eda_appendEntry(struct _Entry_DA *arr, Entry_t *entry)
{
	if (!arr || !entry) return -1;
	if (arr->size >= arr->max)
		_eda_reallocInnerArray(arr, 0);
	arr->array[arr->size++] = entry;
	return 0;
}


Logbook_t *lb_createLogbook()
{
	Logbook_t *lb = malloc(sizeof(*lb));
	lb->title = wide_create();
	lb->entries = eda_createArray();
	return lb;
}

void lb_freeLogbook(Logbook_t *lb)
{
	if (lb) {
		if (lb->title)
			wide_free(lb->title);
		if (lb->entries)
			eda_freeArray(lb->entries);
		free(lb);
	}
}

bool lb_isEmpty(const Logbook_t *lb)
{
	return eda_isEmpty(lb->entries);
}

int lb_countEntries(const Logbook_t *lb)
{
	if (!lb)
		return -1;
	else if (!lb->entries)
		return 0;
	return lb->entries->size;
}

int lb_appendEntry(const Logbook_t *lb, Entry_t *entry)
{
	if (!lb || !lb->entries || !entry) return -1;
	eda_appendEntry(lb->entries, entry);
	return 0;
}

Entry_t *lb_getEntry(const Logbook_t *lb, size_t ind)
{
	if (!lb || !lb->entries || ind >= lb->entries->size) return NULL;
	return lb->entries->array[ind];
}

Entry_t *lb_getLastEntry(const Logbook_t *lb)
{
	if (!lb || !lb->entries || lb->entries->size == 0) return NULL;
	return lb->entries->array[lb->entries->size - 1];
}
