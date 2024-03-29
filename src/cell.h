/*
 * Brainfuck interpreter
 *     ~ DynCoder
 *
 * This file is published under the GPLv3 license.
 * A copy of GPLv3 is provided in the project's original repository:
 *
 * https://github.com/DynCoder/bf_interpreter
 *
 */

#ifndef CELL_H_
#define CELL_H_

#include <stdlib.h>

typedef struct _cell {
    char val;
    struct _cell *next;
    struct _cell *prev;
} cell;

void cell_free(cell *ptr);
void cell_free_all(cell *ptr);
cell* cell_add(cell *prev);
cell* cell_add_val(cell *prev, char v);
cell* cell_shift(cell *first);
cell* cell_new();

#endif /* CELL_H_ */
