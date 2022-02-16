/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA3
 * FindComponents.c
 * Main code for FindComponents, client for graph ADT
 * ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"

int main(int argc, char**argv) {

	FILE *infile, *outfile;
	int order; //number of vertices
	
	//check command line for correct number of arguments
	if (argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	infile = fopen(argv[1], "r");
		if (infile == NULL){
			printf("Unable to open file %s for reading\n", argv[1]);
			exit(1);
		}

	outfile = fopen(argv[2], "w");
		if (outfile == NULL){
			printf("Unable to open file %s for writing\n", argv[2]);
			exit(1);
		}

	fscanf(infile, "%d",&order);
	Graph G = newGraph(order);

	int u, v = 1;	

	fscanf(infile, "%d %d", &u, &v);

	while(!feof(infile) && u!=0 && v!=0){
		addArc(G,u,v);
		fscanf(infile, "%d %d", &u, &v);
	}
	
	fprintf(outfile, "Adjacency list representation of G:\n");

	printGraph(outfile, G);

	fprintf(outfile, "\n");

	List S = newList(); //empty List to serve as a stack
	
	for (int i = getOrder(G); i > 0; i--){
		prepend(S,i);
	}
	
	DFS(G,S);
	Graph GT = transpose(G);
	DFS(GT, S);

	int count;
	for (moveFront(S);index(S)>=0;moveNext(S)){
		if (getParent(GT, get(S))==NIL){
			count++;
		}
	}

	//what about the case of no strongly connected components?
	fprintf(outfile, "G contains %d strongly connected components:\n",count);

	moveBack(S);
	
	int componentNumber = 0;
	List reverseStack = newList();
	if (count!=0){
		while(index(S)>=0){
			if(index(S)>=0 && getParent(GT,get(S))==NIL){
				prepend(reverseStack,get(S));
				movePrev(S);
				fprintf(outfile,"Component %d: ",++componentNumber);
				printList(outfile,reverseStack);
				fprintf(outfile,"\n");
				clear(reverseStack);
			}
			else {
				prepend(reverseStack,get(S));
				movePrev(S);
			}
		}
	}

	freeList(&S);
	freeList(&reverseStack);
	freeGraph(&G);
	freeGraph(&GT);

	fclose(infile);
	fclose(outfile);
	
	return(0);
}
