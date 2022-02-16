/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA1
 * FindPath.c
 * Main code for FindPath, client for graph ADT
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
		addEdge(G,u,v);
		fscanf(infile, "%d %d", &u, &v);
	}

	printGraph(outfile, G);

	fprintf(outfile, "\n");

	fscanf(infile, "%d %d", &u, &v);
	
	List Path = newList();

	while(!feof(infile) && u!=0 && v!=0){
		BFS(G, u);
		if (getDist(G,v)==INF){
			fprintf(outfile, "The distance from %d to %d is infinity\n", u, v);
			fprintf(outfile, "No %d-%d path exists\n", u, v);
			fprintf(outfile, "\n");
		}
		else {
			fprintf(outfile, "The distance from %d to %d is %d\n", u, v, getDist(G,v));
			getPath(Path, G, v);
			fprintf(outfile, "A shortest %d-%d path is: ", u, v);
			printList(outfile, Path);
			fprintf(outfile, "\n");
			clear(Path);
			fprintf(outfile,"\n");
		}	
		fscanf(infile, "%d %d", &u, &v);
	}

	fclose(infile);
	fclose(outfile);
	
	freeList(&Path);

	return(0);
}
