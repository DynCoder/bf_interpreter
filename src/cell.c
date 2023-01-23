/*
 * Brainfuck interpreter
 *     ~ DynCoder
 *
 * This file is published under the GPLv3 license.
 * A copy of GPLv3 is provided in the project's original repository:
 *
 * https://github.com/Joshua260403/bf_interpreter
 *
 */

#include <cell.h>

void cell_free(cell *ptr) {
    if (!ptr) return;
    cell_free(ptr->next);
    free(ptr);
}

void cell_free_all(cell *ptr) {
    if (!ptr) return;
    while (ptr->prev) {
        ptr = ptr->prev;
    }
    cell_free(ptr);
}

cell *cell_add(cell *prev) {
    if (prev->next) cell_free(prev->next);
    cell *c = malloc(sizeof(cell));
    c->val = 0;
    c->prev = prev;
    prev->next = c;
    c->next = NULL;
    return c;
}

cell *cell_add_val(cell *prev, char v) {
    cell *c = cell_add(prev);
    c->val = v;
    return c;
}

cell *cell_shift(cell *first) {
    cell *c = cell_new();
    c->next = first;
    first->prev = c;
    return c;
}

cell *cell_new() {
    cell *c = malloc(sizeof(cell));
    c->val = 0;
    c->prev = NULL;
    c->next = NULL;
    return c;
}
