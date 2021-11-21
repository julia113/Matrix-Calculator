//Julia Ni
//juni
//pa2

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
   
	List A = newList();
   	List B = newList();
   	List C = newList();
   	int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   	int i, u=-1, v=-2, equal=0;

 	for(i=1; i<=20; i++){
		append(A, &X[i]);
      		prepend(B, &X[i]);
   	}	
	for(moveFront(A); index(A)>=0; moveNext(A)){
      		printf("%d ", *(int*)get(A));
   	}
   	printf("\n");
   	for(moveFront(B); index(B)>=0; moveNext(B)){
      		printf("%d ", *(int*)get(B));
   	}
   	printf("\n");

	for(moveBack(A); index(A)>=0; movePrev(A)){
      		printf("%d ", *(int*)get(A));
   	}
   	printf("\n");
   	for(moveBack(B); index(B)>=0; movePrev(B)){
      		printf("%d ", *(int*)get(B));
   	}
   	printf("\n");

	moveFront(A);
   	while( index(A)>=0 ){
      		append(C, get(A));
      		moveNext(A);
   	}
	for(moveFront(C); index(C)>=0; moveNext(C)){
      		printf("%d ", *(int*)get(C));
   	}
   	printf("\n");


	equal = (length(A)==length(C));
   	moveFront(A);
   	moveFront(C);
   	while( index(A)>=0 && equal){
   		   equal = ( get(A)==get(C) );
   		   moveNext(A);
   		   moveNext(C);
   	}
   	printf("A equals C is %s\n", (equal?"true":"false") );

   	moveFront(A);

	for(i=0; i<5; i++) moveNext(A);
		insertBefore(A, &u);  
     	for(i=0; i<9; i++) moveNext(A);
 	insertAfter(A, &v);
	for(i=0; i<5; i++) movePrev(A);
	delete(A);
	
	for(moveFront(A); index(A)>=0; moveNext(A)){
	      printf("%d ", *(int*)get(A));
	}
   	printf("\n");
   	for(moveBack(A); index(A)>=0; movePrev(A)){
   		   printf("%d ", *(int*)get(A));
   	}
   	printf("\n");
	printf("%d\n", length(A));
   	clear(A);
   	printf("%d\n", length(A));

   	freeList(&A);
   	freeList(&B);
   	freeList(&C);

   	return(0);
}

