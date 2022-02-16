/******************************************************************************
 * Radhika Sinha, rasinha
 * 2022 Winter CSE101 PA4
 * ListTest.c
 * Test file for List ADT
 *****************************************************************************/

#include <stdlib.h>
#include "List.h"

int main(){
	//create a new List
	List L = newList();
	int a = 1, b = 2, c = 3, d = 4, e = 5;

	//populate List with pointers to a-d
	//test append
	append(L, &a);
	append(L, &b);
	append(L, &c);

	printf("After appending 1, 2, and 3, List is: ");
	
	//moveFront, index, and moveNext
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");
	
	//test length
	printf("Expected length(L): 3\n");
	printf("Actual length(L): %d\n",length(L));

	//test empty index
	printf("Expected index(L): -1\n");
	printf("Actual index(L): %d\n",index(L));

	//prepend address of e
	prepend(L, &d);
	prepend(L, &e);
	//&e &d &a &b &c
	//5 4 1 2 3
	printf("After prepending 4 and 5, the List is now: ");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");

	//test moveFront()
	moveFront(L);

	//test index after moveFront
	printf("Expected index(L): 0\n");
	printf("Actual index(L): %d\n",index(L));

	//test insertAfter
	insertAfter(L, &e);
	printf("After inserting 5 after front element, List is now: ");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");
	//&e &e &d &a &b &c
	
	//test moveNext()
	moveFront(L);
	moveNext(L);
	moveNext(L);

	//testing get(L)
	printf("**MOVED NEXT TWICE**");
	printf("The cursor should be pointing to element d which is 4\n");
	printf("The cursor is actually pointing to: %d\n",*(int*)get(L));
	printf("The address stored at the cursor is: %p\n",get(L));

	int f = 22;
	//test set()
	set(L, &f);
	//should be &e &e &f &a &b &c
	//..........5  5  22  1  2 3
	printf("After setting the cursor element (index 2) to 22, List is: ");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");

	//test moveBack()
	moveBack(L);
	//cursor should now be at element 5 which is 3
	printf("After moveBack(), the cursor should now be at the last element which is 3.");
	printf("The cursor is actually pointing to: %d\n",*(int*)get(L));
	printf("The address stored at the cursor is: %p\n",get(L));

	//test insertBefore()
	insertBefore(L, &f);
	printf("should be 5 5 22 1 2 22 3\n");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");

	//test deleteFront()
	deleteFront(L);
	printf("should be 5 22 1 2 22 3\n");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");

	//test deleteBack()
	deleteBack(L);
	printf("should be 5 22 1 2 22\n");
	for (moveFront(L); index(L)>=0; moveNext(L)){
		printf("%d ", *(int*)get(L));
	}
	printf("\n");

	//test movePrev()
	moveBack(L);
	movePrev(L);

	//test delete()
	moveFront(L);
	delete(L);

	//test clear()
	clear(L);

	//free List
	freeList(&L);
}
