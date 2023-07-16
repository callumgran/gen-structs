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

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../datastructures/queue.h"

struct tuple_t {
	int a;
	double b;
};


void test_push_pop_get(void)
{
	/* queue will hold values of Tuple */
	struct queue_t queue;
	queue_init(&queue, 16);

	bool rc = queue_push(&queue, &(struct tuple_t){ .a = 1, .b = 1.1 });
	assert(rc);

	rc = queue_push(&queue, &(struct tuple_t){ .a = 2, .b = 2.2 });
	assert(rc);

	struct tuple_t *get = queue_get(&queue);
	assert(get->a == 2);
	assert(get->b == 2.2);

	struct tuple_t *pop = queue_pop(&queue);
	assert(pop->a == 2);
	assert(pop->b == 2.2);

	get = queue_get(&queue);
	assert(get->a == 1);
	assert(get->b == 1.1);

	pop = queue_pop(&queue);
	assert(pop->a == 1);
	assert(pop->b == 1.1);

	queue_free(&queue);

	printf("--------------------------------\n");
	printf("Completed push pop get queue tests\n");
	printf("--------------------------------\n");
}

int main(void)
{
	test_push_pop_get();
	return 0;
}