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
#include <string.h>

#include "../datastructures/stack.h"

struct tuple_t {
    int a;
    double b;
};


void test_push_pop_get(void)
{
    /* Stack will hold values of Tuple */
    struct stack_t stack;
    stack_init(&stack, 16);

    bool rc = stack_push(&stack, &(struct tuple_t){ .a = 1, .b = 1.1 });
    assert(rc);

    rc = stack_push(&stack, &(struct tuple_t){ .a = 2, .b = 2.2 });
    assert(rc);

    struct tuple_t *get = stack_get(&stack);
    assert(get->a == 2);
    assert(get->b == 2.2);

    struct tuple_t *pop = stack_pop(&stack);
    assert(pop->a == 2);
    assert(pop->b == 2.2);

    get = stack_get(&stack);
    assert(get->a == 1);
    assert(get->b == 1.1);

    pop = stack_pop(&stack);
    assert(pop->a == 1);
    assert(pop->b == 1.1);

    stack_free(&stack);
}

int main(void)
{
    test_push_pop_get();
    return 0;
}