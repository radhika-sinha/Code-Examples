/*************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA3
 * Graph.c
 * Implementation of Graph ADT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

//private function definition
static int visit (Graph G, List S, int u, int *time);

/***structs***/

// private GraphObj type
typedef struct GraphObj {
	int vertices; //order
	int numEdges; //size
	List *adjacencyList;
	int *color;
	int *discover;
	int *finish;
	int *parent;

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
		G->adjacencyList = (List*) malloc((n+1) * sizeof(List));
		G->color = (int*) calloc((n+1), sizeof(int));
		G->discover = (int*) calloc((n+1), sizeof(int));
		G->finish = (int*) calloc((n+1), sizeof(int));
		G->parent = (int*) calloc((n+1), sizeof(int));
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
		if (!G->discover){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->discover[i] = UNDEF;
			}
		}
		if (!G->finish){
			free(G);
			G = NULL;
		}
		else {
			for (int i = 1; i < n+1; i++){
				G->finish[i] = UNDEF;
			}
		}
	}
	return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *G and sets *G to NULL
void freeGraph(Graph* pG){
	if (pG && (*pG) && (*pG)->adjacencyList && (*pG)->color && (*pG)->parent && (*pG)->discover && (*pG)->finish){
		for (int i = 1; i <= (*pG)->vertices; i++){	
			freeList(&(*pG)->adjacencyList[i]);
		}
		free((*pG)->adjacencyList);
		free((*pG)->color);
		free((*pG)->discover);
		free((*pG)->finish);
		free((*pG)->parent);
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

// getDiscover()
// Returns the source of G
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(1);
	}
	return G->discover[u];
}

// getFinish()
// Returns the finish time of vertex u
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(1);
	}
	return G->finish[u];
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
	for (int i = 1; i <= G->vertices; i++){
		clear(G->adjacencyList[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
}

// addEdge()
// inserts a new edge joining u to v 
// (adds u and v to eachothers adjacency lists)
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

// DFS
// Performs Depth First Search on a Graph with List S
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S) { 
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
		exit(1);
	}
	if (length(S)!=getOrder(G)){
		fprintf(stderr, "Graph Error: cannot call DFS on Graph G when the length of S is unequal to the order of G\n");
		}
	for (int i = 1; i <= G->vertices; i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	int time = 0;
	List C = copyList(S);
	clear(S);
	while (length(C)!=0){
		if (G->color[front(C)] == WHITE){
			time = visit(G, S, front(C), &time); //double check
		}
		deleteFront(C);
	}
	freeList(&C);
}

//visit()
//helper function for DFS
int visit (Graph G, List S, int u, int *time){
	if (G==NULL){
		fprintf(stderr, "Graph Error: calling visit on NULL Graph reference\n ");
	}
	G->discover[u] = ++(*time);
	G->color[u] = GRAY;
	moveFront(G->adjacencyList[u]);
	while (index(G->adjacencyList[u])>=0){
		if (G->color[get(G->adjacencyList[u])] == WHITE) {
			G->parent[get(G->adjacencyList[u])] = u;
			visit(G, S, get(G->adjacencyList[u]), time);
		}
		moveNext(G->adjacencyList[u]);
	}
	G->color[u] = BLACK;
	G->finish[u] = ++(*time);
	prepend(S,u);
	return *time;
}

/*** Other operations ***/

// transpose()
// ...
Graph transpose(Graph G){
	Graph tG = newGraph(G->vertices);
	for (int i = 1; i <= tG->vertices; i++){
		moveFront(G->adjacencyList[i]);
		while (index(G->adjacencyList[i])>=0){
			addArc(tG, get(G->adjacencyList[i]), i);
			moveNext(G->adjacencyList[i]);
		}
	}
	return tG;
}

// copyGraph()
// Copies...
Graph copyGraph(Graph G){
	Graph cG = newGraph(G->vertices);
	cG->numEdges = G->numEdges;
	for (int i = 1; i <= cG->vertices; i++){
		cG->parent[i] = G->parent[i];
		cG->discover[i] = G->discover[i];
		cG->finish[i] = G->finish[i];
		freeList(&(cG->adjacencyList[i]));
		cG->adjacencyList[i] = copyList(G->adjacencyList[i]);
	}
	return cG;
}

// printGraph()
// Prints out the Graph (all adjacency lists) to specified file
void printGraph(FILE* out, Graph G){
	for (int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ",i);
		printList(out, G->adjacencyList[i]);
		fprintf(out,"\n");
	}
}
