//Julia Ni
//juni
//pa2

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs-------------------------------------------------------

// private NodeObj type	
typedef struct NodeObj{
	void* x;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{ //change?
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//helper node function
Node newNode(void* a) {
	Node temp = malloc(sizeof(NodeObj));
	temp->x = a;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

//helper node function
void freeNode(Node *N) {
	if(N != NULL && *N != NULL)
	{
		free(*N);
		*N = NULL;
	}
}
// Constructors and Destructors-------------------------------------

// Creates and returns a new empty List
List newList(void) {
	List a = malloc(sizeof(ListObj));
	a->front = NULL;
	a->back = NULL;
	a->cursor = NULL;
	a->index = -1;
	a->length = 0;
	return a;
}

//frees heap memory associated with *pL, sets *pL to NULL
void freeList(List* pL) {
	if(pL != NULL && *pL != NULL)
	{
		
		Node a = (*pL)->front;
		while(a != NULL) 
		{
			Node temp = a;
			a = a->next;
			//free((temp)->x);
			free(temp);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions---------------------------------------------------------
int length(List L) {
	return L->length;
}

int index(List L) {
	if(L->cursor != NULL)
	{
		return L->index;
	}
	else
	{
		return -1;
	}
}

void* front(List L) {
	if(L->length > 0)
	{
		return (L->front)->x;
	}
	else
	{
		return NULL; // UNDEFINEDDDDD???

	}
}


// Returns back element of L. Pre: length()>0
void* back(List L) {
	if(L->length > 0)
	{
		return (L->back)->x;
	}
	else
	{
		return NULL;
	}
}

// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
	if(L->length > 0 && L->index >= 0)
	{
		return (L->cursor)->x;
	}
	else
	{
		return NULL;
	}
}
 

// Manipulation procedures-----------------------------------
void clear (List L) {
	if(L != NULL && L->length != 0)
	{
		L->front = L->back = L->cursor = NULL;
                L->index = -1;
                L->length = 0;
	}
	
	
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L) {
	if(L != NULL)
	{
		L->cursor = L->front;
		L->index = 0;
	}
}

//If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L) {
	if (L != NULL && L->length != 0)
	{
		L->cursor = L->back;
		L->index = (L->length-1);
	}
}

// If cursor is defined and not at front, move cursor one step toward front of L...
void movePrev(List L) {
	if(L->cursor != NULL && L->cursor != L->front)
	{
		L->cursor = (L->cursor)->prev;
		(L->index)--;
		return;
	}
	if(L->cursor != NULL && L->cursor == L->front)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}
			
}

//If cursor is defined and not at back, move cursor one step toward the back of L...
void moveNext(List L) {
	if(L->cursor != NULL &&  L->cursor->next != NULL)
	{
		L->cursor = (L->cursor)->next;
		(L->index)++;
		return;
	}
	if(L->cursor != NULL && L->cursor->next == NULL)
	{
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	if(L->cursor == NULL)
	{
		//do nothing
	}
}

// Insert new element into L. If L is non-empty, insertion takes place before front element
void prepend(List L, void* x) { //have to adjust for how cursor moves???
	if(L == NULL){
		fprintf(stderr, "in ListADT, prepend, List is NULL");
		exit(1);
	}
	if(L->front == NULL)
	{
		Node temp = newNode(x);
		L->front = temp;
		L->back = temp;
	}
	else
	{
		Node temp = newNode(x);
		temp->next = L->front;
		(L->front)->prev = temp;
		L->front = temp;
	}
	L->length++;
	if(L->index!=-1){
		L->index++;
	}
}

// Insert new element into L. If L is non-empty, insertion takes places after back element
void append(List L, void* x) {

	if(L->front == NULL)
	{
		Node temp = newNode(x);
		L->front = temp;
		L->back = temp;

	}
	else
        {
                Node temp = newNode(x);
                temp->prev = L->back;
                (L->back)->next = temp;
                L->back = temp;
        }
	L->length++;	
}

// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
	if(L == NULL)
	{
		printf("error, L is NULL");
		return;
	}

	if(L->length > 0 && L->index >= 0)
	{
		if(L->length == 1)
        	{
        	        prepend(L, x); 
        	}
		else if(L->index == 0)
		{
			prepend(L, x);
		}
		else
		{
			Node z = newNode(x);
			Node temp = L->cursor;
			Node a = temp->prev;
			a->next = z;
			z->next = temp;
			temp->prev = z;
			z->prev = a;
			L->index++;
			L->length++;
		}
	}
}

//Insert new element before cursor. Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
	if(L == NULL)
	{
		printf("error, L is NULL");
	}
	if(L->length > 0 && L->index >= 0)
	{
		if(L->length == 1)
		{
			append(L, x);
		}
		else
		{
			if(L->cursor == L->back)
			{
				append(L,x);
			}
			else
			{	
				Node z = newNode(x);
				Node temp = L->cursor;
				Node c = (L->cursor)->next;
				temp->next = z;
				z->prev = temp;
				z->next = c;
				c->prev = z;
				L->length++;
			}
		}
	}		
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	if(L == NULL)
	{
		printf("error L is NULL");
	}
	if(L->front == L->back)
	{
		Node temp = L->front;
 		L->front = NULL;
		L->back = NULL;
                L->cursor = NULL;
               	L->index = -1;
		//free(temp->x);
		freeNode(&temp);
	}
	if(L->front != L->back)
	{
		Node temp = L->front;
		Node x = (L->front)->next;
		x->prev = NULL;
		L->front = x;

		 if(L->cursor == temp)
                {
                        L->cursor = NULL;
                        L->index = -1; //not necessary? 
                }
		//free(temp->x);
		freeNode(&temp);

		if(L->index > 0)
		{
			(L->index)--;
		}
	
	}
	L->length--;		
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	if(L == NULL)
	{
		printf("error L is NULL");
	}
	if(L->front == L->back) //length is 1
	{
		Node temp = L->back;
		L->front = NULL;
		L->back = NULL;	
		L->cursor = NULL;
		L->index = -1;
		//free(temp->x);
		freeNode(&temp);	
	}
	if(L->cursor == L->back) //if cursor was pointing at end
                {
                        L->cursor = NULL;
                        L->index = -1;
                }

	if(L->front != L->back)
	{
		Node temp = L->back;
		Node x = (L->back)->prev;
		x->next = NULL;
		L->back = x;
		//free(temp->x);
		freeNode(&temp);
//		if(L->cursor == temp) //if cursor was pointing at end
//		{
//			L->cursor = NULL;
//			L->index = -1;
//		}
	}
	L->length--;			
		
}

//Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
	if(L == NULL)
	{
		printf("error, L is NULL");
	}
	if(L->length > 0 && L->index >= 0)
	{
		if(L->length == 1) //only one item in list
		{
			deleteFront(L);
		}
		else if(L->cursor == L->front && L->length != 1)
		{
			deleteFront(L);
		}
		else if(L->cursor == L->back && L->length != 1)
		{
			deleteBack(L);
		}
		else //cursor is in middle of list
		{
			Node temp = L->cursor;
			Node a = (L->cursor)->prev;
			Node c = (L->cursor)->next;
			a->next = c;
			c->prev = a;
			//free(temp->x);
			freeNode(&temp);
			L->cursor = NULL;
			L->index = -1;
			L->length--;
		}
	}
}

// Other operations ----------------------------------

// Prints to the file pointed to by out
/*
void printList(FILE* out, List L) {
	Node temp = L->front;
	while(temp !=NULL)
	{
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
	}
}
*/



