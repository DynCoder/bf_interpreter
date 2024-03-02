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

#ifndef INST_NODE_H_
#define INST_NODE_H_

#include <stdlib.h>

typedef struct _instnode {
    char inst;
    struct _instnode *next;
} instnode;

instnode *inst_new(char c);
void inst_append(instnode *ptr, char c);
void inst_advance(instnode **ptr);
void inst_free(instnode *ptr);

#endif /* INST_NODE_H_ */
