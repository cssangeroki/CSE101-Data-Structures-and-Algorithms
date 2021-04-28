
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj{

   List *adjacent; 

   int *color; 
   int *parent; 
   int *discover; 
   int *finish;

   int order; 
   int size; 

}GraphObj;

typedef struct GraphObj* Graph;
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having
//n vertices and no edges. 
Graph newGraph(int n){

    Graph G = malloc(sizeof(GraphObj));

    G->adjacent = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));

    G->order = n;
    G->size = 0;

    for(int i = 0; i<(n+1); i++){

        G->adjacent[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;

    }

    return G;

}
//Function freeGraph() frees all dynamic memory associated with the Graph
//*pG, then sets the handle *pG to NULL. 
void freeGraph(Graph* pG){
    
    for(int i = 0; i<=getOrder(*pG); i++)
    {
        freeList(&((*pG)->adjacent[i]));
    }

    free((*pG)->adjacent);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    free((*pG)->color);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

int getSize(Graph G){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

int getParent(Graph G, int u){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling getParent() while vertex not found\n");
        exit(1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling getDiscover() while vertex not found\n");
        exit(1);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getFinish() on NULL Graph reference\n");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling getFinish() while vertex not found\n");
        exit(1);
    }
    return G->finish[u];
}

void addEdge(Graph G, int u, int v){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() on NULL Graph reference");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling addEdge() while out of bounds");
        exit(1);
    }
    
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}


void addArc(Graph G, int u, int v){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() on NULL Graph reference");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling addEdge() while out of bounds");
        exit(1);
    }

    moveFront(G->adjacent[u]);
    while (index(G->adjacent[u]) != -1)
    {
        if (v < get(G->adjacent[u]))
        {
            insertBefore(G->adjacent[u], v);
            break;
        }
        moveNext(G->adjacent[u]);
    }
    if (index(G->adjacent[u]) == -1)
    {
        append(G->adjacent[u], v);
    }

    G->size++;
}


void DFS(Graph G, List S){

    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() on NULL Graph reference");
        exit(1);
    }
    if(S == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() while out of bounds");
        exit(1);
    }

    for(int i = 0; i < (getOrder(G) + 1); i++){

	    G->color[i] = WHITE;
        G->parent[i] = NIL;

    }

    int time = 0;

    moveFront(S);

    while (index(S) >= 0){

        int x = get(S);

        if(G->color[u] == WHITE)
        { visit(G,S,x, &time); }

        moveNext(S);

    }

    freeList(&S);
 
}

void visit(Graph G, List S, int x, int *time){

    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() on NULL Graph reference");
        exit(1);
    }
    if(S == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() while out of bounds");
        exit(1);
    }

    G->discover[x] = ++*time;
    G->color[x] = GRAY;
    moveFront(G->adjacent[x]);

    while(index(G->adjacent[x]) >= 0){

        int y = get(G->adjacent[x]);

        if (G->color[y] == WHITE){

            G->parent[y] = x;
            visit (G, S, y, time);

        }
        moveNext(G->adjacent[x]);
    }
    
    G->color[x] = BLACK;
    G->finish[x] = ++*time;
    prepend (S, x);
}
//prints the adjacentacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){

    if(out == NULL || G == NULL) {
      printf("Graph.c ERROR: calling printGraph() on NULL Graph reference");
      exit(1);
   }
   
   for(int i = 0; i < getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adjacent[i]);
      fprintf(out, "\n");
   }
}

Graph transpose(Graph G){

    if(G == NULL) {
      printf("Graph.c ERROR: calling transpose() on NULL Graph reference");
      exit(1);
   }

    Graph G2 = newGraph(getOrder(G));
    for(int i = 0; i < getOrder(G); i++){

        moveFront(G->adjacent[i]);
        while(index(G->adjacent[i]) >= 0){

            addArc(G2, get(G->adjacent[i]), i);
            moveNext(G->adjacent[i]);

        }


    }
    return G2;
}

Graph copyGraph(Graph G){

    if(G == NULL) {
      printf("Graph.c ERROR: calling copyGraph() on NULL Graph reference");
      exit(1);
   }

   Graph G2 = newGraph(getOrder(G));

   for(int i = 0; i < getOrder(G); i++){

        moveFront(G->adjacent[i]);

        while(index(G->adjacent[i]) >= 0){

            addArc(G2, i, get(G->adjacent[i]));
            moveNext(G->adjacent[i]);

        }
   }

   return G2;
}