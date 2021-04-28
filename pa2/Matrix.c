//Name   : Claudio Sangeroki
//ID  : 1677403
//PA2
//Matrix ADT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"
#include "List.h"


typedef struct EntryObj{

int col;
double data;

}

typedef EntryObj* Entry;

typedef struct MatrixObj{

List *row;
int numRows;
int NNZ;

}MatrixObj;



//Constructors and Destructors

Entry newEntry(int col, double value){
Entry E = malloc(sizeof(EntryObj));
E->col = col;
E->data = data;
return (E);
}

void freeEntry(Entry* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

Matrix newEntry(int n){
Matrix M = malloc(sizeof(ListObj));

if (n < 1){
printf ("Matrix Error: newEntry")
exit(1)
}


M->row = new List[n+1];
for(int i = 1; i < (n+1); i++){
row[i] = new List();
}

}

void freeMatrix(Matrix* pM){
  if(pM != NULL && *pM != NULL) {
      Entry temp = (*pM)->front;
      while(temp != NULL) {
         Entry current = temp;
         temp = temp->next;
         free(current);
      }

      //deallocates the memory
      free(*pL);
      *pL = NULL;
   }

}

int size(Matrix M){
return strlen(M->row) - 1;
}

int NNZ(Matrix M){
int NNZ = 0
for (int i = 1; i <=getSize(); i++){
NNZ += row[i].length();
}
return NNZ;
}

int equals (Matrix A, Matrix B){

}

void makeZero (Matrix M){
}

