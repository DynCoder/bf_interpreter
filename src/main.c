#include <stdio.h>
#include <stdlib.h>

typedef struct cell_ cell;
struct cell_ {
    char val;
    cell *next;
    cell *prev;
};

static void cell_free(cell *ptr) {
    if (!ptr) return;
    cell_free(ptr->next);
    free(ptr);
}

static void cell_free_all(cell *ptr) {
    if (!ptr) return;
    while (ptr->prev) {
        ptr = ptr->prev;
    }
    cell_free(ptr);
}

static cell* cell_add(cell *prev) {
    if (prev->next) cell_free(prev->next);
    cell *c = malloc(sizeof(cell));
    c->val = 0;
    c->prev = prev;
    prev->next = c;
    c->next = NULL;
    return c;
}

static cell* cell_add_val(cell *prev, char v) {
    cell *c = cell_add(prev);
    c->val = v;
    return c;
}

static cell* cell_new() {
    cell *c = malloc(sizeof(cell));
    c->val = 0;
    c->prev = NULL;
    c->next = NULL;
    return c;
}

static cell* cell_shift(cell *first) {
    cell *c = cell_new();
    c->next = first;
    first->prev = c;
    return c;
}

static void increment(cell **ptr) {
    (*ptr)->val++;
}
static void decrement(cell **ptr) {
    (*ptr)->val--;
}
static void ptr_right(cell **ptr) {
    if (!(*ptr)->next) cell_add(*ptr);
    *ptr = (*ptr)->next;
}
static void ptr_left(cell **ptr) {
    if (!(*ptr)->prev) (*ptr)->prev = cell_shift(*ptr);
    *ptr = (*ptr)->prev;
}
static void load_out(cell **ptr) {
    putchar((*ptr)->val);
}
static void load_in(cell **ptr) {
    (*ptr)->val = getchar();
}
static void no_op(cell **ptr) {}

static void (*operationFactory(char c))(cell**) {
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

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("No file passed\n");
        return 1;
    }

    FILE *p_file = fopen(argv[1], "r");

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

