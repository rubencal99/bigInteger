// Name: Ruben Calderon
// // CruzID: rucalder
// // Date: November 17, 2019
// // Pa3


#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
#include<string.h>
#include<math.h>
#include<ctype.h>
#include"List.h"

#define POWER 9
#define BASE pow(10, POWER)

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
	int sign;
	List Long;
}BigIntegerObj;



// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
	BigInteger N = malloc(sizeof(BigIntegerObj));

        N->Long = newList();
	return(N);
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
	if(pN!=NULL && *pN!=NULL){
		makeZero(*pN);
                freeList(&((*pN)->Long));
		//free((pN)->Long);
                free(*pN);
                *pN=NULL;
        }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero state
int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling sign() on undefined reference\n");
		exit(1);
	}
	return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling compare() on undefined reference\n");
                exit(1);
        }
	if(length(A->Long) < length(B->Long) || (sign(A) == -1 && sign(B) == 1)){
		return -1;
	}
	else if(length(A->Long) > length(B->Long) || (sign(A) == 1 && sign(B) == -1)){
		return 1;
	}
	
	moveFront(A->Long);
	moveFront(B->Long);
	
	while(index(A->Long) != -1){
		if(get(A->Long) < get(B->Long)){
                	return -1;
        	}
        	else if(get(A->Long) > get(B->Long)){
                	return 1;
        	}
		moveNext(A->Long);
		moveNext(B->Long);
	}
	return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
                printf("BigInteger Error: calling equals() on undefined reference\n");
                exit(1);
        }
	if(compare(A, B) == 0){
		return 1;
	}
	return 0;
}


// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	if(N == NULL){
                printf("BigInteger Error: calling makeZero() on undefined reference\n");
                exit(1);
        }
	clear(N->Long);
	/*moveFront(N->Long);
	while(index(N->Long) != -1){
		set(N->Long, 0);
		moveNext(N->Long);
	}*/
	N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the zero state.
void negate(BigInteger N){
	if(N == NULL){
                printf("BigInteger Error: calling negate() on undefined reference\n");
                exit(1);
        }
	N->sign = (N->sign * -1);
}


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9} and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
	if(s == NULL){
		printf("BigInteger Error: calling stringToBigInteger() on undefined reference\n");
                exit(1);
        }
	if(strlen(s) == 0){
		printf("BigInteger Error: calling stringToBigInteger() on empty string\n");
                exit(1);
        }
	BigInteger N = newBigInteger();
	//long temp;
	
	if(s[0] == '-'){
		N->sign = -1;
	}
	else if(s[0] == '+'){
		N->sign = 1;
	}
	else if(isdigit(s[0])){
		N->sign = 1;
	}
	char* temp = normalizeString(s);
	int Short = strlen(temp) % POWER;
	int num;
	int i = 0;
	if(Short != 0){
		char* a=calloc(Short, sizeof(char));
		//printf("RIGHT BEFORE MEMCPY A\n");
		memcpy(a, temp, Short);
		num = atol(a);
		append(N->Long, num);
		i += Short;
		free(a);
	}
	char* b=calloc(POWER, sizeof(char));
	while(i != strlen(temp)){
		//printf("RIGHT BEFORE MEMCPY B\n");
		memcpy(b, temp+i, POWER);
		num = atol(b);
		append(N->Long, num);
		i += POWER;
		
	}
	free(b);

	//printList(stdout, N->Long);
	return(N);
}

