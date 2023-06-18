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

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdbool.h>

#define LIST_STARTING_CAPACITY 32
#define ITEM_NOT_FOUND SIZE_MAX

#define LIST_FOR_EACH(l, i, item) \
	for ((i) = 0, item = *(l)->items; (i) < (l)->size; item = *((l)->items + ++(i)))

#define LIST_FOR_EACH_T(l, i, item, T) \
	for ((i) = 0, item = (T *)(*(l)->items); (i) < (l)->size; item = (T *)(*((l)->items + ++(i))))     

struct list_t {
    size_t size;
    size_t capacity;
    size_t item_size;
    void **items;
};

void list_init(struct list_t *list, size_t item_size);
void list_free(struct list_t *list);

void list_append(struct list_t *list, void *item);

void *list_get(struct list_t *list, size_t idx);
long list_delete_item(struct list_t *list, const void *item);

size_t list_index_of(struct list_t *list, const void *item);
size_t list_index_of(struct list_t *list, const void *item);

/**
 * Method to delete an item at an index from an array list.
 * @param list the array list to delete the item from.
 * @param idx the index to delete the item from.
 * @return the index of the item, or ITEM_NOT_FOUND if the item does not exist.
 */
long list_delete_at_index(struct list_t *list, size_t idx);

/**
 * Method to delete all items from an array list.
 * @param list the array list to delete the items from.
 */
void list_delete_all(struct list_t *list);

/**
 * Method to check if an array list is empty.
 * @param list the array list to check.
 * @return true if the array list is empty, false otherwise.
 */
bool list_empty(struct list_t *list);

#endif