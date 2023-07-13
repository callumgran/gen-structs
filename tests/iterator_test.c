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

#include "../datastructures/ll_iterator.h"

void test_iter_start(void)
{
        int a = 1;
        int b = 2;
        int c = 3;
        struct d_linkedlist_t dll;
        d_linkedlist_init(&dll);
        d_linkedlist_push_back(&dll, &a);
        d_linkedlist_push_back(&dll, &b);
        d_linkedlist_push_back(&dll, &c);

        struct s_linkedlist_t sll;
        s_linkedlist_init(&sll);
        s_linkedlist_push_back(&sll, &a);
        s_linkedlist_push_back(&sll, &b);
        s_linkedlist_push_back(&sll, &c);

        struct d_ll_iter_t dll_iter;
        LL_ITER_START(&dll_iter, &dll);

        int ret = *(int *)d_ll_get(&dll_iter);

        assert(ret == 1);

        struct s_ll_iter_t sll_iter;
        LL_ITER_START(&sll_iter, &sll);
        ret = *(int *)s_ll_get(&sll_iter);

        assert(ret == 1);

        printf("--------------------------------\n");
        printf("Completed start iterator tests\n");
        printf("--------------------------------\n");
}

int main(void)
{
        test_iter_start();
}
