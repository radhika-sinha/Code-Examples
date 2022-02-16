/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA4
 * Matrix.h
 * Header file for Matrix ADT
 *****************************************************************************/

#include<stdlib.h>

#include "Matrix.h"
#include "List.h"

//defining helper functions
//helper for sum/diff
List addList(List L, List M, int sign);

//helper for product
double vectorDot(List L, List M);

// private Entry type
typedef struct EntryObj* Entry; //double check

// private Entry type
typedef struct EntryObj {
	int column;
	double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
	List *rows;
	int size;
} MatrixObj;

//Constructors-Destructors

// newEntry()
// Returns reference to new Entry object
// Initializes column and value fields
Entry newEntry(int column, double value){
	Entry E = malloc(sizeof(EntryObj));
	E->column = column;
	E->value = value;
	return E;
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
void freeEntry(Entry* pE){
	if (pE!=NULL && *pE!=NULL){
		free(*pE);
		*pE = NULL;
	}
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->rows = (List*) malloc ((n+1) * sizeof(List));
	if (!M->rows){
		free(M);
		M = NULL;
	}
	else{
		for (int i = 1; i < n+1; i++){
			M->rows[i] = newList();
		}
	}
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM){
	if (pM!=NULL && *pM!=NULL && (*pM)->rows) {
		for (int i = 1; i <= (*pM)->size; i++){
			moveFront((*pM)->rows[i]);
			while (index((*pM)->rows[i])>=0){
				Entry E = (Entry)get((*pM)->rows[i]);
				freeEntry(&E);				
				moveNext((*pM)->rows[i]);
			}
			freeList(&((*pM)->rows[i]));
		}
		free((*pM)->rows);
		free((*pM));
		*pM = NULL;
	}
}

// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if (M==NULL){
		fprintf(stderr,"Matrix Error: calling size() on NULL Matrix reference.");
		exit(1);
	}
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ (Matrix M){
	int nonZero = 0;
	for (int i = 1; i <= size(M); i++){
		moveFront(M->rows[i]);
		while (index(M->rows[i])>=0){
			nonZero++;
			moveNext(M->rows[i]);
		}
	}
	return nonZero;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if (size(A)!=size(B)){
		return 0;
	}
	else {
		for (int i = 1; i <= size(A); i++){
			moveFront(A->rows[i]);
			moveFront(B->rows[i]);
			while (index(A->rows[i])>=0 && index(B->rows[i])>=0){
				if (((Entry)get(A->rows[i]))->column != ((Entry)get(B->rows[i]))->column || ((Entry)get(A->rows[i]))->value != ((Entry)get(B->rows[i]))->value){
					return 0;
				}
				moveNext(A->rows[i]);
				moveNext(B->rows[i]); 
			}
			if (index(A->rows[i])>=0 && index(B->rows[i]) < 0){
				return 0;
			}
			if (index(B->rows[i])>=0 && index(A->rows[i]) < 0){
				return 0;
			}
		}
		return 1;
	}
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	for (int i = 1; i <= size(M); i++){
		for (int j = 1; j <= size(M); j++) {
			changeEntry(M, i, j, 0.0);
		}
	}
}

// changeEntry()
// changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if (i < 1 || i > size(M) || j < 1 || j > size(M)){
		fprintf(stderr, "Matrix Error: calling changeEntry() out of bounds");
		exit(1);
	}
	moveFront(M->rows[i]);
	while (index(M->rows[i])>=0 && ((Entry)get(M->rows[i]))->column<j){
		moveNext(M->rows[i]);
	}	
	if (index(M->rows[i])<0){
		if (x!=0.0){
			Entry E = newEntry(j,x);
			append(M->rows[i],E);
		}
	}
	else {
		if (((Entry)get(M->rows[i]))->column==j){
			if(x==0.0){
				delete(M->rows[i]);
			}
			else {
				Entry E = (Entry)get(M->rows[i]);
				freeEntry(&E);
				E = newEntry(j,x);
				set(M->rows[i],E);
			}
		}
		else {
			if (x!=0.0){
				Entry E = newEntry(j,x);
				insertBefore(M->rows[i],E);
			}
		}
	}
}

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	Matrix C = newMatrix(size(A));
	Entry E;
	int column;
	double value;
	for (int i = 1; i <= size(C); i++){
		moveFront(A->rows[i]);
		while (index(A->rows[i])>=0){
			column = ((Entry)get(A->rows[i]))->column;
			value = ((Entry)get(A->rows[i]))->value;
			E = newEntry(column,value);
			append(C->rows[i],E);
			moveNext(A->rows[i]);
		}
	}
	return C;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	Matrix T = newMatrix(size(A));
	Entry E;
	int row;
	double value;
	for (int i = 1; i <= size(T); i++){
		moveFront(A->rows[i]);
		while (index(A->rows[i])>=0){
			row = ((Entry)get(A->rows[i]))->column;
			value = ((Entry)get(A->rows[i]))->value;
			E = newEntry(i,value);
			append(T->rows[row],E);
			moveNext(A->rows[i]);
		}
	}
	return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	Matrix C = newMatrix(size(A));
	Entry E;
	int column;
	double value;
	for (int i = 1; i <= size(C); i++){
		moveFront(A->rows[i]);
		while (index(A->rows[i])>=0){
			column = ((Entry)get(A->rows[i]))->column;
			value = x * ((Entry)get(A->rows[i]))->value;
			E = newEntry(column,value);
			append(C->rows[i],E);
			moveNext(A->rows[i]);
		}
	}
	return C;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
	if (size(A)!=size(B)){
		fprintf(stderr, "Matrix Error: calling sum() on two matrices of unequal size.");
		exit(1);
	}
	Matrix S = newMatrix(size(A));
	Matrix C = copy(B);
	for (int i = 1; i <= size(S); i++) {
		freeList(&(S->rows[i]));
		S->rows[i] = addList(A->rows[i],C->rows[i],1);
	}
	freeMatrix(&C);
	return S;	
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if (size(A)!=size(B)){
		fprintf(stderr, "Matrix Error: calling sum() on two matrices of unequal size.");
		exit(1);
	}
	Matrix D = newMatrix(size(A));
	Matrix C = copy(B);
	for (int i = 1; i <= size(D); i++) {
		freeList(&(D->rows[i]));
		D->rows[i] = addList(A->rows[i],C->rows[i],-1);
	}
	freeMatrix(&C);
	return D;	
}

