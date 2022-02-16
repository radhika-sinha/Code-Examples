/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA1
 * GraphTest.c
 * Testing for Graph ADT
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main(int argc, char* argv[]){
	if (argc==2){
		printf("hi");
}
	if (argv[1]){
		printf("hello");
}
/*
	//List G = newList();
	Graph G = newGraph(7); 
	if (G==NULL){
		fprintf(stderr, "Cannot call on a NULL Graph Object\n");
		exit(1);
	}

	//size of graph
	Graph A = newGraph(55);
	addEdge(A, 54, 1);
	printf("getSize: should be 1, is %d:", getSize(A));
        addEdge(A, 54, 2);
	printf("getSize: should be 2, is %d:", getSize(A));
        addEdge(A, 54, 3);
	printf("getSize: should be 3, is %d:", getSize(A));
        addEdge(A, 1, 55);
	printf("getSize: should be 4, is %d:", getSize(A));
	printf("\n");

	//fixing list equals
	List A = newList();
	List B = newList();
	prepend(A, 1);
	prepend(B, 1);
	prepend(A, 2);
	prepend(B, 2);
	deleteBack(A);
	deleteBack(B);
	printf("printing Lists A and B below:\n");
	printList(stdout, A);
	printList(stdout, B);
	printf("Length A: %d\n", length(A));
	printf("Length B: %d\n", length(B));
	if (!equals(A,B)){
		printf("does not equal eachother");
	}
	printf("\n\n\n");
	

	//think about numEdges
	//TEST: adding an edge to itself
	//what about adding the same thing more than once?
	addEdge(G, 1, 4);
	//addEdge(G, 4, 4);
	addArc(G, 1, 4);
	addArc(G, 1, 4); //testing repeat
	addEdge(G, 1, 5);
	addEdge(G, 4, 5);
	addEdge(G, 2, 3);
	addEdge(G, 2, 6);
	addEdge(G, 3, 7);
	addEdge(G, 6, 7);
	//addEdge(G, 0, 0);
	//addEdge(G, 2, 7);
	//addEdge(G, 3, 6);
	//addEdge(G, 1, 7);
	//addEdge(G, 0, 0);
	printGraph(stdout,G);
	//makeNull(G);
	//printGraph(stdout,G);
	List L = newList();
	BFS(G,2);
	printf("The distance from 2 to 7 is %d\n", getDist(G,7));
	getPath(L,G,7);
	printList(stdout,L);
	clear(L);
	printf("\n");
	BFS(G,3);
	printf("The distance from 3 to 6 is %d\n", getDist(G,6));
	getPath(L,G,6);
	printList(stdout,L);
	clear(L);
	printf("\n");
	BFS(G,1);
	printf("The distance from 1 to 7 is %d\n", getDist(G,7));
	getPath(L,G,7);
	printList(stdout,L);
	
	//getPath(L,G,7);
	//printList(stdout,L);
	freeList(&L);
	freeGraph(&G);
*/
   return(0);
}


