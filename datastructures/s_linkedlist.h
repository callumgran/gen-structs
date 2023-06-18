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

#ifndef S_LINKEDLIST_H
#define S_LINKEDLIST_H

#include <stdbool.h>
#include <sys/types.h>

struct list_node_t {
	void *item;
	struct list_node_t *next;
};

struct s_linkedlist_t {
	struct list_node_t *head;
	struct list_node_t *tail;
	size_t size;
	size_t item_size;
};

bool s_linkedlist_init(struct s_linkedlist_t *list, const size_t item_size);
void s_linkedlist_free(struct s_linkedlist_t *list);

bool s_linkedlist_empty(struct s_linkedlist_t *list);
size_t s_linkedlist_size(struct s_linkedlist_t *list);

bool s_linkedlist_push_front(struct s_linkedlist_t *list, void *item);
bool s_linkedlist_push_back(struct s_linkedlist_t *list, void *item);
void

	bool
	s_linkedlist_pop_front(struct s_linkedlist_t *list);
bool s_linkedlist_pop_back(struct s_linkedlist_t *list);

void *s_linkedlist_get_front(struct s_linkedlist_t *list);
void *s_linkedlist_get_back(struct s_linkedlist_t *list);

void s_linkedlist_remove(struct s_linkedlist_t *list, void *item);

#endif