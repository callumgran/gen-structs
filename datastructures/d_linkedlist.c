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

#include "d_linkedlist.h"

bool d_linkedlist_init(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return false;

	d_linkedlist->head = NULL;
	d_linkedlist->tail = NULL;
	d_linkedlist->size = 0;

	return true;
}

bool d_linkedlist_free(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return false;

	struct d_linkedlist_node_t *node = d_linkedlist->head;
	struct d_linkedlist_node_t *next;

	while (node != NULL) {
		next = node->next;
		free(node);
		node = next;
	}

	return true;
}

bool d_linkedlist_empty(const struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return false;

	return !d_linkedlist->size;
}

size_t d_linkedlist_size(const struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return 0;

	return d_linkedlist->size;
}

bool d_linkedlist_push_front(struct d_linkedlist_t *d_linkedlist, void *item)
{
	if (d_linkedlist == NULL || item == NULL)
		return false;

	struct d_linkedlist_node_t *node = malloc(sizeof(struct d_linkedlist_node_t));

	if (node == NULL)
		return false;

	node->item = item;
	node->next = d_linkedlist->head;
	node->prev = NULL;

	if (d_linkedlist->head != NULL)
		d_linkedlist->head->prev = node;

	d_linkedlist->head = node;

	if (d_linkedlist->tail == NULL)
		d_linkedlist->tail = node;

	d_linkedlist->size++;

	return true;
}

bool d_linkedlist_push_back(struct d_linkedlist_t *d_linkedlist, void *item)
{
	if (d_linkedlist == NULL || item == NULL)
		return false;

	struct d_linkedlist_node_t *node = malloc(sizeof(struct d_linkedlist_node_t));

	if (node == NULL)
		return false;

	node->item = item;
	node->next = NULL;
	node->prev = d_linkedlist->tail;

	if (d_linkedlist->tail != NULL)
		d_linkedlist->tail->next = node;

	d_linkedlist->tail = node;

	if (d_linkedlist->head == NULL)
		d_linkedlist->head = node;

	d_linkedlist->size++;

	return true;
}

void *d_linkedlist_pop_front(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return NULL;

	if (d_linkedlist->head == NULL)
		return NULL;

	struct d_linkedlist_node_t *node = d_linkedlist->head;
	void *item = node->item;

	d_linkedlist->head = node->next;

	if (d_linkedlist->head != NULL)
		d_linkedlist->head->prev = NULL;

	if (d_linkedlist->tail == node)
		d_linkedlist->tail = NULL;

	free(node);

	d_linkedlist->size--;

	return item;
}

void *d_linkedlist_pop_back(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return NULL;

	if (d_linkedlist->tail == NULL)
		return NULL;

	struct d_linkedlist_node_t *node = d_linkedlist->tail;
	void *item = node->item;

	d_linkedlist->tail = node->prev;

	if (d_linkedlist->tail != NULL)
		d_linkedlist->tail->next = NULL;

	if (d_linkedlist->head == node)
		d_linkedlist->head = NULL;

	free(node);

	d_linkedlist->size--;

	return item;
}

void *d_linkedlist_remove(struct d_linkedlist_t *d_linkedlist, const void *item, compare_fn_t cmp)
{
	if (d_linkedlist == NULL || item == NULL)
		return NULL;

	struct d_linkedlist_node_t *node = d_linkedlist->head;

	while (node != NULL) {
		if (cmp(node->item, item) == 0) {
			if (node->prev != NULL)
				node->prev->next = node->next;

			if (node->next != NULL)
				node->next->prev = node->prev;

			if (d_linkedlist->head == node)
				d_linkedlist->head = node->next;

			if (d_linkedlist->tail == node)
				d_linkedlist->tail = node->prev;

			void *ret = node->item;

			free(node);

			d_linkedlist->size--;

			return ret;
		}

		node = node->next;
	}

	return NULL;
}

void *d_linkedlist_front(const struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return NULL;

	if (d_linkedlist->head == NULL)
		return NULL;

	return d_linkedlist->head->item;
}

void *d_linkedlist_back(const struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return NULL;

	if (d_linkedlist->tail == NULL)
		return NULL;

	return d_linkedlist->tail->item;
}

bool d_linkedlist_clear(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return false;

	struct d_linkedlist_node_t *node = d_linkedlist->head;

	while (node != NULL) {
		struct d_linkedlist_node_t *next = node->next;
		free(node);
		node = next;
	}

	d_linkedlist->head = NULL;
	d_linkedlist->tail = NULL;
	d_linkedlist->size = 0;

	return true;
}

bool d_linkedlist_contains(const struct d_linkedlist_t *d_linkedlist, const void *item,
						   compare_fn_t cmp)
{
	if (d_linkedlist == NULL || item == NULL)
		return false;

	struct d_linkedlist_node_t *node = d_linkedlist->head;

	while (node != NULL) {
		if (cmp(node->item, item) == 0)
			return true;

		node = node->next;
	}

	return false;
}

void *d_linkedlist_get(const struct d_linkedlist_t *d_linkedlist, size_t index)
{
	if (d_linkedlist == NULL)
		return NULL;

	if (index >= d_linkedlist->size)
		return NULL;

	struct d_linkedlist_node_t *node;
	if (d_linkedlist->size - index < index) {
		node = d_linkedlist->tail;
		for (size_t i = 0; i < index; i++)
			node = node->prev;
	} else {
		node = d_linkedlist->head;
		for (size_t i = 0; i < index; i++)
			node = node->next;
	}

	return node->item;
}

bool d_linkedlist_reverse(struct d_linkedlist_t *d_linkedlist)
{
	if (d_linkedlist == NULL)
		return false;

	struct d_linkedlist_node_t *node = d_linkedlist->head;

	while (node != NULL) {
		struct d_linkedlist_node_t *next = node->next;
		node->next = node->prev;
		node->prev = next;
		node = next;
	}

	struct d_linkedlist_node_t *tmp = d_linkedlist->head;
	d_linkedlist->head = d_linkedlist->tail;
	d_linkedlist->tail = tmp;

	return true;
}