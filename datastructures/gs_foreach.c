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

#include <stdlib.h>

#include "gs_foreach.h"
#include "ll_iterator.h"

void queue_foreach(struct queue_t *queue, exec_fn_t exec)
{
	for (size_t i = 0; i < queue->size; i++) {
		exec(queue->items[i]);
	}
}

void stack_foreach(struct stack_t *stack, exec_fn_t exec)
{
	for (size_t i = 0; i < stack->size; i++) {
		exec(stack->items[i]);
	}
}


void list_foreach(struct list_t *list, exec_fn_t exec)
{
	for (size_t i = 0; i < list->size; i++) {
		exec(list->items[i]);
	}
}

void d_ll_foreach(struct d_linkedlist_t *dll, exec_fn_t exec)
{
	struct d_ll_iter_t iter;
	LL_ITER_START(&iter, dll);

	while (LL_ITER_HAS_NEXT(&iter)) {
		exec(LL_ITER_GET(&iter));
		LL_ITER_NEXT(&iter);
	}
}

void s_ll_foreach(struct s_linkedlist_t *sll, exec_fn_t exec)
{
	struct s_ll_iter_t iter;
	LL_ITER_START(&iter, sll);

	while (LL_ITER_HAS_NEXT(&iter)) {
		exec(LL_ITER_GET(&iter));
		LL_ITER_NEXT(&iter);
	}
}
