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

#define MAX_ITER 512

// #define MEM_DUMP '#'
// TODO implement memdump command

#include <brainf.h>

static void skip(instnode **ptr) {
    char cmd;
    int n_loop = 1;
    do {
        inst_advance(ptr);
        cmd = (*ptr)->inst;
        if      (cmd == '[') n_loop++;
        else if (cmd == ']') n_loop--;
    } while (n_loop);
    inst_advance(ptr);
}

static void loop(instnode *instptr, cell *cellptr) {
    char cmd;
    int iter = 0;
    inst_advance(&instptr);
    while ((cmd = instptr->inst) != ']') {
#ifdef MAX_ITER
        if (iter++ > MAX_ITER) return;
#endif
        if (cmd == '[') {
            if (cellptr->val != 0) loop(instptr, cellptr);
            else                   skip(&instptr);
        } else {
            (*operationFactory(cmd))(&cellptr);
            inst_advance(&instptr);
        }
    }
}

void bf_run(instnode *instptr) {

    cell *cellptr = cell_new();

    loop(instptr, cellptr);

    cell_free_all(cellptr);

}

void bf_close(instnode *instptr) {
    inst_free(instptr);
}

instnode *bf_compile(char *filename) {

    FILE *p_file = fopen(filename, "r");

    if (!p_file) {
        printf("Problem trying to open file\n");
        fclose(p_file);
        return NULL;
    }

    instnode *inst_start = inst_new(' ');
    instnode *i = inst_start;

    int n_loop = 0;
    char cmd;

    while ((cmd = fgetc(p_file)) != EOF && n_loop >= 0) {
        if (cmd == '[')
            n_loop++;
        else if (cmd == ']')
            n_loop--;
        inst_append(i, cmd);
        inst_advance(&i);
    }
    inst_append(i, ']');

    fclose(p_file);

    if (n_loop != 0) {
        inst_free(inst_start);
        return NULL;
    }

    return inst_start;

}
