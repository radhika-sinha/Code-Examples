/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA4
 * List.h
 * Header file for List ADT
 *****************************************************************************/

#pragma once

#include <stdio.h>
#include <stdbool.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;
typedef void* ListElement;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object
List newList();

// freeList()
// Frees all heap memory associated with List *L, and sets *L to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L);

// front()
// Returns front element of L.
// Pre: length()>0
ListElement front(List L);

// back()
// Returns back element of L.
// Pre: length()>0
ListElement back(List L);

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
ListElement get(List L);

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, ListElement x);

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L); 

// moveBack();
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveBack(List L);

// movePrev();
// If cursor is defined and not at front, move cursor one 
// step toward the front of L; if cursor is defined and at 
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined 
// do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, ListElement x);

// append()
// Insert new element into L. If L is non-empty, 
// insertion takes place after back element.
void append(List L, ListElement x);

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x); 

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x); 

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L);

// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
// concatList(List A, List B);
