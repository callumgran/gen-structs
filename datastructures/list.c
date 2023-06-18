/*
 *  Copyright (C) 2022-2023 Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

bool list_init(struct list_t *list, const size_t item_size)
{
    if (list == NULL)
        return false;
    if (item_size == 0)
        return false;
    
	list->size = 0;
	list->capacity = LIST_STARTING_CAPACITY;
	list->items = (void **)(malloc(LIST_STARTING_CAPACITY * sizeof(void *)));
	list->item_size = item_size;

    return true;
}

void list_free(struct list_t *list)
{
	free(list->items);
}

bool list_empty(const struct list_t *list)
{
    if (list == NULL)
        return false;

	return !list->size;
}

size_t list_size(const struct list_t *list)
{
    if (list == NULL)
        return 0;

    return list->size;
}

size_t list_index_of(struct list_t *list, const void *item, equality_fn_t *eq)
{
    if (list == NULL || item == NULL)
        return ITEM_NOT_FOUND;

    for (long i = 0; i < list->size; i++) {
        if (eq(*(list->items + i), item))
            return i;
    }

    return ITEM_NOT_FOUND;
}

size_t list_index_of_r(struct list_t *list, const void *item, equality_fn_t *eq)
{
    if (list == NULL || item == NULL)
        return ITEM_NOT_FOUND;

    for (ssize_t i = list->size; i >= 0; --i) {
        if (eq(*(list->items + i), item))
            return i;
    }

    return ITEM_NOT_FOUND;
}

void list_append(struct list_t *list, const void *item)
{
    if (list == NULL || item == NULL)
        return;

	ENSURE_CAP(list->size, list->capacity, list->items);

	list->items[list->size++] = item;
}

inline void *list_get(struct list_t *list, const size_t idx)
{
    if (list == NULL)
        return NULL;

	if (idx >= list->size)
		return NULL;

	return list->items[idx];
}

bool list_remove(struct list_t *list, const size_t idx)
{
    if (list == NULL)
        return false;
    
	if (idx >= list->size)
		return false;

	for (size_t i = idx; i < list->size - 1; i++)
		list->items[i] = list->items[i + 1];

	--list->size;

	REDUCE_CAP(list->size, list->capacity, list->items);

	return idx;
}

bool list_remove_item(struct list_t *list, const void *item, equality_fn_t *eq)
{
    if (list == NULL || item == NULL)
        return false;

	size_t ret;

	if ((ret = list_index_of(list, item, eq)) == ITEM_NOT_FOUND)
		return false;

	list_remove(list, ret);

	return ret;
}

void list_remove_all(struct list_t *list)
{
	list->size = 0;
	list->capacity = LIST_STARTING_CAPACITY;
	list->items = (void **)(realloc(list->items, list->capacity * sizeof(void *)));
}

bool list_sort(struct list_t *list, compare_fn_t *cmp)
{
    if (list == NULL)
        return false;

    if (list->size == 0)
        return false;

    if (list->size == 1)
        return true;

    qsort(list->items, list->size, sizeof(void *), cmp);
    
    return true;
}