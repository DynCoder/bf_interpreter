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

#include <brainf.h>

static int loop(cell *instptr, cell *cellptr);

static int execute(cell *instptr, cell *cellptr) {
    cell *i = instptr;
    int status = 0;
    char cmd;
    while (i && !status) {
        cmd = i->val;
        i = i->next;
        if (cmd == EOF) return 1;
        if (cmd == '[') {
            cell *p_loop = cell_new(), *m;
            m = p_loop;
            while (i) {
                cmd = i->val;
                i = i->next;
                if (cmd == EOF) status++;
                m = cell_add_val(m, cmd);
            }
            status += loop(p_loop, cellptr);
            cell_free_all(p_loop);
        } else {
            (*operationFactory(cmd))(&cellptr);
        }
    }
    return 0;
}

static int loop(cell *instptr, cell *cellptr) {
    int status = 0;
    while (cellptr->val && !status) {
        status = execute(instptr, cellptr);
    }
    return status;
}

int bf_run_file(char filename[]) {

	FILE *p_file = fopen(filename, "r");

	if (!p_file) {
		printf("Problem trying to open file\n");
		return 1;
	}

	int status = 0;
	cell *p_cell = cell_new();

	char cmd;
	while ((cmd = fgetc(p_file)) != EOF && !status) {
		if (cmd == '[') {
			cell *p_loop = cell_new(), *m;
			m = p_loop;
			int n = 1;
			while (n) {
				if ((cmd = fgetc(p_file)) == ']') n--;
				if (cmd == '[') n++;
				if (cmd == EOF) status++;
				m = cell_add_val(m, cmd);
			}
			status += loop(p_loop, p_cell);
			cell_free_all(p_loop);
		} else if (cmd == ']') {
			printf("Unopened closing bracket encountered\n");
			status++;
		} else {
			(*operationFactory(cmd))(&p_cell);
		}
	}

	fclose(p_file);
	cell_free_all(p_cell);

	return status;

}


