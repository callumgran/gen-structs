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

#include "common.h"
#include <stdbool.h>
#include <sys/types.h>

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

bool list_init(struct list_t *list, const size_t item_size);
bool list_free(struct list_t *list);

bool list_empty(const struct list_t *list);
size_t list_size(const struct list_t *list);

size_t list_index_of(struct list_t *list, const void *item, equality_fn_t *eq);
size_t list_index_of_r(struct list_t *list, const void *item, equality_fn_t *eq);

bool list_append(struct list_t *list, const void *item);
void *list_get(struct list_t *list, const size_t idx);
bool list_remove(struct list_t *list, const size_t idx);
bool list_remove_item(struct list_t *list, const void *item, equality_fn_t *eq);
bool list_remove_all(struct list_t *list);

bool list_sort(struct list_t *list, compare_fn_t *cmp);

#endif