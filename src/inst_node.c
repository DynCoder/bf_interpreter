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

#include <inst_node.h>

instnode *inst_new(char c) {
    instnode *in = malloc(sizeof(instnode));
    in->inst = c;
    in->next = NULL;
    return in;
}

void inst_append(instnode *ptr, char c) {
    if (ptr->next) inst_free(ptr->next);
    ptr->next = inst_new(c);
}

void inst_advance(instnode **ptr) {
    *ptr = (*ptr)->next;
}

void inst_free(instnode *ptr) {
    if (!ptr) return;
    inst_free(ptr->next);
    free(ptr);
}
