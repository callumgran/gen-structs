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

#ifndef LL_ITERATOR_H
#define LL_ITERATOR_H

#include <stdlib.h>

#include "d_linkedlist.h"
#include "s_linkedlist.h"

struct d_ll_iter_t {
        struct d_linkedlist_node_t *curr;
};

struct s_ll_iter_t {
        struct s_linkedlist_node_t *curr;
};

void d_ll_start(struct d_ll_iter_t *iter, struct d_linkedlist_t *list);

void d_ll_start_rev(struct d_ll_iter_t *iter, struct d_linkedlist_t *list);

void d_ll_next(struct d_ll_iter_t *iter);

void d_ll_prev(struct d_ll_iter_t *iter);

bool d_ll_has_next(struct d_ll_iter_t *iter);

void *d_ll_get(struct d_ll_iter_t *iter);

void s_ll_start(struct s_ll_iter_t *iter, struct s_linkedlist_t *list);

void s_ll_next(struct s_ll_iter_t *iter);

bool s_ll_has_next(struct s_ll_iter_t *iter);

void *s_ll_get(struct s_ll_iter_t *iter);

#define LL_ITER_START(iter, list) _Generic((iter), \
              struct d_ll_iter_t *: d_ll_start, \
              struct s_ll_iter_t *: s_ll_start \
              )(iter, list)

#endif