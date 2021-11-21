//Julia Ni
//juni
//pa2

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include "List.h" 

typedef struct EntryObj {
	int col;
	double data;
} EntryObj;

typedef struct MatrixObj {
	int entries;
	int size;
	List L[];
} MatrixObj;


typedef EntryObj* Entry;
typedef MatrixObj* Matrix;

Entry newEntry(int a, double d) {
	Entry temp = (void*)malloc(sizeof(EntryObj));
	temp->col = a;
	temp->data = d;
	return temp;
}
//constructor/destructor---------------------------------------------
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = malloc(2*sizeof(int)+n*sizeof(List));
	M->entries = 0;
	M->size = n;
	for(int i = 0; i < size(M); i++) //initalize the rows
	{
		M->L[i] = newList();
	}	
	return M;
}

//frees heap memory associated with *pM, sets *pM to NULL

void freeMatrix(Matrix* pM) {
	if(pM != NULL && *pM != NULL)
 	{
		Matrix M = *pM;
		for(int i = 0; i < M->size; i++)
		{
			freeList(&(M->L[i])); //????
		}
	
		free(*pM);
                *pM = NULL;
	} 
	return;	
} 




//private helper function
//computes the vector dot product of two matrix rows 

double vectorDot(List P, List Q) {
        if(P == NULL)
        {
                printf("error, P is NULL");
                exit(1);
        }
        if(Q == NULL)
        {
                printf("error, Q is NULL");
                exit(1);
        }
        double sum = 0;

	moveFront(P);
	moveFront(Q);
       while(index(P) >= 0 || index(Q) >= 0)
        {             
                Entry p = NULL;
                Entry q = NULL;

                if(index(P)>=0)
                {
                        p = (Entry)get(P);
                }
                if(index(Q)>=0)
                {
                        q = (Entry)get(Q);
                }

                if(p == NULL)
                {
                        moveNext(Q);
                }
                else if(q == NULL)
                {
                        moveNext(P);
                }
                else if(p->col < q->col) //B = 0 at an index
                {
                        moveNext(P);
                }
                else if(p->col > q->col) //A = 0 at an index 
                {
                        moveNext(Q);
                }
                else //columns are equal
                {
                        double temp = p->data * q->data;
                        sum = sum + temp;
                        moveNext(P);
                        moveNext(Q);
                }
		
        }
        return sum; //dot product of two rows(one entry)
}


//access functions--------------------------------------------------
//return the size of square Matrix M
int size(Matrix M) {
	return M->size;
}

//return the number of non-zero elements in M
int NNZ(Matrix M) { 
	return M->entries;
}

//return true (1) if matrices A and B are equal, false (0) otherwise
int equals(Matrix A, Matrix B) {
	if(A == NULL || B == NULL)
	{
		printf("error, matrix a or b is NULL");
		exit(1);
	}
	//check addresses if equals (A,A)
	if(A == B)
	{
		return 1;
	}
	if(size(A) != size(B))
	{
		return 0;
	}
	if(A->entries == 0 && B->entries == 0) //both empty
	{
		return 1;
	}
	if(A->entries != B->entries)
	{
		fprintf(stdout, "hello");
		return 0;
	}
	for(int i = 0; i < size(A); i++) //loop through rows
	{
		if(length(A->L[i]) != length(B->L[i]))
		{
			return 0;
		}
		moveFront(A->L[i]);
		moveFront(B->L[i]);	
		while(index(A->L[i]) >= 0)
		{
			Entry a = get(A->L[i]);
                	Entry b = get(B->L[i]);
			if(a->col != b->col)
			{
				return 0;
			}
			if(a->data != b->data)
			{
				return 0;
			}	
			moveNext(A->L[i]);
			moveNext(B->L[i]);
		}	
	}
	return 1;
}

//Manipulation procedures------------------------------------------
//resets M to the zero Matrix
void makeZero(Matrix M) {
	if(M == NULL)
	{
		printf("error, matrix M is NULL");
		exit(1);
	}
	for(int i = 0; i < size(M); i++)
	{
		if(M->L[i] == NULL)
		{
			printf("error, list does not exist");
		}	
		else
		{
			clear(M->L[i]);
		}
	}
	M->entries = 0;
}