// addList()
// Helper function to add/subtract Lists
List addList(List L, List M, int sign){
	List S = newList();
	moveFront(L);
	moveFront(M);
	Entry E;
	while(index(L)>=0 && index(M)>=0){
		if (((Entry)get(L))->column < ((Entry)get(M))->column) {
			//append(S,((Entry)get(L)));
			E = newEntry(((Entry)get(L))->column,((Entry)get(L))->value);
			append(S,E);
			moveNext(L);
		}
		else if (((Entry)get(M))->column < ((Entry)get(L))->column) {
			if (sign>0){
				E = newEntry(((Entry)get(M))->column,((Entry)get(M))->value);
				append(S,E);
				//append(S,((Entry)get(M)));
			}
			else {
				double diff = 0.0 - ((Entry)get(M))->value;
				E = newEntry(((Entry)get(M))->column, diff);
				append(S,E);
			}
			moveNext(M);
		}
		else {
			Entry E;
			if (sign > 0) {
				double sum = ((Entry)get(M))->value + ((Entry)get(L))->value;
				E = newEntry(((Entry)get(L))->column, sum);
				if (sum!=0){
					append(S,E);
				}
			}
			if (sign < 0) {
				double diff = ((Entry)get(L))->value - ((Entry)get(M))->value;
				E = newEntry(((Entry)get(L))->column, diff);
				if (diff!=0){
					append(S,E);
				}
			}
			moveNext(M);
			moveNext(L);
		}		
	}
	while (index(L)>=0){
		E = newEntry(((Entry)get(L))->column,((Entry)get(L))->value);
		append(S,E);
		//append(S,((Entry)get(L)));
		moveNext(L);
	}
	while (index(M)>=0){
		if (sign>0){
			E = newEntry(((Entry)get(M))->column,((Entry)get(M))->value);
			append(S,E);
			//append(S,((Entry)get(M)));
		}
		else {
			double diff = 0.0 - ((Entry)get(M))->value;
			Entry E = newEntry(((Entry)get(M))->column, diff);
			append(S,E);
		}
		moveNext(M);
	}
	return S;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	Matrix P = newMatrix(size(A));
	Matrix T = transpose(B);
	double dot;
	for (int i = 1; i <= size(P); i++) {
		for (int j = 1; j <= size(P); j++){
			dot = vectorDot(A->rows[i],T->rows[j]);
			changeEntry(P,i,j,dot);
		}
	}
	return P;
}	

// vectorDot()
// Computes the vector dot product of two matrix rows
// Private helper function for product
double vectorDot(List L, List M){
	moveFront(L);
	moveFront(M);
	double dot = 0;
	while (index(L)>=0 && index(M)>=0){
		if (((Entry)get(L))->column == ((Entry)get(M))->column){
			dot += ((Entry)(get(L)))->value * ((Entry)(get(M)))->value;
			moveNext(L);
			moveNext(M); 
		}
		else if (((Entry)get(L))->column < ((Entry)get(M))->column){
			moveNext(L);
		}
		else if (((Entry)get(L))->column > ((Entry)get(M))->column){
			moveNext(M);
		}
	}
	return dot;	
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	for (int i = 1; i <= M->size; i++){
		if (length(M->rows[i])!=0){
			fprintf(out,"%d: ",i);
			moveFront(M->rows[i]);
			while (index(M->rows[i])>=0){
				fprintf(out,"(");
				fprintf(out,"%d, ",((Entry)get(M->rows[i]))->column);	
				fprintf(out,"%0.1f",((Entry)get(M->rows[i]))->value);	
				fprintf(out,") ");
				moveNext(M->rows[i]);
			}
			fprintf(out,"\n");
		}
	}
}
