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

#ifndef CELL_OP_H_
#define CELL_OP_H_

#include <cell.h>
#include <stdio.h>

void increment(cell **ptr);
void decrement(cell **ptr);
void ptr_right(cell **ptr);
void ptr_left(cell **ptr);
void load_out(cell **ptr);
void load_in(cell **ptr);

void (*operationFactory(char c))(cell**);

#endif /* CELL_OP_H_ */
