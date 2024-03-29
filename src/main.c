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

#include <stdio.h>
#include <brainf.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("No file passed\n");
        return 0;
    }

    instnode *instructions = bf_compile(argv[1]);
    if (!instructions) return 1; // Fail

    bf_run(instructions);

    bf_close(instructions);
    return 0;

}
