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

#ifndef BRAINF_H_
#define BRAINF_H_

#include <cell.h>
#include <cell_op.h>
#include <inst_node.h>
#include <stdlib.h>
#include <stdio.h>

void bf_run(instnode *instptr);
void bf_close(instnode *instptr);
instnode *bf_compile(char *filename);

#endif /* BRAINF_H_ */
