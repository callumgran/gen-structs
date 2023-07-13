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
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../datastructures/gs_foreach.h"

int q_a = 1;
int q_b = 2;
int q_c = 3;

int s_a = 4;
int s_b = 5;
int s_c = 6;

int l_a = 7;
int l_b = 8;
int l_c = 9;

int dll_a = 10;
int dll_b = 11;
int dll_c = 12;

int sll_a = 13;
int sll_b = 14;
int sll_c = 15;

int counter = 1;

void conf_queue(struct queue_t *queue)
{
	queue_init(queue, 3);

	queue_push(queue, &q_a);
	queue_push(queue, &q_b);
	queue_push(queue, &q_c);
}

void conf_stack(struct stack_t *stack)
{
	stack_init(stack, 3);

	stack_push(stack, &s_a);
	stack_push(stack, &s_b);
	stack_push(stack, &s_c);
}

void conf_list(struct list_t *list)
{
	list_init(list);

	list_append(list, &l_a);
	list_append(list, &l_b);
	list_append(list, &l_c);
}

void conf_dll(struct d_linkedlist_t *dll)
{
	d_linkedlist_init(dll);

	d_linkedlist_push_back(dll, &dll_a);
	d_linkedlist_push_back(dll, &dll_b);
	d_linkedlist_push_back(dll, &dll_c);
}

void conf_sll(struct s_linkedlist_t *sll)
{
	s_linkedlist_init(sll);

	s_linkedlist_push_back(sll, &sll_a);
	s_linkedlist_push_back(sll, &sll_b);
	s_linkedlist_push_back(sll, &sll_c);
}

void print_and_check_val(void *item)
{
	int val = *(int *)item;

	printf("Val is %d\n", val);
	assert(val == counter++);
}

int main(void)
{
	struct queue_t queue;
	struct stack_t stack;
	struct list_t list;
	struct d_linkedlist_t dll;
	struct s_linkedlist_t sll;

	conf_queue(&queue);
	conf_stack(&stack);
	conf_list(&list);
	conf_dll(&dll);
	conf_sll(&sll);

	FOREACH(&queue, &print_and_check_val);
	FOREACH(&stack, &print_and_check_val);
	FOREACH(&list, &print_and_check_val);
	FOREACH(&dll, &print_and_check_val);
	FOREACH(&sll, &print_and_check_val);

	printf("--------------------------------\n");
	printf("Completed foreach tests\n");
	printf("--------------------------------\n");
}