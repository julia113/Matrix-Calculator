//Julia Ni
//juni
//pa2


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"

#define MAX_LENGTH 160

int main (int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char line[MAX_LENGTH];
	char* token;
	int n, a, b;

	int row;
	int column;
	double value;
	
	if(argc != 3)
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL)
	{
		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
	}
	if(out == NULL)
	{
		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
	}
	

	//read input file
	//n = size, a = entries of a, b = entries of b
	fgets(line, MAX_LENGTH, in);
	token = strtok(line, " ");
	sscanf(token, "%d", &n);
	token = strtok(NULL, " ");
	sscanf(token, "%d", &a);
	token = strtok(NULL, " ");
	sscanf(token, "%d", &b);
	
	//fprintf(out, "%d %d %d\n", n, a, b);
	Matrix A = newMatrix(n);
	//A->entries = a;

	Matrix B = newMatrix(n);
	//B->entries = b;
	//build the array of lists
		
	fgets(line, MAX_LENGTH, in);
	fgets(line, MAX_LENGTH, in);
	for(int i = 0; i < a; i++)
	{
		 token = strtok(line, " ");
        	sscanf(token, "%d", &row);
        	token = strtok(NULL, " ");
        	sscanf(token, "%d", &column);
        	token = strtok(NULL, " ");
       		sscanf(token, "%lf", &value);
		changeEntry(A, row, column, value);
		fgets(line, MAX_LENGTH, in);
	//	 fprintf(stdout, "%d %d", row, column);

	}
       // printMatrix(out, A);	
	
	fgets(line, MAX_LENGTH, in);
//        fgets(line, MAX_LENGTH, in);
	  for(int i = 0; i < b; i++)
        {
                 token = strtok(line, " ");
                sscanf(token, "%d", &row);
                token = strtok(NULL, " ");
                sscanf(token, "%d", &column);
                token = strtok(NULL, " ");
                sscanf(token, "%lf", &value);
		changeEntry(B, row, column, value);
		fgets(line, MAX_LENGTH, in);
	//	fprintf(stdout, "%d %d", row, column);
        }
	
	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out,A);
	fprintf(out, "\n");

	//B
	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out,B);
	fprintf(out, "\n");
	
	//scalar mult
	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, scalarMult(1.5, A));
	fprintf(out, "\n");

	//A+B
	fprintf(out, "A+B =\n");
	printMatrix(out, sum(A,B));
	fprintf(out, "\n");

///A+A
	fprintf(out, "A+A =\n");
 	printMatrix(out, sum(A,A));		
	fprintf(out, "\n");


	//B-A
	fprintf(out, "B-A =\n");
	printMatrix(out, diff(B,A));
	fprintf(out, "\n");	

	//A-A
	fprintf(out, "A-A =\n");
        printMatrix(out, diff(A,A));
        fprintf(out, "\n");

	//transpose A
	fprintf(out, "Transpose(A) =\n");
        printMatrix(out, transpose(A));
        fprintf(out, "\n");
	
	//A times B
	fprintf(out, "A*B =\n");
        printMatrix(out, product(A,B));
        fprintf(out, "\n");	

	//B times B	
	fprintf(out, "B*B =\n");
        printMatrix(out, product(B,B));
        fprintf(out, "\n");	


	     
   	
		fclose(in);
   	fclose(out);

   	return(0);

}
