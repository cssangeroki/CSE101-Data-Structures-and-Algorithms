//Name: Claudio Sangeroki
//ID  : 1677403
//pa4


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 500

int main(int argc, char * argv[]){

   int n = 0;

   int u,v;
   u = 0;
   v = 0; //vertices

   FILE *in, *out;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   fscanf(in, "%d", &n);
   Graph G = newGraph(n);

   while (fgetc(in) != EOF){

      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);

      if (u == 0 && v == 0){
         break;
      }

      addArc(G, u, v);
   }




   List S = newList();

   for (int i = 0; i < n; i++){

      append(S, (i+1));

   }

   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);
   fprintf(out, "\n");

   DFS(G,S);

   Graph T = transpose(G);
   DFS(T, S);

   int scc = 0;

   for(int i = 0; i < getOrder(T); i++){                                                             //

      if(getParent(T, (i+1)) == NIL)
      {  scc++;  }

   }

  fprintf(out, "G contains %d strongly connected components: \n", scc);

  int tempCount = 1;
  List tempL = newList();

   for(moveBack(S); index(S) >= 0; movePrev(S)){

      prepend(tempL, get(S));

      if(getParent(T,get(S)) == NIL)
         {  
            fprintf(out, "Component %d: ", tempCount);
            printList(out, tempL);
        
            fprintf(out, "\n");

            clear(tempL);  
            tempCount++; 

        }

   }

   fprintf(out, "\n");

   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);
   freeList(&tempL);

   fclose(in);
   fclose(out);

   return(0);
}




