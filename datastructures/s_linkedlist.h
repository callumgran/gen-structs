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

struct s_linkedlist_node_t {
	void *item;
	struct s_linkedlist_node_t *next;
};

struct s_linkedlist_t {
	struct s_linkedlist_node_t *head;
	struct s_linkedlist_node_t *tail;
	size_t size;
};

bool s_linkedlist_init(struct s_linkedlist_t *list);
bool s_linkedlist_free(struct s_linkedlist_t *list);

bool s_linkedlist_empty(const struct s_linkedlist_t *list);
size_t s_linkedlist_size(const struct s_linkedlist_t *list);

bool s_linkedlist_push_front(struct s_linkedlist_t *list, void *item);
bool s_linkedlist_push_back(struct s_linkedlist_t *list, void *item);

void *s_linkedlist_pop_front(struct s_linkedlist_t *list);
void *s_linkedlist_pop_back(struct s_linkedlist_t *list);
bool s_linkedlist_remove(struct s_linkedlist_t *s_linkedlist, const void *item, compare_fn_t cmp);

void *s_linkedlist_front(const struct s_linkedlist_t *list);
void *s_linkedlist_back(const struct s_linkedlist_t *list);

bool s_linkedlist_clear(struct s_linkedlist_t *list);
bool s_linkedlist_contains(const struct s_linkedlist_t *s_linkedlist, const void *item, compare_fn_t cmp);
void *s_linkedlist_get(const struct s_linkedlist_t *list, const size_t index);

bool s_linkedlist_reverse(struct s_linkedlist_t *list);

#endif