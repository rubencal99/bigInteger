// Name: Ruben Calderon
// // CruzID: rucalder
// // Date: November 17, 2019
// // Pa3


#include<stdio.h>
#include<stdlib.h>
//#include"List.h"
#include"BigInteger.h"
//#include <string.h>

int main(int argc, char* argv[]){

	char* s = "-1111";
	char* t = "6789";
	printf("%s\n", s);
	printf("%s\n", t);
	//printf("right before stringToBigInteger(A)\n");
	BigInteger A = stringToBigInteger(s);
	BigInteger B = stringToBigInteger(t);
	//printf("right before addi\n");
	BigInteger S = newBigInteger();
	add(S, A, B);

	printf("TESTING ADD FUNCTION:\n");
	printBigInteger(stdout, A);
	printBigInteger(stdout, B);
	printBigInteger(stdout, S);
	printf("\n\n");
	//printf("right before 11111111\n");
	
	char* u = "11111111";
	BigInteger U = stringToBigInteger(u);
	add(S, U, B);

	printBigInteger(stdout, U);
        printBigInteger(stdout, B);
        printBigInteger(stdout, S);
	printf("\n\n");

	printBigInteger(stdout, A);
	printBigInteger(stdout, A);
	add(A, A, A);
	printBigInteger(stdout, S);
	printf("\n\n");


	printf("TESTING SUBTRACT FUNCTION:\n");
	char* r = "10000000";
	char* v = "9999";
	BigInteger R = stringToBigInteger(r);
	BigInteger V = stringToBigInteger(v);
	BigInteger D1 = newBigInteger();
	BigInteger D2 = newBigInteger();
	
	D1 = diff(R, V);
	D2 = diff(V, R);

	printBigInteger(stdout, R);
	printBigInteger(stdout, V);
	//printf("pre print D1\n");
	printBigInteger(stdout, D1);
	//printf("pre print D2\n");
	printBigInteger(stdout, D2);
	printf("\n");
	makeZero(D1);
	makeZero(D2);
	

	char* w = "-999999999";
	BigInteger W = stringToBigInteger(w);
	printBigInteger(stdout, R);
	printBigInteger(stdout, W);

	D1 = diff(R, W);
	D2 = diff(W, R);

	printBigInteger(stdout, D1);
	printBigInteger(stdout, D2);
	printf("\n\n");

	
	printf("TESTING MULTIPLY FUCTION:\n");
	char* factor1 = "13";
	char* factor2 = "110";

	BigInteger F1 = stringToBigInteger(factor1);
	BigInteger F2 = stringToBigInteger(factor2);
	printBigInteger(stdout, F1);
	printBigInteger(stdout, F2);

	BigInteger M = newBigInteger();
	multiply(M, F1, F2);
	printBigInteger(stdout, M);
	printf("\n");
	
	char* factor3 = "422199";
	char* factor4 = "361122";

	BigInteger F3 = stringToBigInteger(factor3);
	BigInteger F4 = stringToBigInteger(factor4);
	
	printBigInteger(stdout, F3);
	printBigInteger(stdout, F4);
	multiply(M, F3, F4);
	printBigInteger(stdout, M);
	printf("\n");
	
	BigInteger F5 = stringToBigInteger("999999");
	BigInteger F6 = stringToBigInteger("2");
	multiply(M, F5, F6);

	printBigInteger(stdout, F5);
	printBigInteger(stdout, F6);
	printBigInteger(stdout, M);
	printf("\n");


	BigInteger pA = stringToBigInteger("+111122223333");
	BigInteger pB = stringToBigInteger("+222211110000");
	BigInteger pC = newBigInteger();

	BigInteger pD = stringToBigInteger("+333333333333");
	add(pC, pA, pB);
	printBigInteger(stdout, pC);
	printBigInteger(stdout, pD);
	makeZero(pB);
	freeBigInteger(&pB);

	
	pB = stringToBigInteger("-110122223333");
	printBigInteger(stdout, pA);
        printBigInteger(stdout, pB);
	add(pC, pA, pB);
	printBigInteger(stdout, pC);
	printf("Sign of Test 3: %d\n", sign(pC));

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&S);
	freeBigInteger(&U);
	freeBigInteger(&R);
	freeBigInteger(&V);
	freeBigInteger(&D1);
	freeBigInteger(&D2);
	freeBigInteger(&W);
	freeBigInteger(&F1);
	freeBigInteger(&F2);
	freeBigInteger(&M);
	freeBigInteger(&F3);
	freeBigInteger(&F4);
	freeBigInteger(&F5);
	freeBigInteger(&F6);

	return(0);
}
