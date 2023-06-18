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

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "common.h"

void init_list(struct list_t * list, size_t item_size)
{
    list->size = 0;
    list->capacity = LIST_STARTING_CAPACITY;
    list->items = (void **)(malloc(LIST_STARTING_CAPACITY * sizeof(void *)));
    list->item_size = item_size;
}

bool list_empty(struct list_t *list)
{
    return !list->size;
}

void list_add(struct list_t *list, void *item)
{
    ENSURE_CAP(list->size, list->capacity, list->items);
    *(list->items + list->size++) = item;
}

inline void *list_item_at_index(struct list_t *list, size_t idx)
{
    if (idx > list->size)
        return NULL;
    
    return *(list->items + idx);
}

long list_index_of_item(struct list_t *list, const void *item)
{
    bool pred = true;
    long i = 0;
    while (i < list->size) {
        BYTES_EQUAL((char *)*(list->items + i), (char *)item, list->item_size, pred);
        if (pred) 
            break;
        i++;
    }
    
    if (!pred)
        i = ITEM_NOT_FOUND;

    return i;
}

long list_delete_at_index(struct list_t *list, size_t idx)
{
    if (idx > list->size)
        return ITEM_NOT_FOUND;

    for (long i = idx; i < list->size - 1; i++)
        *(list->items + i) = *(list->items + i + 1);

    --list->size;

    REDUCE_CAP(list->size, list->capacity, list->items);

    return idx;
}

long list_delete_item(struct list_t *list, const void *item)
{
    long ret;
    if ((ret = list_index_of_item(list, item)) == ITEM_NOT_FOUND)
        return ITEM_NOT_FOUND;
    
    for (long i = ret; i < list->size - 1; i++)
        *(list->items + i) = *(list->items + i + 1);
    
    --list->item_size;

    REDUCE_CAP(list->size, list->capacity, list->items);

    return ret;
}

void list_delete_all(struct list_t *list)
{
    list->size = 0;
    list->capacity = LIST_STARTING_CAPACITY;
    list->items = (void **)(realloc(list->items, list->capacity * sizeof(void *)));
}

void free_list(struct list_t *list)
{
    free(list->items);
}