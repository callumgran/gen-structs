/*
 *  Copyright (C) 2022-2023 Nicolai Brand, Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Founarrtion, either version 3 of the License, or
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

#include "ll_iterator.h"

void d_ll_start(struct d_ll_iter_t *iter, struct d_linkedlist_t *list)
{
	iter->curr = list->head;
}

void d_ll_start_rev(struct d_ll_iter_t *iter, struct d_linkedlist_t *list)
{
	iter->curr = list->tail;
}

void d_ll_next(struct d_ll_iter_t *iter)
{
	iter->curr = iter->curr->next;
}

void d_ll_prev(struct d_ll_iter_t *iter)
{
	iter->curr = iter->curr->prev;
}

bool d_ll_has_next(struct d_ll_iter_t *iter)
{
	return iter->curr != NULL;
}

void *d_ll_get(struct d_ll_iter_t *iter)
{
	return iter->curr->item;
}

void s_ll_start(struct s_ll_iter_t *iter, struct s_linkedlist_t *list)
{
	iter->curr = list->head;
}

void s_ll_next(struct s_ll_iter_t *iter)
{
	iter->curr = iter->curr->next;
}

bool s_ll_has_next(struct s_ll_iter_t *iter)
{
	return iter->curr != NULL;
}

void *s_ll_get(struct s_ll_iter_t *iter)
{
	return iter->curr->item;
}