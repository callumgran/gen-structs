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

#include "stack.h"

bool stack_init(struct stack_t *stack, const size_t cap)
{
	if (stack == NULL)
		return false;

	if (cap == 0)
		return false;

	stack->size = 0;
	stack->capacity = cap;
	stack->items = (void **)(malloc(cap * sizeof(void *)));

	return true;
}

bool stack_free(struct stack_t *stack)
{
	if (stack == NULL)
		return false;

	free(stack->items);

	return true;
}

bool stack_empty(const struct stack_t *stack)
{
	if (stack == NULL)
		return false;

	return !stack->size;
}

bool stack_full(const struct stack_t *stack)
{
	if (stack == NULL)
		return false;

	return stack->size == stack->capacity;
}

bool stack_push(struct stack_t *stack, void *item)
{
	if (stack == NULL || item == NULL)
		return false;

	if (stack_full(stack))
		return false;

	stack->items[stack->size++] = item;
	return true;
}

void *stack_pop(struct stack_t *stack)
{
	if (stack == NULL)
		return NULL;

	if (stack_empty(stack))
		return NULL;

	return stack->items[--stack->size];
}

void *stack_get(struct stack_t *stack)
{
	if (stack == NULL)
		return NULL;

	if (stack_empty(stack))
		return NULL;

	return stack->items[stack->size - 1];
}