char* normalizeString(char* s){
	char* temp = s;
	int i = 0;
	while(s[i] == '0' || s[i] == '-' || s[i] == '+'){
		temp = s + i + 1;
		i++;
	}
	return(temp);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
	if(N == NULL){
                printf("BigInteger Error: calling copy() on undefined reference\n");
                exit(1);
        }
	moveFront(N->Long);
	long j;
	BigInteger new = newBigInteger();
	while(index(N->Long) != -1){
		j = get(N->Long);
		append(new->Long, j);
		moveNext(N->Long);
	}
	new->sign = N->sign;
	return(new);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
	if(S == NULL || A == NULL || B == NULL){
                printf("BigInteger Error: calling add() on undefined reference\n");
                exit(1);
        }
	moveBack(A->Long);
	moveBack(B->Long);
	makeZero(S);
	long numA;
	long numB;
	int sum;
	int carry = 0;
	//printf("In add\n");
	if(A->sign == 0 && B->sign == 0){
		return;
	}
	else if(A->sign == 0){
		S = copy(B);
		return;
	}
	else if(B->sign == 0){
		S = copy(A);
		return;
	}

	if(A->sign == 1 && B->sign == -1){
		BigInteger C = copy(B);
		negate(C);
		//BigInteger temp = newBigInteger();
		subtract(S, A, C);
		//S = copy(temp);
		//printBigInteger(stdout, S);
		freeBigInteger(&C);
		//freeBigInteger(&temp);
		return;
	}
	else if(A->sign == -1 && B ->sign == 1){
		BigInteger C = copy(B);
		negate(C);
		subtract(S, C, A);
		return;
	}
	if(compare(A, B) == 0){
		BigInteger temp = stringToBigInteger("2");
		S = prod(A, temp);
		freeBigInteger(&temp);
		return;
	}
	moveBack(A->Long);
	moveBack(B->Long);
	while(index(A->Long) != -1 && index(B->Long) != -1){
		numA = get(A->Long);
		numB = get(B->Long);
		sum = (int)(numA + numB + carry);
		prepend(S->Long, sum % (int)BASE);
		carry = sum / (int)BASE;
		movePrev(A->Long);
		movePrev(B->Long);
	}
	while(index(A->Long) != -1){
		numA = get(A->Long);
		sum = (int)(numA + carry);
		prepend(S->Long, sum % (int)BASE);
		carry = sum / (int)BASE;
		movePrev(A->Long);
	}
	while(index(B->Long) != -1){
                numB = get(B->Long);
                sum = (int)(numB + carry);
                prepend(S->Long, sum % (int)BASE);
                carry = sum / (int)BASE;
                movePrev(B->Long);
        }
	if(carry != 0){
		prepend(S->Long, carry);
	}
	if(A->sign == 1 && B->sign == 1){
		S->sign = 1;
	}
	else if(A->sign == -1 && B->sign == -1){
		S->sign = -1;
	}
	normalizeBig(S);
	//printBigInteger(stdout, S);
	return;
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling sum() on undefined reference\n");
                exit(1);
        }
	BigInteger S = newBigInteger();
	add(S, A, B);
	S->sign = 1;
	return(S);
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
                printf("BigInteger Error: calling subtract() on undefined reference\n");
                exit(1);
        }
	BigInteger tempA = copy(A);
	BigInteger tempB = copy(B);
	long numA;
	long numB;
	long difference;
	//BigInteger tempD = copy(D);
	moveBack(tempA->Long);
	moveBack(tempB->Long);
	//printf("Back elements are %ld and %ld\n", get(A->Long), get(B->Long));
	makeZero(D);
	int borrow = 0;
	int carry = 0;
	if(tempA->sign == 0 && tempB->sign == 0){
		//D = copy(tempD);
		//freeBigInteger(&tempD);
                return;
        }
        else if(tempA->sign == 0){
                D = copy(tempB);
		negate(D);
		//D = copy(tempD);
                //freeBigInteger(&tempD);
                return;
        }
        else if(tempB->sign == 0){
                D = copy(tempA);
        	//D = copy(tempD);
                //freeBigInteger(&tempD); 
	       return;
        }

	if(tempA->sign != tempB->sign){
		//printf("opposite signs\n");
		BigInteger C = copy(B);
		negate(C);
		//printf("before sum, C sign = %d\n", C->sign);
		add(D, A, C);
		//add(D, A, C);
		//printf("after sum\n");
		D->sign = A->sign;
		//freeBigInteger(&C);
		//printf("in subtract (called by diff) Different signs: ");
		//printBigInteger(stdout, D);
		freeBigInteger(&C);
		return;
	}
	if(equals(A, B)){
		//D = copy(tempD);
                //freeBigInteger(&tempD);
		return;
	}
	//printf("right before shallow compare\n");
	if(shallowCompare(A, B) == -1){
		//printf("in shallow compare\n");
		subtract(D, B, A);
		D->sign = -1;
		//D = copy(tempD);
                //freeBigInteger(&tempD);
		return;
	}
	else{
		//printf("after shallow compare\n");
		//printBigInteger(stdout, A);
		//printBigInteger(stdout, B);
		moveBack(tempA->Long);
		moveBack(tempB->Long);
		while(index(tempA->Long) != -1 && index(tempB->Long) != -1){
			numA = get(tempA->Long);
			numB = get(tempB->Long);
			//printf("Subtracting %ld from %ld\n", numB, numA);
			if(borrow == BASE){
				carry = 1;
			}
			if(numB > numA){
				borrow = (int)BASE;
			}
			else{
				borrow = 0;
			}
			difference = (long)(numA + borrow - numB - carry);
			prepend(D->Long, difference);
			//printf("diff == %ld\n", diff);
			if(numA > 0 && borrow != BASE){
				carry =0;
			}
			movePrev(tempA->Long);
			movePrev(tempB->Long);
		}
		//printf("after first while\n");
		while(index(tempA->Long) != -1){
			numA = get(tempA->Long);
			//printf("numA = %ld\n", numA);
			difference = numA - carry;
			if(0 > difference){
				borrow = (int)BASE;
				difference += borrow;
				carry = 1;
			}
			else{
				carry = 0;
			}
			prepend(D->Long, difference);

			movePrev(tempA->Long);
			//printBigInteger(stdout, D);
		}
	}
	//printf("after second while\n");
	D->sign = 1;
	normalizeBig(D);
	//makeZero(D);
	//D = copy(tempD);
	//freeBigInteger(&tempD);
	//printf("after normalize\n");
	return;

	
}

