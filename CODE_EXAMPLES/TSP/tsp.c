//Radhika Sinha
//Assignment 4 - Traveling Salesman Problem
//Oct 18, 2021

#include "graph.h"
#include "path.h"
#include "set.h"
#include "vertices.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTS "uvhi:o:"

bool verbose = false;

void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    int *counter, uint32_t *popped);

typedef enum { UNDIRECTED, VERBOSE, HELP, INPUT, OUTPUT } Options;

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    Set s = empty_set();
    int num_vertices = 0;
    int counter = 0;
    bool undirected = false;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTS)) != -1) {
        switch (opt) {
        case 'u':
            s = insert_set(UNDIRECTED, s);
            undirected = true;
            break;
        case 'v':
            s = insert_set(VERBOSE, s);
            verbose = true;
            break;
        case 'h': s = insert_set(HELP, s); break;
        case 'i':
            s = insert_set(INPUT, s);
            infile = fopen(optarg, "r");
            break;
        case 'o':
            s = insert_set(OUTPUT, s);
            outfile = fopen(optarg, "w");
            break;
        }
    }

    if (member_set(HELP, s)) {
        char opt_array[5][10] = { "-u", "-v", "-h", "-i infile", "-o outfile" };
        char display_message[5][45] = { "use undirected graph.", "enable verbose printing.",
            "program usage and help.", "input containing graph (default: stdin)",
            "output of computed path (default: stdout)" };
        char my_tab[4] = "   ";
        printf("SYNOPSIS\n");
        printf("   Traveling Salesman Problem using DFS.\n\n");
        printf("USAGE\n");
        printf("./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        for (int i = 0; i < 5; i++) {
            printf("%s%-15s%-56s \n", my_tab, opt_array[i], display_message[i]);
        }
    }

    if (infile == NULL) {
        printf("Error: failed to open infile.\n");
        exit(1);
    }
    char buf[1024];
    char *num_string = (fgets(buf, 1024, infile));
    if (num_string == NULL) {
        printf("Error: malformed number of vertices.\n");
        exit(1);
    }
    num_vertices = atoi(num_string);
    if (num_vertices > VERTICES) {
        printf("Error: malformed number of vertices.");
        exit(1);
    }
    char *cities[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        if (fgets(buf, 1024, infile) != NULL) {
            buf[strlen(buf) - 1] = '\0';
            cities[i] = strdup(buf);
        } else {
            printf("Error: malformed city name");
            exit(1);
        }
    }

    Graph *G = graph_create(num_vertices, undirected);
    uint32_t i;
    uint32_t j;
    uint32_t k;
    int scan;
    while (((scan = fscanf(infile, "%d %d %d", &i, &j, &k)) == 3) && scan != EOF) {
        graph_add_edge(G, i, j, k);
    }
    if (scan != 3 && scan != EOF) {
        printf("Error: malformed edge.\n");
        exit(1);
    }

    Path *curr = path_create();
    Path *shortest = path_create();
    uint32_t popped = 0;
    DFS(G, START_VERTEX, curr, shortest, cities, outfile, &counter, &popped);
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Total recursive calls: %d\n", counter);

    graph_delete(&G);
    path_delete(&curr);
    path_delete(&shortest);
    return 0;
}

//change to amount of vertices for graph
void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    int *counter, uint32_t *popped) {
    *counter += 1;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    for (uint32_t j = START_VERTEX; j < graph_vertices(G); j++) {
        if (graph_has_edge(G, v, j)) {
            if (!graph_visited(G, j)) {
                if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                    DFS(G, j, curr, shortest, cities, outfile, counter, popped);
                }
            }
        }
    }
    if (path_vertices(curr) == graph_vertices(G)) {
        if (graph_has_edge(G, v, START_VERTEX)) {
            path_push_vertex(curr, START_VERTEX, G);
            if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                path_copy(shortest, curr);
            }
            if (verbose) {
                path_print(curr, outfile, cities);
            }
            path_pop_vertex(curr, popped, G);
        }
    }
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, popped, G);
}
