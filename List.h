// Name: Ruben Calderon
// CruzID: rucalder
// Assignment Name: pa1


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct NodeObj* Node;
Node newNode(long data);
void freeNode(Node* pN);

// Constructors-Destructors ---------------------------------------------------
typedef struct ListObj* List;
List newList(void);
void freeList(List* pL);

// Access functions ----------------------------------------------------------
int length(List L);
int index(List L);
long front(List L);
long back(List L);
long get(List L);
//int equals(List A, List B);
int isEmpty(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, long data);
void append(List L, long data);
void set(List L, long data);
void insertBefore(List L, long data);
void insertAfter(List L, long data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);

#endif
