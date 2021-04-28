#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int n;

   int u,v; //vertices

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

   List S = newList();

   for (int i = 0; i < n; i++){
      append(S, i);
   }

   while (fgetc(in) != EOF){

      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);

      if (u == 0 && v == 0){
         break;
      }

      addArc(G, u, v);

   }

   DFS(G,S);

   Graph T = transpose(G);
   DFS(T, S);

   moveFront(S);

   int temp = 0;

   for (int i = 0; i < getOrder(T); i++){                                                             //

      if(getParent(T, i) == NIL)
      {  temp++;  }

      moveNext(S);
   }

   List *tempL = calloc(temp + 1, sizeof(List));

   for(int i = 0; i < temp; i++){

      tempL[i] = newList();

   }

   moveFront(S);

   int tempCount = temp;

   while(index(S) >= 0){

      if(getParent(T,get(S)) == NIL)
         {  tempCount--; }

      if(tempCount == temp)
         {  
		fprintf(out, "oof");
		break;  }

      append(tempL[tempCount], get(S));
      moveNext(S);
   }
  //  while (fgetc(in) != EOF){

  //     fscanf(in, "%d", &src);
  //     fscanf(in, "%d", &dest);

  //     if (src == 0 && dest == 0){
  //        break;
  //     }

  //     BFS(G, src);
  //     List L = newList();
  //     getPath(L, G, dest);
  //     if (getDist(G, dest) == INF){
  //        fprintf(out, "The distance from %d to %d is infinity", src, dest);
	 // fprintf(out, "\n");
	 // fprintf(out, "No %d-%d path exists", src, dest);
	 // fprintf(out, "\n");
  //     }else{
  //        fprintf(out, "The distance from %d to %d is %d", src, dest, length(L)-1);
  //        fprintf(out, "\n");
  //        fprintf(out, "A shortest %d-%d path is: ", src, dest);
  //        printList(out , L);
  //        fprintf(out, "\n");

  //     }

  //     freeList(&L);

  //  }

   fprintf(out, "Adjacency list representation of G:");
   fprintf(out, "\n");

   printGraph(out, G);

   fprintf(out, "\nG contains %d strongly connected components: \n", temp);

   for(int pc = 0; pc < temp; pc++){

      fprintf(out, "Component %d: ", (pc + 1));
      printList(out, tempL[pc]);
      freeList(&(tempL[pc]));
      fprintf(out, "\n");

   }
   fprintf(out, "\n");

   freeGraph(&G);
   freeGraph(&T);
   freeList(&S);

   fclose(in);
   fclose(out);

   return(0);
}




