#include "Matrix.h"

int main(){
//	Matrix A = newMatrix(100);
//	Matrix B = newMatrix(10);

/*changeEntry(A, 1, 1, -4);
    changeEntry(A, 1, 2, -2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 5, 4);
    changeEntry(A, 2, 1, -2);
    changeEntry(A, 3, 1, 2);
    changeEntry(A, 2, 2, -2);
    changeEntry(A, 3, 3, 0);
    Matrix pC = diff(A, A);
	printf("**PRINTING A**\n");
	printMatrix(stdout,A);
	printf("**PRINTING MATRIX pC: A-A**\n");
	printMatrix(stdout,pC);
    if (NNZ(pC) != 0 || NNZ(A) != 6)
      printf("failed 1\n");
changeEntry(A, 1, 1, 1);
    changeEntry(A, 2, 2, 1);
    changeEntry(A, 3, 3, 1);
    Matrix pC = product(A, A);
    if (NNZ(pC) != 3)
      printf("failed 1\n");
    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 3);
    changeEntry(A, 2, 1, 4);
    changeEntry(A, 2, 2, 5);
    changeEntry(A, 2, 3, 6);
    changeEntry(A, 3, 1, 7);
    changeEntry(A, 3, 2, 8);
    changeEntry(A, 3, 3, 9);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 2, 2, 1);
    Matrix pD = product(A, B);
	printf("**PRINTING A**\n");
	printMatrix(stdout,A);
	Matrix T = transpose(B);
	printf("**PRINTING TRANSPOSE(B)**\n");
	printMatrix(stdout,T);
	printf("**PRINTING pD**\n");
	printMatrix(stdout,pD);
    if (NNZ(pD) != 6)
      printf("failed 2\n");;
    printf("passed");
	Matrix G = newMatrix(10);
	changeEntry(G, 1, 1, 4);
  	changeEntry(G, 1, 2, 2);	
	changeEntry(G, 1, 3, 0);
	changeEntry(G, 2, 1, 2);
	changeEntry(G, 3, 1, 0);
	changeEntry(G, 2, 2, 2);
	changeEntry(G, 3, 3, 0);
	Matrix B = newMatrix(10);
	changeEntry(B, 1, 1, -4);
	changeEntry(B, 1, 2, 0);
	changeEntry(B, 2, 1, 0);
	changeEntry(B, 2, 2, -2);
	changeEntry(B, 2, 4, 2);
	changeEntry(B, 3, 1, 0);
	changeEntry(B, 3, 2, 2);
	changeEntry(B, 7, 8, 5);
	Matrix W = sum (G, B);
	printf("**PRINTING MATRIX G**\n");
	printMatrix(stdout,G);
	printf("**PRINTING MATRIX B**\n");
	printMatrix(stdout,B);
	printf("**PRINTING MATRIX W: G+B**\n");
	printMatrix(stdout,W);
	printf("NNZ should be 4:  %d\n",NNZ(G));	
	printf("NNZ should be 5:  %d\n",NNZ(W));	
	Matrix M = newMatrix(60);
	Matrix L = newMatrix(60);
	printf("size of Matrix M is: %d\n",size(M));
	changeEntry(M, 2, 3, 0.0);
	changeEntry(M, 1, 1, 1.0);
	changeEntry(M, 1, 1, 5.0);
	changeEntry(M, 1, 2, 2.0);
	changeEntry(M, 4, 1, 4.0);
	changeEntry(M, 4, 1, 13.5);
	changeEntry(M, 4, 1, 0);
	changeEntry(M, 1, 1, 5.0);
	changeEntry(M, 1, 2, 0);
	changeEntry(M, 1, 10, 3.0);
	changeEntry(M, 1, 20, 4.0);
	changeEntry(M, 1, 50, -1.0);
	changeEntry(M, 1, 60, 2.0);
	changeEntry(L, 1, 15, 4.0);
	changeEntry(L, 1, 25, 5.0);
	changeEntry(L, 1, 50, 3.0);
	changeEntry(L, 1, 55, 1.0);
	changeEntry(M, 2, 1, 5.0);
	changeEntry(L, 2, 1, 5.0);
	Matrix sM = scalarMult(2,M);
	Matrix S = sum(M,L);
	Matrix D = diff(M,L);
	Matrix C = copy(M);
	if (equals(C,M)){
		printf("Yes, C == M\n");
	}
	if (!equals(C,M)){
		printf("C != M but this is the wrong answer\n");
	}
	if (equals(C,L)){
		printf("C == L but this is the wrong answer\n");
	}
	if (!equals(C,L)){
		printf("C != L (correct)\n");
	}
	
	Matrix T = transpose(M);
	Matrix TT = transpose(T);
	Matrix P = product(L, T);
	makeZero(P);
	//should test with more than one row as well
	printf("**MATRIX M**\n");
	printMatrix(stdout, M);
	printf("**MATRIX sM**\n");
	printMatrix(stdout, sM);
	printf("**MATRIX C**\n");
	printMatrix(stdout, C);
	printf("**MATRIX TT**\n");
	printMatrix(stdout, TT);
	printf("**MATRIX T**\n");
	printMatrix(stdout, T);
	printf("**MATRIX L**\n");
	printMatrix(stdout, L);
	printf("**MATRIX P**\n");
	printMatrix(stdout, P);
	printf("**MATRIX P after make Zero**\n");
	printMatrix(stdout, P);
	printf("**MATRIX S**\n");
	printMatrix(stdout, S);
	printf("**MATRIX D**\n");
	printMatrix(stdout, D);
	freeMatrix(&M);
	freeMatrix(&L);
	freeMatrix(&S);
	freeMatrix(&D);
	*/
}
