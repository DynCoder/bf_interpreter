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
#include <stdlib.h>
#include <stdio.h>

int bf_run_file(char *filename);

#endif /* BRAINF_H_ */
