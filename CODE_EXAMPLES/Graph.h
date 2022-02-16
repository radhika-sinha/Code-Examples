/*************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA2
 * Graph.h
 * Header file for Graph ADT
 ************************************************************************/

#pragma once

#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -100
#define NIL -1

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

// getSource()
// Returns the source of G
int getSource(Graph G);

// getParent()
// Returns the parent of vertex u
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the source for vertex u
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u);

// getPath()
// Adds the shortest path from the source to u
// to a list if such a path exists, appends NIL
// to the list otherwise
// Pre: getSource()!=NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u);

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

// BFS
// Performs Breadth First Search on a Graph with source s
void BFS(Graph G, int s);
/*** Other operations ***/

// printGraph()
// Prints out the Graph (all adjacency lists) to specified file
void printGraph(FILE* out, Graph G);

