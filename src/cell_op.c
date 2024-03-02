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

#include <cell_op.h>

void increment(cell **ptr) {
    (*ptr)->val++;
}

void decrement(cell **ptr) {
    (*ptr)->val--;
}

void ptr_right(cell **ptr) {
    if (!(*ptr)->next) cell_add(*ptr);
    *ptr = (*ptr)->next;
}

void ptr_left(cell **ptr) {
    if (!(*ptr)->prev) (*ptr)->prev = cell_shift(*ptr);
    *ptr = (*ptr)->prev;
}

void load_out(cell **ptr) {
    putchar((*ptr)->val);
}

void load_in(cell **ptr) {
    (*ptr)->val = getchar();
}

void no_op(cell **ptr) {}

void (*operationFactory(char c))(cell**) {
    switch (c) {
        case '+':
            return &increment;
        case '-':
            return &decrement;
        case '>':
            return &ptr_right;
        case '<':
            return &ptr_left;
        case '.':
            return &load_out;
        case ',':
            return &load_in;
        default:
            return &no_op;
    }
}