//changes the ith row, jth column of M to the value x
void changeEntry(Matrix M, int i, int j, double x) {
	if(M == NULL)
	{
		printf("error, M is NULL");
		exit(1);
	}
	if(length(M->L[i-1]) == 0) //if list is empty
	{
		if(x != 0)
		{
			Entry temp = newEntry(j,x);
			append(M->L[i-1], temp);
			M->entries++;
		}
		return;
	}
	if(i<=size(M) && j<=size(M) && i >= 1 && j >= 1)
	{
		List cur = M->L[i-1];
		moveFront(cur);
		Entry temp = (get(cur));
		while(index(cur) >= 0 && temp->col < j) //moving cursor
		{
			moveNext(cur);
			if(index(cur) >= 0)
			{
				temp = get(cur);
			}
			else
			{
				temp = NULL;
			}
		}
		if(temp == NULL) //add to back of list
                {
                        Entry temp = newEntry(j,x);
                        if(x != 0)
                        {
                                append(cur, temp);
				M->entries++;
                        }
                     

                        return;
                }

		if(temp->col == j) 
		{
			temp->data = x;
			if(x == 0)
			{
								
				//freeEntry(E);//????		
				delete(cur);
				M->entries--;
			}
			return;
		}
		if(temp->col > j) 
		{
			Entry temp = newEntry(j,x);
			if(x != 0)
			{
				insertBefore(cur, temp);
			}	
			M->entries++;
			return;
		}
		
	}
}

//Matrix arithmetic operations
//returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A) {
	if(A == NULL)
	{
		printf("error, A is NULL");
		exit(1);
	}
	if(A->entries == 0) //empty matrix
	{
		Matrix B = newMatrix(size(A)); //B is new matrix
		return B;
	}

	Matrix B = newMatrix(size(A));
	for(int i = 0; i < size(A); i++)
	{
		List cur = A->L[i];
		List curB = B->L[i];
		moveFront(cur);
		while(index(cur) >= 0)
		{
			Entry temp = get(cur);
			append(curB, temp);
			moveNext(cur);
		}
	}
	B->entries = A->entries;
	return B;	
}

//returns a reference to a new Matrix object representing the tranpose
Matrix transpose(Matrix A){ //doesnt work with 0????
	if(A == NULL)
        {
                printf("error, A is NULL");
                exit(1);
        }
        if(A->entries == 0) //empty matrix
        {
                Matrix B = newMatrix(size(A)); //B is new matrix
                return B;
        }

        Matrix B = newMatrix(size(A));
        for(int i = 0; i < size(A); i++)
        {
                List cur = A->L[i];
                //List curB = B->L[i];
                moveFront(cur);
                while(index(cur) >= 0)
                {
                        Entry original = get(cur);
			Entry temp = newEntry(i+1 , original->data);
			append(B->L[original->col - 1], temp);
        	        B->entries++;
        	        moveNext(cur);
			
                }
        }
        return B;

}

//returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A) { //affecting original A matrix??
	//change matrix A or make a new Matrix B??
	if(A == NULL)
	{
		printf("error, A is NULL");
		exit(1);
	}
	if(x == 0) //returns 0 matrix
	{
		Matrix B = newMatrix(size(A));
		return B;

	}
	if(x == 1.0) //returns original matrix
	{
		Matrix B = copy(A);
		return B;
	}
	Matrix B = newMatrix(size(A));
	for(int i = 0; i < size(B); i++)
	{
		List curA = A->L[i];
		List curB = B->L[i];
		moveFront(curA);
		moveFront(curB);
		while(index(curA) >= 0)
		{
			Entry entryA = get(curA);
               
			Entry temp = newEntry(entryA->col, entryA->data * x);
			append(curB, temp);
			B->entries++;
			moveNext(curA);
			moveNext(curB);	
		}	
	}
	return B;

}

// Returns a reference to a new Matrix object representing A+B.
Matrix sum(Matrix A, Matrix B) {
	if(A == NULL)
        {
                printf("error, A is NULL");
                exit(1);
        }
	if(B == NULL)
	{
		printf("error, A is NULL");
                exit(1);
	}
	if(size(A) != size(B)) //check if size are equal
	{
		printf("error, sizes are not equal");
                exit(1);
	}
	//if A is empty matrix, return B
	if(A->entries  == 0)
	{
		return B;
	}
	//if B is empty matrix, return A
	if(B->entries == 0) 
	{
		return A;
	}
	Matrix C;

	if(A == B)
	{
		C = scalarMult(2,A);
		return C;
	}	
	C = newMatrix(size(A));
	
	  //Matrix C = newMatrix(size(A));	
	for(int i = 0; i < size(A); i++)
	{
		List curA = A->L[i];
		List curB = B->L[i];
		List curC = C->L[i];
		moveFront(curA);
		moveFront(curB);
		while(index(curA) >= 0 || index(curB) >= 0) 
		{	
			Entry entryA = NULL;
			Entry entryB = NULL;
			if(index(curA)>=0){
				entryA = get(curA);
			}
			if(index(curB)>=0){
				entryB = get(curB);
			}

			if(entryA == NULL)
			{
				append(curC, entryB);
				C->entries++;
				moveNext(curB);	
			}
			else if(entryB == NULL)
			{
				append(curC, entryA);
				 C->entries++;
				moveNext(curA);
			}
			else if(entryA->col < entryB->col) //B = 0 at an index
                        {
				append(curC, entryA);
				 C->entries++;
                               	moveNext(curA);
			}
                        else if(entryA->col > entryB->col) //A = 0 at an index 
                        {
				append(curC, entryB);
				 C->entries++;
				moveNext(curB);
                        }
			
			//if (entryA->col == entryB->col) //check index are equal 
			else
			{		
				if(entryA->data + entryB->data == 0 || entryB->data + entryA->data == 0) //numbers cancel each other out
				{	
                                        moveNext(curA);
                                       	moveNext(curB);
                               
				}
	
				else //adding two numbers
				{
					Entry temp = newEntry(entryA->col, entryA->data + entryB->data);
                        	        append(curC, temp);
					 C->entries++;
                        	        moveNext(curA);
                        	        moveNext(curB);
				}
			}
		} 
	}
	
	return C;
	

}

