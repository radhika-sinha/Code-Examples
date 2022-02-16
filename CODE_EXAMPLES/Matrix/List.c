/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA4
 * List.c
 * Implementation file for List ADT
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
	ListElement data;
	Node next;
	Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int cursorIndex;
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. 
// Initializes next, prev, and data fields.
Node newNode(ListElement data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = N->prev = NULL;
	return N;
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object
List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->cursorIndex = -1;
	L->length = 0;
	return L;
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL) {
		while(length(*pL)!=0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return L->length;
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L){
	return L->cursorIndex;
}

// front()
// Returns front element of L.
// Pre: length()>0
ListElement front(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling front() on an empty List\n");
		exit(1);
	}
	return(L->front->data);
}

// back()
// Returns back element of L.
// Pre: length()>0
ListElement back(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling back() on an empty List\n");
		exit(1);
	}
	return(L->back->data);
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
ListElement get(List L){
	if (length(L)==0){
		fprintf(stderr, "List Error: calling get() on an empty List\n");
		exit(1);	
	}
	if (index(L)<0){
		fprintf(stderr, "List Error: calling get() when cursor element is off the end of the list\n");
		exit(1);
	}
	return L->cursor->data;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	int compareLength = length(L);
	for (int i = 0; i < compareLength; i++){
		deleteFront(L);
	}
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, ListElement x){
	if (L==NULL){
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling set() on an empty List\n");
		exit(1);	
	}
	if (index(L)<0){
		fprintf(stderr, "List Error: calling set() when cursor element is off the end of the list\n");
		exit(1);
	}
	L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L)>0){
		L->cursor = L->front;
		L->cursorIndex = 0;
	}
}

// moveBack();
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if (length(L)>0){
		L->cursor = L->back;
		L->cursorIndex = length(L)-1;
	}
}

// movePrev();
// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if (index(L)>0){
		L->cursor = L->cursor->prev;
		L->cursorIndex--;
	}
	else if (index(L)==0){
		L->cursor = NULL;
		L->cursorIndex = -1;
	}
}

// moveNext()
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if (index(L)==length(L)-1){
		L->cursor = NULL;
		L->cursorIndex = -1;
	}
	else if (index(L)>=0){
		L->cursor = L->cursor->next;
		L->cursorIndex++;
	}
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, ListElement x){
	if (L==NULL){
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(x);
	if (length(L)==0){
		L->front = L->back = N;
	}
	else {
		N->next = L->front;
		L->front->prev = N;
		L->front = L->front->prev;
	}
	L->length++;
	if (index(L)>=0){
		L->cursorIndex++;
	}
}

// append()
// Insert new element into L. If L is non-empty, 
// insertion takes place after back element.
void append(List L, ListElement x){
	if (L==NULL){
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(x);
	if (length(L)==0){
		L->front = L->back = N;
	}
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = L->back->next;
	}
	L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x){
	if (L==NULL){
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
		exit(1);
	}
	if (index(L)<0){
		fprintf(stderr, "List Error: calling insertBefore() when cursor element is off end of list.\n");
		exit(1);
	}
	if(index(L)==0){
		prepend(L,x);
	}
	else{
		Node N = newNode(x);
		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		L->cursor->prev = N;
		N->next = L->cursor;
		L->length++;
		L->cursorIndex++;
	}
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x){
	if (L==NULL){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
		exit(1);
	}
	if (index(L)<0){
		fprintf(stderr, "List Error: calling insertAfter() when cursor element is off end of list.\n");
		exit(1);
	}
	Node N = newNode(x);
	if(index(L)==length(L)-1){
		append(L,x);
	}
	else{
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		L->cursor->next = N;
		N->prev = L->cursor;
		L->length++;
	}
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
		exit(1);
	}
	Node N = NULL;
	N = L->front;
	if (length(L)>1){
		L->front = L->front->next;
		L->cursorIndex--;
		if (index(L)==0){
			L->cursor = NULL;
		}
	}
	else {
		L->front = L->back = L->cursor = NULL;
		L->cursorIndex = -1;
	}
	L->length--;
	freeNode(&N);
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
		exit(1);
	}
	Node N = NULL;
	N = L->back;
	if (length(L)>1){
		L->back = L->back->prev;
		if (index(L)==length(L)-1){
			L->cursor = NULL;
			L->cursorIndex = -1;;
		}
		L->back->next = NULL;
	}
	else {
		L->front = L->back = L->cursor = NULL;
		L->cursorIndex = -1;
	}
	L->length--;
	freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(1);
	}
	if (length(L)==0){
		fprintf(stderr, "List Error: calling delete() on an empty List\n");
		exit(1);
	}
	if (index(L)<0){
		fprintf(stderr, "List Error: calling delete() when cursor element is off end of list.\n");
		exit(1);
	}
	if(index(L)==0){
		deleteFront(L);
	}
	else if (index(L)==length(L)-1){
		deleteBack(L);
	}
	else{
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		L->length--;
		freeNode(&N);
	}
	L->cursor = NULL;
	L->cursorIndex = -1;
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
	if (L==NULL){
		fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
		exit(1);
	}
	Node iter = L->front;
	for (int i = 0; i < length(L); i++){
		fprintf(out, "%p ",iter->data);
		iter = iter->next;
	}
}

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
// concatList(List A, List B);

