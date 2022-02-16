/*************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA2
 * Graph.c
 * Implementation of Graph ADT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/***structs***/

// private GraphObj type
typedef struct GraphObj {
	int vertices; //order
	int numEdges; //size
	int source;
	List *adjacencyList;
	int *color;
	int *parent;
	int *distance;

} GraphObj;

/*** Constructors-Destructors ***/

// newGraph()
// Returns reference to new empty Graph object
Graph newGraph (int n){
	Graph G;
	G = malloc(sizeof(GraphObj));
	if (G){
		G->vertices = n;
		G->numEdges = 0;
		G->source = NIL;
		G->adjacencyList = (List*) malloc((n+1) * sizeof(List));
		G->color = (int*) calloc((n+1), sizeof(int));
		G->parent = (int*) calloc((n+1), sizeof(int));
		G->distance = (int*) calloc((n+1), sizeof(int));
		if (!G->adjacencyList){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->adjacencyList[i] = newList();
			}
		}
		if (!G->color){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->color[i] = WHITE;
			}
		}
		if (!G->parent){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->parent[i] = NIL;
			}
		}
		if (!G->distance){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->distance[i] = INF;
			}
		}
	}
	return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *G and sets *G to NULL
void freeGraph(Graph* pG){
	if (pG && (*pG) && (*pG)->adjacencyList && (*pG)->color && (*pG)->parent && (*pG)->distance){
		for (int i = 1; i <= (*pG)->vertices; i++){	
			freeList(&(*pG)->adjacencyList[i]);
		}
		free((*pG)->adjacencyList);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free(*pG);
		*pG = NULL;
	}
}

/*** Access functions ***/

// getOrder()
// Returns the order (number of vertices) of Graph G
int getOrder(Graph G){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return G->vertices;
}

// getSize()
// Returns the size (number of edges) of Graph G
int getSize(Graph G){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return G->numEdges;
}

// getSource()
// Returns the source of G
int getSource(Graph G){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	return G->source;
}

// getParent()
// Returns the parent of vertex u
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getParent() out of bounds\n");
		exit(1);
	}
	return G->parent[u];
}

// getDist()
// Returns the distance from the source for vertex u
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getDist() out of bounds\n");
		exit(1);
	}
	return G->distance[u];
}

// getPath()
// Adds the shortest path from the source to u
// to a list if such a path exists, appends NIL
// to the list otherwise 
// Pre: getSource()!=NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	if (getSource(G)==NIL){
		fprintf(stderr, "GraphError: calling getPath() when source is equal to NIL\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getPath() out of bounds\n");
		exit(1);
	}
	if (u==getSource(G)){
		append(L,u);
	}
	else if (G->parent[u] == NIL){
		append(L,NIL);
	}
	else {
		getPath(L, G, G->parent[u]);
		append(L,u);
	}
	return;
}

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, creating a null graph
void makeNull(Graph G){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(1);
	}
	G->numEdges = 0;
	G->source = NIL;
	for (int i = 1; i <= G->vertices; i++){
		clear(G->adjacencyList[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
}

// addEdge()
// inserts a new edge joining u to v (adds u and v to eachothers adjacency lists)
// Pre: u and v must be in range [1, getOrder(G)]
void addEdge(Graph G, int u, int v){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() out of bounds\n");
		exit(1);
	}
	if (length(G->adjacencyList[u])==0){
		append(G->adjacencyList[u],v);
	}
	else {
		moveFront(G->adjacencyList[u]);
		while (v > get(G->adjacencyList[u])){
			moveNext(G->adjacencyList[u]);
			if (index(G->adjacencyList[u])<0){
				break;
			}
		}
		if (index(G->adjacencyList[u])>=0){
			if (v==get(G->adjacencyList[u])){
				return;
			}
			insertBefore(G->adjacencyList[u],v);
		}
		else {
			append(G->adjacencyList[u],v);
		}
	}
	if (length(G->adjacencyList[v])==0){
		append(G->adjacencyList[v],u);
	}
	else {
		moveFront(G->adjacencyList[v]);
		while (u > get(G->adjacencyList[v])){
			moveNext(G->adjacencyList[v]);
			if (index(G->adjacencyList[v])<0){
				break;
			}
		}
		if (index(G->adjacencyList[v])>=0){
			if (u==get(G->adjacencyList[v])){
				return;	
			}
			insertBefore(G->adjacencyList[v],u);
		}
		else {
			append(G->adjacencyList[v],u);
		}
	}
	G->numEdges++;
}

// addArc()
// Inserts a new directed edge from u to v
// Pre: u and v must be in range [1, getOrder(G)]
void addArc(Graph G, int u, int v){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addArc() out of bounds\n");
		exit(1);
	}
	if (length(G->adjacencyList[u])==0){
		append(G->adjacencyList[u],v);
		G->numEdges++;
	}
	else {
		moveFront(G->adjacencyList[u]);
		while (v > get(G->adjacencyList[u])){
			moveNext(G->adjacencyList[u]);
			if (index(G->adjacencyList[u])<0){
				break;
			}
		}
		if (index(G->adjacencyList[u])>=0){
			if (v!=get(G->adjacencyList[u])){
				insertBefore(G->adjacencyList[u],v);
				G->numEdges++;
			}
		}
		else {
			append(G->adjacencyList[u],v);
			G->numEdges++;
		}
	}
}

// BFS
// Performs Breadth First Search on a Graph with source s
void BFS(Graph G, int s){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
		exit(1);
	}
	G->source = s;
	for (int i = 1; i <= G->vertices; i++){
		if (i==s){
			continue;
		}
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List Q = newList();
	append(Q,s);
	while (length(Q)!=0){
		int x = front(Q);
		deleteFront(Q);
		moveFront(G->adjacencyList[x]);
		while (index(G->adjacencyList[x])>-1){
			if (G->color[get(G->adjacencyList[x])] == WHITE){
				G->color[get(G->adjacencyList[x])] = GRAY;
				G->distance[get(G->adjacencyList[x])] = G->distance[x]+1;
				G->parent[get(G->adjacencyList[x])] = x;
				append(Q,get(G->adjacencyList[x]));
			}
			moveNext(G->adjacencyList[x]);
		}
		G->color[x] = BLACK;
	}
	freeList(&Q);
}

/*** Other operations ***/

// printGraph()
// Prints out the Graph (all adjacency lists) to specified file
void printGraph(FILE* out, Graph G){
	for (int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ",i);
		printList(out, G->adjacencyList[i]);
		fprintf(out,"\n");
	}
}
