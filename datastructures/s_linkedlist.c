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

#include "common.h"
#include "s_linkedlist.h"

bool s_linkedlist_init(struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return false;

	s_linkedlist->head = NULL;
	s_linkedlist->tail = NULL;
	s_linkedlist->size = 0;

	return true;
}

bool s_linkedlist_free(struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return false;

	struct s_linkedlist_node_t *node = s_linkedlist->head;
	struct s_linkedlist_node_t *next;

	while (node != NULL) {
		next = node->next;
		free(node);
		node = next;
	}

	return true;
}

bool s_linkedlist_empty(const struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return false;

	return !s_linkedlist->size;
}

size_t s_linkedlist_size(const struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return 0;

	return s_linkedlist->size;
}

bool s_linkedlist_push_front(struct s_linkedlist_t *s_linkedlist, const void *item)
{
	if (s_linkedlist == NULL)
		return false;

	struct s_linkedlist_node_t *node =
		(struct s_linkedlist_node_t *)(malloc(sizeof(struct s_linkedlist_node_t)));

	if (node == NULL)
		return false;

	node->item = item;
	node->next = s_linkedlist->head;
	s_linkedlist->head = node;

	if (s_linkedlist->tail == NULL)
		s_linkedlist->tail = node;

	s_linkedlist->size++;

	return true;
}

bool s_linkedlist_push_back(struct s_linkedlist_t *s_linkedlist, const void *item)
{
	if (s_linkedlist == NULL)
		return false;

	struct s_linkedlist_node_t *node =
		(struct s_linkedlist_node_t *)(malloc(sizeof(struct s_linkedlist_node_t)));

	if (node == NULL)
		return false;

	node->item = item;
	node->next = NULL;

	if (s_linkedlist->tail != NULL)
		s_linkedlist->tail->next = node;

	s_linkedlist->tail = node;

	if (s_linkedlist->head == NULL)
		s_linkedlist->head = node;

	s_linkedlist->size++;

	return true;
}

void *s_linkedlist_pop_front(struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return NULL;

	if (s_linkedlist->head == NULL)
		return NULL;

	struct s_linkedlist_node_t *node = s_linkedlist->head;
	void *item = node->item;

	s_linkedlist->head = node->next;

	if (s_linkedlist->head == NULL)
		s_linkedlist->tail = NULL;

	free(node);

	s_linkedlist->size--;

	return item;
}

void *s_linkedlist_pop_back(struct s_linkedlist_t *s_linkedlist)
{
	if (s_linkedlist == NULL)
		return NULL;

	if (s_linkedlist->tail == NULL)
		return NULL;

	struct s_linkedlist_node_t *node = s_linkedlist->head;
	void *item = node->item;

	if (s_linkedlist->head == s_linkedlist->tail) {
		s_linkedlist->head = NULL;
		s_linkedlist->tail = NULL;
	} else {
		while (node->next != s_linkedlist->tail)
			node = node->next;

		node->next = NULL;
		s_linkedlist->tail = node;
	}

	free(node);

	s_linkedlist->size--;

	return item;
}

bool s_linkedlist_remove(struct s_linkedlist_t *s_linkedlist, const void *item, compare_fn_t cmp)
{
	if (s_linkedlist == NULL || item == NULL)
		return false;

	if (s_linkedlist->head == NULL)
		return false;

	struct s_linkedlist_node_t *node = s_linkedlist->head;
	struct s_linkedlist_node_t *prev = NULL;

	while (node != NULL) {
		if (cmp(node->item, item) == 0) {
			if (prev == NULL)
				s_linkedlist->head = node->next;
			else
				prev->next = node->next;

			if (node == s_linkedlist->tail)
				s_linkedlist->tail = prev;

			free(node);

			s_linkedlist->size--;

			return true;
		}

		prev = node;
		node = node->next;
	}

	return false;
}

void *s_linkedlist_front(const struct s_linkedlist_t *s_linkedlist)
{
        if (s_linkedlist == NULL)
                return NULL;

        if (s_linkedlist->head == NULL)
                return NULL;

        return s_linkedlist->head->item;
}

void *s_linkedlist_back(const struct s_linkedlist_t *s_linkedlist)
{
        if (s_linkedlist == NULL)
                return NULL;

        if (s_linkedlist->tail == NULL)
                return NULL;

        return s_linkedlist->tail->item;
}

bool s_linkedlist_clear(struct s_linkedlist_t *s_linkedlist)
{
        if (s_linkedlist == NULL)
                return false;
        
        s_linkedlist_free(s_linkedlist);

        s_linkedlist->head = NULL;
        s_linkedlist->tail = NULL;
        s_linkedlist->size = 0;

        return true;
}

bool s_linkedlist_contains(const struct s_linkedlist_t *s_linkedlist, const void *item, compare_fn_t cmp)
{
        if (s_linkedlist == NULL || item == NULL)
                return false;

        if (s_linkedlist->head == NULL)
                return false;

        struct s_linkedlist_node_t *node = s_linkedlist->head;

        while (node != NULL) {
                if (cmp(node->item, item) == 0)
                        return true;

                node = node->next;
        }

        return false;
}

void *s_linkedlist_get(const struct s_linkedlist_t *s_linkedlist, size_t index)
{
        if (s_linkedlist == NULL)
                return NULL;

        if (s_linkedlist->head == NULL)
                return NULL;

        struct s_linkedlist_node_t *node = s_linkedlist->head;

        while (index-- > 0) {
                if (node == NULL)
                        return NULL;

                node = node->next;
        }

        return node->item;
}

bool s_linkedlist_reverse(struct s_linkedlist_t *s_linkedlist)
{
        if (s_linkedlist == NULL)
                return false;

        if (s_linkedlist->head == NULL)
                return false;

        struct s_linkedlist_node_t *prev = NULL;
        struct s_linkedlist_node_t *node = s_linkedlist->head;
        struct s_linkedlist_node_t *next = NULL;

        while (node != NULL) {
                next = node->next;
                node->next = prev;
                prev = node;
                node = next;
        }

        s_linkedlist->tail = s_linkedlist->head;
        s_linkedlist->head = prev;

        return true;
}