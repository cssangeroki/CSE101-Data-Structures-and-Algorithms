#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int n;

   int u,v; //vertices
   int src, dest;

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

      addEdge(G, u, v);

   }

   printGraph(out, G);

   while (fgetc(in) != EOF){

      fscanf(in, "%d", &src);
      fscanf(in, "%d", &dest);

      if (src == 0 && dest == 0){
         break;
      }

      BFS(G, src);
      List L = newList();
      getPath(L, G, dest);
      if (getDist(G, dest) == INF){
         fprintf(out, "The distance from %d to %d is infinity", src, dest);
	 fprintf(out, "\n");
	 fprintf(out, "No %d-%d path exists", src, dest);
	 fprintf(out, "\n");
      }else{
         fprintf(out, "The distance from %d to %d is %d", src, dest, length(L)-1);
         fprintf(out, "\n");
         fprintf(out, "A shortest %d-%d path is: ", src, dest);
         printList(out , L);
         fprintf(out, "\n");

      }

      freeList(&L);

   }

fprintf(out, "\n");
freeGraph(&G);

fclose(in);
fclose(out);

return(0);
}




