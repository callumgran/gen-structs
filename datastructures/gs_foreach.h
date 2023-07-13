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

#ifndef GS_FOREACH_H
#define GS_FOREACH_H

#include "d_linkedlist.h"
#include "list.h"
#include "queue.h"
#include "s_linkedlist.h"
#include "stack.h"

typedef void exec_fn_t(void *item);

void queue_foreach(struct queue_t *queue, exec_fn_t exec);

void stack_foreach(struct stack_t *stack, exec_fn_t exec);

void list_foreach(struct list_t *list, exec_fn_t exec);

void d_ll_foreach(struct d_linkedlist_t *dll, exec_fn_t exec);

void s_ll_foreach(struct s_linkedlist_t *sll, exec_fn_t exec);

#define FOREACH(structure, exec)                     \
	_Generic((structure), struct queue_t *           \
			 : queue_foreach, struct stack_t *       \
			 : stack_foreach, struct list_t *        \
			 : list_foreach, struct d_linkedlist_t * \
			 : d_ll_foreach, struct s_linkedlist_t * \
			 : s_ll_foreach)(structure, exec)

#endif