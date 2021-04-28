//Name	: Claudio Sangeroki
//ID 	: 1677403
//PA1
//Doubly Linked List ADT

#include<stdio.h>
#include<stdlib.h>

#include "List.h"

typedef struct NodeObj
{
	struct NodeObj* prev;
	int data;
	struct NodeObj* next;

}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{

	Node front;
	Node back;
	Node curr;

	int length;
	int index;

}ListObj;


Node newNode(int data)
{
    Node N = NULL;
    N = malloc(sizeof(NodeObj));
 
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return (N);
}

void freeNode(Node* pN)
{

    if (pN != NULL && *pN != NULL)
    {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) {
	List L;

	L = malloc(sizeof(ListObj));

	L->front = NULL;
	L->back = NULL;
	L->curr = NULL;

	L->index = -1;
	L->length = 0;

	return(L);
}


void freeList(List* pL){

    if (pL != NULL && *pL!= NULL) 
    { 
      while (length(*pL) > 0)
      {            
        
          deleteFront(*pL);
      }
   
      free(*pL);
      *pL = NULL;
    }
}

	// Access functions -----------------------------------------------------------
void* length(List L){

    if (L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }

	return (L->length);
}

void* index(List L){

	if (L == NULL)
    {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }
    return (L->index);
}

void* front(List L){
	    if (L == NULL)
    {
        printf("Error on front(). L is NULL\n");
        exit(1);
    }

    if (length(L) < 1)
    { 
    	printf("Error on front(). Length of list is 0 or less\n"); 
    }

    return (L->front->data);
} // Returns front element of L. Pre: length()>0

void* back(List L){ // Returns back element of L. Pre: length()>0
    if (L == NULL)
    {
        printf("Error on back(). L is NULL\n");
        exit(1);
    }

    if (length(L) < 1)
    { printf("Error on back(). Length of list is 0 or less\n"); }

    return (L->back->data);
}

void* get(List L){

	if (L == NULL)
    {
        printf("Error on get(). List is NULL\n");
        exit(1);
    }

    if (length(L) <= 0)
    { 
    	printf("Error on get(). List is empty\n"); 
    }

    if (L->curr == NULL)
    { 
    	printf("Error on get(). current is NULL\n"); 
    }

    return (L->curr->data);


} // Returns curr element of L. Pre: length()>0, index()>=0

void* equals(List A, List B){
	
   	int eq = 0;
   	Node N = NULL;
  	Node M = NULL;

   	if( A==NULL || B==NULL ){
    	printf("List Error: calling equals() on NULL List reference\n");
      	exit(1);
   	}

   	if (A->length != B->length){
   		return 0;
   	}

   	eq = ( A->length == B->length );
   	N = A->front;
   	M = B->front;
   	while( eq && N!=NULL){
    	eq = (N->data==M->data);
    	N = N->next;
    	M = M->next;
   	}
   	return eq;


} // Returns true (1) iff Lists A and B are in same

							 // state, and returns false (0) otherwise.
	// Manipulation procedures ----------------------------------------------------
void clear(List L){

	L->front = NULL;
	L->back = NULL;
	L->curr = NULL;
	L->length = 0;
	L->index = -1;

}// Resets L to its original empty state.

void moveFront(List L){

    if (L == NULL)
    {
        printf("List Error: calling moveFront() on a NULL List reference\n");
        exit(1);
    }

	if(L->length > 0){
		L->curr = L->front;
		L->index = 0;
	}
}// If L is non-empty, sets curr under the front element,
							 // otherwise does nothing.

void moveBack(List L){

    if (L == NULL)
    {
        printf("List Error: calling moveBack() on a NULL List reference\n");
        exit(1);
    }

	if(L->length > 0){
		L->curr = L->back;
		L->index = L->length-1;
	}
} // If L is non-empty, sets curr under the back element,
							 // otherwise does nothing.

void movePrev(List L){

    if (L == NULL)
    {
        printf("List Error: calling movePrev() on a NULL List reference\n");
        exit(1);
    }

	if(L->curr == L->front){
		L->curr = NULL;
		L->index = -1;
	}	
	else {
		L->curr = L->curr->prev;
		L->index = L->index-1;
	}
} // If curr is defined and not at front, move curr one
							// step toward the front of L; if curr is defined and at
	 						// front, curr becomes undefined; if curr is undefined
	 						// do nothing
void moveNext(List L){

	    if (L == NULL)
    {
        printf("List Error: calling moveNext() on a NULL List reference\n");
        exit(1);
    }

	if(L->curr == L->back){
		L->curr = NULL;
		L->index = -1;
	}	
	else {
		L->curr = L->curr->next;
		L->index++;
	}

} // If curr is defined and not at back, move curr one
							// step toward the back of L; if curr is defined and at
							// back, curr becomes undefined; if curr is undefined
							// do nothing
void prepend(List L, int data){

	if (L == NULL)
    {
        printf("List Error: calling prepend() on a NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);

    if(L->length == 0){
    	L->front = N;
    	L->back = N;
    	L->curr = L->front;
    }
    else{
    	L->front->prev = N;
    	N->next = L->front;
    	L->front = N;
    	L->index++;
    }
    L->length++;
} // Insert new element into L. If L is non-empty,
	 								// insertion takes place before front element.
void append(List L, int data){
	if (L == NULL)
    {
        printf("List Error: calling append() on a NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);

    if(L->length == 0){
    	L->front = N;
    	L->back = N;
    	L->curr = L->back;
    }
    else{
    	L->back->next = N;
    	N->prev = L->back;
    	L->back = N;
    	N->next = NULL;
    }
    L->length++;

}// Insert new element into L. If L is non-empty,
	 							// insertion takes place after back element.

void insertBefore(List L, int data){
	 if (L == NULL)
    {
        printf("List Error: calling insertBefore() on a NULL List reference\n");
        exit(1);
    }
    if (L->curr == NULL)
    {
        printf("List Error: cannot insertBefore()  if curr is undefined\n");
    }
    if (L->curr == L->front)
    {
        prepend(L, data);
    }
    else {
      	Node N = newNode(data);

        N->prev = L->curr->prev;
        N->next = L->curr;

        L->curr->prev->next = N;
        L->curr->prev = N;

        L->index++;
        L->length++;
    }
} // Insert new element before curr.
	 									// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if (L == NULL)
    {
        printf("List Error: calling insertAfter() on a NULL List reference\n");
        exit(1);
    }
    if (L->curr == NULL)
    {
        printf("List Error: cannot insertAfter()  if curr is undefined\n");
    }
    if (L->curr == L->back)
    {
        append(L, data);
    }
    else {
    	Node N = newNode(data);

        N->prev = L->curr;
        N->next = L->curr->next;

        L->curr->next->prev = N;
        L->curr->next = N;

        L->length++;
    }
} // Insert new element before curr.
 									// Pre: length()>0, index()>=0
void deleteFront(List L){
	if (L == NULL)
    {
        printf("List Error: calling deleteFront() on a NULL List reference\n");
        exit(1);
    }

    if (length(L) <= 0)
    {
        printf("List Error: cannot deleteFront() empty List\n");
        exit(1);
    }

    if (L->length == 1)
      	{
        Node N = L->front;

        freeNode(&N);
 
        L->curr = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length--;
     }
     else 
     {
        Node N = L->front;
        L->front = L->front->next;

        L->front->prev = NULL;

        if (L->curr != NULL)
        {
            L->index--;
        }
        freeNode(&N);
        L->length--;
    }

}
// Delete the front element. Pre: length()>0
void deleteBack(List L){
	if (L == NULL)
    {
        printf("List Error: calling deleteBack() on a NULL List reference\n");
        exit(1);
    }

    if (length(L) <= 0)
    {
        printf("List Error: cannot deleteBack() empty List\n");
        exit(1);
    }

    if (L->length == 1)
      	{
        Node N = L->back;

        freeNode(&N);
 
        L->curr = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length--;
     }
     else 
     {
        Node N = L->back;
        L->back = L->back->prev;

        L->back->next = NULL;

        if (L->index == L->length-1)
        {
            L->index = -1;
        }
        freeNode(&N);
        L->length--;
    }
}// Delete the back element. Pre: length()>0
void delete(List L){
	if (L == NULL)
    {
       	printf("List Error: cannot delete() on NULL List reference\n");
    	exit(1);
    }
    if (length(L) <= 0)
    {
    	printf("List Error: cannot delete() empty List");
       	exit(1);
    }
    if (L->curr == NULL)
    {
        printf("List Error: cannot delete() on undefined curr");
        exit(1);
    }
    if (L->curr == L->front)
    {
        deleteFront(L);
    }
    else if (L->curr == L->back)
    {
        deleteBack(L);
    }else{
    	Node N = L->curr;
        L->curr->prev->next = L->curr->next;
        L->curr->next->prev = L->curr->prev;
        freeNode(&N);
        L->length--;
    }
    L->index = -1;
    
} // Delete curr element, making curr undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
	Node N = NULL;
    if(L == NULL) 
    {
        fprintf(stderr, "List error: printList() called on NULL List reference\n");
        exit(1);
    }
    for (N = L->front; N != NULL; N= N->next) 
    {
        fprintf(out, "%d", N->data);
        fprintf(out, " ");
    }
} // Prints to the file pointed to by out, a
 // string representation of L consisting
// of a space separated sequence of integers,
// with front on left.


