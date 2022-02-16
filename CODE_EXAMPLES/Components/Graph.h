/*************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA3
 * Graph.h
 * Header file for Graph ADT
 ************************************************************************/

#pragma once

#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define UNDEF -1
#define NIL 0

/***Exported type***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// newGraph()
// Returns reference to new empty Graph object
Graph newGraph (int n);

// freeGraph()
// Frees all heap memory associated with Graph *G and sets *G to NULL
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder()
// Returns the order of Graph G
int getOrder(Graph G);

// getSize()
// Returns the size of Graph G
int getSize(Graph G);

// getParent()
// Returns the parent of vertex u
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of vertex u
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of verex u
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, creating a null graph
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v (adds u and v to eachothers
// adjacency lists)
// Pre: u and v must be in range [1, getOrder(G)]
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v
// Pre: u and v must be in range [1, getOrder(G)]
void addArc(Graph G, int u, int v);

// DFS
// Performs Depth First Search on a Graph with List S
void DFS(Graph G, List S);

/*** Other operations ***/

// transpose()
// ...
Graph transpose(Graph G);

//copyGraph();
// Copies...
Graph copyGraph(Graph G);

// printGraph()
// Prints out the Graph (all adjacency lists) to specified file
void printGraph(FILE* out, Graph G);

