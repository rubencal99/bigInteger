// Name: Ruben Calderon
// // CruzID: rucalder
// // Date: November 17, 2019
// // Pa3

#include<stdio.h>
#include<stdlib.h>
//#include"List.h"
#include"BigInteger.h"

int main(int argc, char* argv[]){

	if(argc != 3){
		fprintf(stderr, "Error: Incorrect amount of command line arguments.\n");
		exit(1);
	}

	FILE* in;
	FILE* out;
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		fprintf(stderr, "Error: input file not found.\n");
		exit(1);
	}
	int a;
	fscanf(in, "%d\n", &a);
	char* bigA = calloc(a+1, sizeof(char));
	fscanf(in, "%s\n", bigA);
	int b;
	fscanf(in, "%d\n", &b);
	char* bigB = calloc(b+1, sizeof(char));
	fscanf(in, "%s\n", bigB);
	
	fprintf(out, "%d\n%s\n%d\n%s\n", a, bigA, b, bigB);

	BigInteger A = stringToBigInteger(bigA);
	BigInteger B = stringToBigInteger(bigB);

	fprintf(out, "A\n");
	printBigInteger(out, A);			//A
	fprintf(out, "\n");
	
	fprintf(out, "B\n");
	printBigInteger(out, B);			//B
        fprintf(out, "\n");

	fprintf(out, "A + B\n");
	BigInteger Sum = newBigInteger();		//A + B
	add(Sum, A, B);
	printBigInteger(out, Sum);
	fprintf(out, "\n");

	fprintf(out, "A - B\n");
	BigInteger Diff = newBigInteger();		//A - B
	subtract(Diff, A, B);
	printBigInteger(out, Diff);
	fprintf(out, "\n");

	fprintf(out, "A - A");
	subtract(Diff, A, A);
	printBigInteger(out, Diff);			//A - A
	fprintf(out, "\n");

	fprintf(out, "3A - 2B");
	BigInteger Three = stringToBigInteger("3");	//3A - 2B
	multiply(Three, Three, A);
	BigInteger Two = stringToBigInteger("2");
	multiply(Two, Two, B);
	subtract(Diff, Three, Two);
	printBigInteger(out, Diff);
	fprintf(out, "\n");
	
	
	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&Sum);
	freeBigInteger(&Diff);
	fclose(in);
	fclose(out);
	return(0);
}
