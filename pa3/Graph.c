
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
   int *distance; 

   int order; 
   int size; 
   int source;
}GraphObj;

typedef struct GraphObj* Graph;
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having
//n vertices and no edges. 
Graph newGraph(int n){

    Graph G = malloc(sizeof(GraphObj));

    G->adjacent = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));

    G->order = n;
    G->size = 0;
    G->source = NIL;

    for(int i = 0; i<(n+1); i++){

        G->adjacent[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;

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
    free((*pG)->distance);
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

int getSource(Graph G){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getSource() on NULL Graph reference\n");
        exit(1);
    }
    return G->source;
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


int getDist(Graph G, int u){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getDist() on NULL Graph reference\n");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling getParent() while vertex not found\n");
        exit(1);
    }
    if(getSource(G) == NIL)
    {
      return INF;
    }

    return G->distance[u];
}


void getPath(List L, Graph G, int u){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling getPath() on NULL Graph reference");
        exit(1);
    }

    if(getSource(G) == NIL)
    {
        printf( "Graph.c ERROR: calling getPath() on NULL Graph source");
        exit(1);
    }
    if(!(u >= 1 && u <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling getPath() on invalid Graph reference");
        exit(1);
    }
    if(u == G->source)
    {
        append(L, G->source);
    }
    else if(G->parent[u] == NIL)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, G->parent[u]);
        append(L,u);
    }
}

void makeNull(Graph G)
{
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling makeNull() on NULL Graph reference");
        exit(1);
    }
    
    for(int i = 0; i < (getOrder(G) + 1); i++)
    {
        clear(G->adjacent[i]);
    }

    G->size = 0;
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


void BFS(Graph G, int s){
    if(G == NULL)
    {
        printf( "Graph.c ERROR: calling addEdge() on NULL Graph reference");
        exit(1);
    }
    if(!(s >= 1 && s <= getOrder(G)))
    {
        printf( "Graph.c ERROR: calling addEdge() while out of bounds");
        exit(1);
    }

    for(int i = 0; i < (G->order +1); i++){

	G->color[i] = WHITE;
	G->distance[i] = INF;
        G->parent[i] = NIL;

    }

    
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List L = newList();
    prepend(L,s);

    while(length(L) > 0)
    {
        int x = front(L);
        deleteFront(L);

        moveFront(G->adjacent[x]);


        while(index(G->adjacent[x]) >= 0)
        {
            int u = get(G->adjacent[x]);

            if(G->color[u] == WHITE)
            {
                G->color[u] =  GRAY;
                G->parent[u] = x;
                G->distance[u] = G->distance[x] + 1;
                append(L,u);
            }
            moveNext(G->adjacent[x]);
        }
        G->color[x] = BLACK;
    }
    freeList(&L);
}
//prints the adjacentacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){

    if(out == NULL || G == NULL) {
      printf("Graph.c ERROR: calling printGraph() on NULL Graph reference");
      exit(1);
   }
   
   for(int i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adjacent[i]);
      fprintf(out, "\n");
   }
}
