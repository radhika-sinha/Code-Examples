/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA3
 * FindComponents.c
 * Main code for FindComponents, client for graph ADT
 * ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Matrix.h"

int main(int argc, char**argv) {

	FILE *infile, *outfile;
	
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


   	int n, a, b;

	fscanf(infile, "%d %d %d", &n, &a, &b);

	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);

	int i, j;
	double x;

	while(!feof(infile) && a!=0){
		fscanf(infile, "%d %d %lf", &i, &j, &x);
		changeEntry(A,i,j,x);
		a--;
	}
	
	while(!feof(infile) && b!=0){
		fscanf(infile, "%d %d %lf", &i, &j, &x);
		changeEntry(B,i,j,x);
		b--;
	}
	
	a = NNZ(A);
	b = NNZ(B);

	fprintf(outfile,"A has %d non-zero entries:\n",a);
	printMatrix(outfile,A);
	fprintf(outfile,"\n");

	fprintf(outfile,"B has %d non-zero entries:\n",b);
	printMatrix(outfile,B);
	fprintf(outfile,"\n");
	
	fprintf(outfile,"(1.5)*A =\n");
	Matrix sM = scalarMult(1.5,A);
	printMatrix(outfile, sM);
	fprintf(outfile,"\n");
	
	fprintf(outfile,"A+B =\n");
	Matrix S = sum(A,B);
	printMatrix(outfile, S);
	fprintf(outfile,"\n");

	fprintf(outfile,"A+A =\n");
	S = sum(A,A);
	printMatrix(outfile, S);
	fprintf(outfile,"\n");

	fprintf(outfile,"B-A =\n");
	Matrix D = diff(B,A);
	printMatrix(outfile,D);
	fprintf(outfile,"\n");
	
	fprintf(outfile,"A-A =\n");
	D = diff(A,A);
	printMatrix(outfile,D);
	fprintf(outfile,"\n");
	
	fprintf(outfile,"Transpose(A) =\n");
	Matrix T = transpose(A);
	printMatrix(outfile,T);
	fprintf(outfile,"\n");
	
	fprintf(outfile,"A*B =\n");
	Matrix P = product(A,B);
	printMatrix(outfile,P);
	fprintf(outfile,"\n");

	fprintf(outfile,"B*B =\n");
	P = product(B,B);
	printMatrix(outfile,P);
	fprintf(outfile,"\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&sM);
	freeMatrix(&S);
	freeMatrix(&D);
	freeMatrix(&T);
	freeMatrix(&P);
	return(0);
}
