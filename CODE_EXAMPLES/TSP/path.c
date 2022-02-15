#include "path.h"

#include "inttypes.h"
#include "stack.h"
#include "vertices.h"

#include <stdlib.h>

//taken from assignment
struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
        if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    if (!stack_peek(p->vertices, &x)) {
        stack_push(p->vertices, v);
        return true;
    }
    stack_peek(p->vertices, &x);
    graph_edge_weight(G, x, v);
    if (stack_push(p->vertices, v)) {
        p->length += graph_edge_weight(G, x, v);
        return true;
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_pop(p->vertices, v)) {
        uint32_t x;
        if (stack_peek(p->vertices, &x)) {
            p->length -= graph_edge_weight(G, x, *v);
        }
        return true;
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

//check if also need to print out length of path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
}
