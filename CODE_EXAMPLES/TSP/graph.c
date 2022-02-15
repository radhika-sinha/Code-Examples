#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//from assignment
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

//from assignment
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

//from assignment
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < START_VERTEX || i >= G->vertices || j < START_VERTEX || j >= G->vertices || k < 1) {
        return false;
    }
    G->matrix[i][j] = k;
    if (G->undirected) {
        G->matrix[j][i] = k;
    }
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (START_VERTEX <= i && i < G->vertices) {
        if (START_VERTEX <= j && j < G->vertices) {
            if (G->matrix[i][j] > 0) {
                return true;
            }
        }
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (START_VERTEX <= i && i < G->vertices && START_VERTEX <= j && j < G->vertices) {
        if (G->matrix[i][j] > 0) {
            return G->matrix[i][j];
        }
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (START_VERTEX <= v && v < VERTICES) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (START_VERTEX <= v && v < VERTICES) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = START_VERTEX; i < G->vertices; i++) {
        for (uint32_t j = START_VERTEX; j < G->vertices; j++) {
            if (graph_has_edge(G, i, j)) {
                printf("matrix[%" PRIu32 "][%" PRIu32 "] = %" PRIu32 "\n", i, j, G->matrix[i][j]);
            }
        }
    }
}
