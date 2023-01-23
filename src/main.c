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

#include <stdio.h>
#include <brainf.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("No file passed\n");
        return 1;
    }

    int status = bf_run_file(argv[1]);

    return status;

}