// shallowCompare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B, regardless of sign
int shallowCompare(BigInteger A, BigInteger B){
        if(A == NULL || B == NULL){
                printf("BigInteger Error: calling compare() on undefined reference\n");
                exit(1);
        }
	int lenA = length(A->Long);
	int lenB = length(B->Long);
        //printf("Length of A = %d\n", lenA);
        //printf("Length of B = %d\n", lenB);
	
	if(lenA < lenB){
                return -1;
        }
        else if(lenA > lenB){
                return 1;
        }
	//printf("after compare\n");
        moveFront(A->Long);
        moveFront(B->Long);

        while(index(A->Long) != -1){
                if(get(A->Long) < get(B->Long)){
                        return -1;
                }
                else if(get(A->Long) > get(B->Long)){
                        return 1;
                }
                moveNext(A->Long);
                moveNext(B->Long);
        }
        return 0;
}

//diff()
// Returns a reference to a new BigInteger object representing A-B.
BigInteger diff(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
                printf("BigInteger Error: calling sum() on undefined reference\n");
                exit(1);
        }
        BigInteger temp = newBigInteger();
        subtract(temp, A, B);
	//D = copy(temp);
	//freeBigInteger(&temp);
	return temp;
        //D->sign = 1;
       // printf("in diff: \n");
       // printBigInteger(stdout ,D);
	//printf("====== SIGN %d =======\n", D->sign);
	//printBigInteger(stdout, D);
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
	if(P == NULL || A == NULL || B == NULL){
                printf("BigInteger Error: calling subtract() on undefined reference\n");
                exit(1);
        }
	long numA;
	long numB;
	long numC;
	long prod;
	//BigInteger P = newBigInteger();
	moveBack(A->Long);
	int i = 0;
	int k = 0;
	int carry;
	int sum;
	while(index(A->Long) != -1){
		moveBack(B->Long);
		numA = get(A->Long);
		moveBack(P->Long);
		carry = 0;
		while(index(B->Long) != -1){
			numB = get(B->Long);
                        prod = (numA * numB);
			if(i == 0){
				sum = (int)prod + carry;
				prepend(P->Long, sum%(int)BASE);
				if(k == 0){
					moveBack(P->Long);
				}
				carry = sum/(int)BASE;
				//printf("carry = %d\n", carry);
				k++;
				movePrev(P->Long);
			}
			else{
				for(int j = 0; j < i; j++){
					movePrev(P->Long);
				}
				//printf("right before get\n");
				//for(int j = 0; j < k; j++){
					if(index(P->Long) != -1){
						numC = get(P->Long);
						//printf("numC = %ld\n", numC);
						sum = numC + (int)prod + carry;
						set(P->Long, sum%(int)BASE);
					}
					else{
						//printf("carry = %d\n", carry);
						sum = (int)prod + carry;
						prepend(P->Long, sum%(int)BASE);
					}
					carry = sum/(int)BASE;
					//movePrev(P->Long);
					//movePrev(B->Long);
					//prod = (numA * numB);
					//printBigInteger(stdout, P);
					//printf("In for loop: ");
					//printBigInteger(stdout, P);
				//}
			}
			movePrev(B->Long);
			//movePrev(P->Long);
		}
		if(carry != 0){
			prepend(P->Long, carry);
		}
		//printBigInteger(stdout, P);
		i++;
		movePrev(A->Long);
	}
	return;
}




// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
                printf("BigInteger Error: calling subtract() on undefined reference\n");
                exit(1);
        }
	BigInteger P = newBigInteger();
	//makeZero(P);
	//BigInteger temp = prod(A, B);
	//P = copy(temp);
	
	//freeBigInteger(&temp);
	return P;
}


// Other operations -----------------------------------------------------------

// normalizeBig()
// erases all leading 0s from the big integer
void normalizeBig(BigInteger N){
	List list = N->Long;
	moveFront(list);
	while(index(list) != -1){
		if(get(list) == 0){
			delete(list);
			moveFront(list);
		}
		else{
			char buffer[POWER];
			sprintf(buffer, "%ld", get(list));
			//printf("temp = %s\n", temp);
			normalizeString(buffer);
			delete(list);
			long num = atol(buffer);
			prepend(list, num);
			return;
		}
	}
	return;
}

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
	if(N == NULL){
                printf("BigInteger Error: calling printBigInteger() on undefined reference\n");
                exit(1);
        }
	//BigInteger temp = copy(N);
	moveFront(N->Long);
	if(N->sign == -1){
		fprintf(out, "-");
	}
	//int i = POWER;
	fprintf(out, "%ld ", get(N->Long));
	moveNext(N->Long);
	while(index(N->Long) != -1){
	//	printf("in print while\n");
		fprintf(out, "%0*ld ", POWER, get(N->Long));
		moveNext(N->Long);
	}
	fprintf(out, "\n");
	//makeZero(temp);
	//free(temp);
	//moveFront(N->Long);
}






