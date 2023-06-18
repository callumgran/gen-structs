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

#ifndef D_LINKEDLIST_H
#define D_LINKEDLIST_H

#include <stdbool.h>
#include <sys/types.h>

#include "common.h"

struct d_linkedlist_node_t {
	void *item;
	struct d_linkedlist_node_t *next;
	struct d_linkedlist_node_t *prev;
};

struct d_linkedlist_t {
	struct d_linkedlist_node_t *head;
	struct d_linkedlist_node_t *tail;
	size_t size;
};

bool d_linkedlist_init(struct d_linkedlist_t *list);
bool d_linkedlist_free(struct d_linkedlist_t *list);

bool d_linkedlist_empty(const struct d_linkedlist_t *list);
size_t d_linkedlist_size(const struct d_linkedlist_t *list);

bool d_linkedlist_push_front(struct d_linkedlist_t *list, void *item);
bool d_linkedlist_push_back(struct d_linkedlist_t *list, void *item);

void *d_linkedlist_pop_front(struct d_linkedlist_t *list);
void *d_linkedlist_pop_back(struct d_linkedlist_t *list);
void *d_linkedlist_remove(struct d_linkedlist_t *d_linkedlist, const void *item, compare_fn_t cmp);

void *d_linkedlist_front(const struct d_linkedlist_t *list);
void *d_linkedlist_back(const struct d_linkedlist_t *list);

bool d_linkedlist_clear(struct d_linkedlist_t *list);
bool d_linkedlist_contains(const struct d_linkedlist_t *d_linkedlist, const void *item,
						   compare_fn_t cmp);
void *d_linkedlist_get(const struct d_linkedlist_t *list, const size_t index);

bool d_linkedlist_reverse(struct d_linkedlist_t *list);

#endif