//returns a reference to a new Matrix object representing A-B
Matrix diff(Matrix A, Matrix B) {
	if(A == NULL)
        {
                printf("error, A is NULL");
                exit(1);
        }
        if(B == NULL)
        {
                printf("error, A is NULL");
                exit(1);
        }
	if(size(A) != size(B))
	{
		printf("error, sizes are not the same");
		exit(1);
	}
	if(A==B)
	{
		return newMatrix(size(A));
	}
	Matrix C = newMatrix(size(A));

	for(int i = 0; i < size(A);i++)
	{
		List curA = A->L[i];
		List curB = B->L[i];
		List curC = C->L[i];
		moveFront(curA);
		moveFront(curB);
		while(index(curA) >= 0 || index(curB) >= 0)
		{
			Entry entryA = NULL;
			Entry entryB = NULL;
			if(index(curA) >= 0)
			{
				entryA = get(curA);
			}
			if(index(curB) >= 0)
			{
				entryB = get(curB);
			}
			if(entryA == NULL) //cursor und on list a
			{		
				Entry e = newEntry(entryB->col, 0 - entryB->data);
				append(curC, e);
				C->entries++;
				moveNext(curB);
			}
			else if(entryB == NULL) //b =0
			{
				append(curC, entryA);
				C->entries++;
				moveNext(curA);
			}
			else if(entryA->col < entryB->col) 
			{
				append(curC, entryA);
				C->entries++;
				moveNext(curA);
			}
			else if(entryA->col > entryB->col)
			{
				Entry e = newEntry(entryB->col, 0 - entryB->data);
				append(curC, e);
				C->entries++;
				moveNext(curB);
			}
			else
			{
				Entry temp = newEntry(entryA->col, entryA->data - entryB->data);
				
				if(temp->data != 0)
				{
					append(curC, temp);
					C->entries++;
				}
				moveNext(curA);
				moveNext(curB);
			}
		}
	}
	return C;
}

//returns a reference to a new Matrix object representing AB
Matrix product(Matrix A, Matrix B){
	if(A == NULL)
        {       
                printf("error, A is NULL");
                exit(1);
        }
        if(B == NULL)
        {       
                printf("error, A is NULL");
                exit(1);
        }
	if(size(A) != size(B))
	{
		printf("error, matrices are not the same size");
		exit(1);
	}
	Matrix C = newMatrix(size(A)); //represents product
	Matrix flip = transpose(B);
//second and third column data values swapped?
	
	for(int i = 0; i < size(A); i++) // loop thru rows
	{
		int rowB = 0;	
		List a = A->L[i];
		List b = flip->L[rowB];
		List cur = C->L[i];
		while(rowB < size(A) && rowB >= 0) //loop thru rows of B
		{		
				
				double temp = vectorDot(a,b);//b is transpose matrix
				
				Entry e = newEntry(rowB + 1 , temp);
				if(temp != 0) //appends if dot product isnt 0
				{
					append(cur, e);
					C->entries++;
				}
				rowB++;
				b = flip->L[rowB];   
		}
	}
	return C;
		
	
}

//Prints a string representation of Matrix M. zero rows not printed...
void printMatrix(FILE* out, Matrix M) {
	for(int i = 0; i < size(M); i++)
	{
		List cur = M->L[i];
		if(length(cur) != 0)
			{
				moveFront(cur);
				Entry temp = get(cur);
				fprintf(out, "%d: ", i+1);
				while(index(cur) >= 0) //loop thru the list and print it out
				{
					fprintf(out, "(%d, %.1f) ", temp->col, temp->data);
					moveNext(cur);
					temp = get(cur);
				}
				fprintf(out, "\n");
			}
	}
}
 
