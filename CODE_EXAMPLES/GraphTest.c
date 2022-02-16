/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA3
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

//newGraph
Graph G = newGraph(8);

//addArc
addArc(G, 1, 2);
addArc(G, 2, 3);
addArc(G, 2, 5);
addArc(G, 2, 6);
addArc(G, 3, 4);
addArc(G, 3, 7);
addArc(G, 4, 3);
addArc(G, 4, 8);
addArc(G, 5, 1);
addArc(G, 5, 6);
addArc(G, 6, 7);
addArc(G, 7, 6);
addArc(G, 7, 8);
addArc(G, 8, 8);

//printGraph
printf("***PRINTING GRAPH***\n");
printGraph(stdout, G);

//getOrder
printf("Order: %d\n", getOrder(G));

//getSize
printf("Size: %d\n", getSize(G));

//getParent
printf("Parent of 3: %d\n", getParent(G,3));

//getDiscover
printf("Discover of 3: %d\n", getDiscover(G,3));

//getFinish
printf("Finish of 3: %d\n", getFinish(G,3));

//copyGraph
//currently having memory leaks in the newList part of copyGraph
Graph cG = copyGraph(G);

//print copyGraph
printf("\n\n***PRINTING COPYGRAPH***\n");
printGraph(stdout, cG);

printf("Order of copyGraph: %d\n", getOrder(cG));
printf("Size of copyGraph: %d\n", getSize(cG));
printf("Parent of 3: %d\n", getParent(cG,3));
printf("Discover of 3: %d\n", getDiscover(cG,3));
printf("Finish of 3: %d\n", getFinish(cG,3));

//transpose
Graph tG = transpose(G);

//print transposeGraph
printf("\n\n***PRINTING TRANSPOSEGRAPH***\n");
printGraph(stdout, tG);

printf("\n\nOrder of transposeGraph: %d\n", getOrder(tG));
printf("Size of transposeGraph: %d\n", getSize(tG));
printf("Parent of 3: %d\n", getParent(tG,3));
printf("Discover of 3: %d\n", getDiscover(tG,3));
printf("Finish of 3: %d\n", getFinish(tG,3));

//run valgrind and see if all memory is freed
freeGraph(&G);
freeGraph(&cG);
freeGraph(&tG);	
   return(0);
}


