
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct GraphObj
{
    List* neighbors;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order; // number of vertices
    int size; // number of edges
}GraphObj;

typedef struct GraphObj* Graph;

// newGraph()
// creats a new graph 'object'
Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    //printf("in newGraph(): G malloc address: %p\n", G);
    G->neighbors = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));    
    
    G->order = n;
    G->size = 0;
    for (int i = 1; i <= n; i++)
    {
        G->neighbors[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}

// freeGraph()
// frees all the memory allocated
// for the graph
void freeGraph(Graph* pG)
{
    Graph ptr = *pG;
    //printf("in freeGraph(): ptr is: %p\n", ptr);
    //printf("in freeGraph(): *pG is: %p\n", *pG);
    // free list first
    for(int i = 1; i <= getOrder(ptr); i++)
    {
        freeList(&(ptr->neighbors[i]));
    }

    // free rest and set *pG to NULL
    free(ptr->neighbors);
    free(ptr->color);
    free(ptr->parent);
    free(ptr->discover);
    free(ptr->finish);

    // finally free *pG
    //printf("in freeGraph(): free(*pG) called!!\n");
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/

// getOrder()
// gets the number of vertices
// in the graph
int getOrder(Graph G)
{
    if (G == NULL)
    {
        printf("Graph error: cannot getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

// getSize()
// returns the number of vertices
// in the graph
int getSize(Graph G)
{
    if (G == NULL)
    {
        printf("Graph error: cannot getSize() on NULL graph reference\n");
        exit(1);
    }
    return G->size;
}

// getParent()
// gets the parent vertex
// pre: 1<=u<getOrder(G)
int getParent(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph error: cannot getSource() on NULL Graph reference\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        printf("Graph error: cannot getParent() if u is out of bounds\n");
        exit(1);
    }
    return G->parent[u];
}

// getDiscover()
// gets discover time of vertex
int getDiscover(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph error: cannot getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        printf("Graph error: cannot getParent() if u is out of bounds\n");
        exit(1);
    }
    return G->discover[u];
}

// getFinish()
// gets finish time of vertex
int getFinish(Graph G, int u)
{
    if (G == NULL)
    {
        printf("Graph error: cannot getFinish() on NULL Graph reference\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        printf("Graph error: cannot getParent() if u is out of bounds\n");
        exit(1);
    }
    return G->finish[u];
}

// addSortedEdge()
// helper for addEdge() in sorted order
// by using a modified insertion sort algorithm
// note: came directly from pa4
void addSortedEdge(List L, int v)
{
    //printf("in addSortedEdge(): v is: %d\n", v);
    if (L == NULL)
    {
        printf("Graph error: cannot addSortedEdge() on NULL List reference\n");
        exit(1);
    }
    if (length(L) == 0)
    {
        append(L, v);
        return;
    }    
    moveFront(L);
    while (index(L) != -1)
    {
        if (v < get(L))
        {
            insertBefore(L, v);
            break;
        }
        moveNext(L);
    }
    if (index(L) == -1)
    {
        append(L, v);
    }
}

// addEdge()
// adds an directed edge to the current graph
// note: taken from pa4
void addEdge(Graph G, int u, int v)
{
    //printf("in addEdge(): u is: % d, v is: %d\n", u, v);
    if (G == NULL)
    {
        printf("Graph error: cannot addEdge() on NULL Graph reference\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        printf("Graph error: cannot getPath() if u is out of bounds\n");
        exit(1);
    }
    if (!(1 <= v && v <= getOrder(G)))
    {
        printf("Graph error: cannot getPath() if v is out of bounds\n");
        exit(1);
    }
    addSortedEdge(G->neighbors[u], v);
    addSortedEdge(G->neighbors[v], u);
    G->size++;
}

// addArc()
// adds undirected edge to graph
// note: directly from pa4
void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        printf("Graph error: cannot addArc() on NULL Graph reference\n");
        exit(1);
    }
    if (!(1 <= u && u <= getOrder(G)))
    {
        printf("Graph error: cannot getPath() if u is out of bounds\n");
        exit(1);
    }
    if (!(1 <= v && v <= getOrder(G)))
    {
        printf("Graph error: cannot getPath() if v is out of bounds\n");
        exit(1);
    }
    addSortedEdge(G->neighbors[u], v);
    G->size++;
}

// DFS()
// implements the DFS algorithm presented in class
// pre: length(S)==getOrder(G)
void DFS(Graph G, List S) 
{
    if (G == NULL)
    {
        printf("Graph error: cannot DFS() on NULL Graph reference\n");
        exit(1);
    }
    if (S == NULL)
    {
        printf("Graph error: cannot DFS on NULL List reference\n");
        exit(1);
    }
    if (length(S) != getOrder(G)) 
    {
        printf("Graph error: cannot DFS() if length(S) != getOrder(G)\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); i++) 
    {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    moveFront(S);
    while (index(S) >= 0) 
    {
        int u = get(S);
        //printf("in DFS(): u is: %d\n", u);
        if (G->color[u] == WHITE) 
        {
            visit(G, S, u, &time);
        }
        moveNext(S);
    }
    for (int i = 0; i < getOrder(G); i++) 
    {
        deleteBack(S);
    }
}

// visit()
// helper function for DFS()
void visit(Graph G, List S, int u, int *time) 
{
    if (G == NULL)
    {
        printf("Graph error: cannot DFS() on NULL Graph reference\n");
        exit(1);
    }
    if (S == NULL)
    {
        printf("Graph error: cannot DFS on NULL List reference\n");
        exit(1);
    }
    G->discover[u] = ++*time;
    G->color[u] = GRAY;
    moveFront(G->neighbors[u]);
    while (index(G->neighbors[u]) >= 0) 
    {
        int y = get(G->neighbors[u]);
        //printf("int visit(): y is: %d\n", y);
        //printf("in visit(): G->parent[y] is: %d\n", G->parent[y]);
        if (G->color[y] == WHITE) 
        {
            G->parent[y] = u;
            //printf("in visit(): u is: %d\n", u);
            //printf("in visit(): G->parent[y] is: %d\n", G->parent[y]);
            visit(G, S, y, time);
        }
        moveNext(G->neighbors[u]);
    }
    G->color[u] = BLACK;
    G->finish[u] = ++*time;
    prepend(S, u);
}

/*** Other Functions ***/

// transpose()
// transposes a graph by switching directions
Graph transpose(Graph G) 
{
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) 
    {
        moveFront(G->neighbors[i]);
        if (length(G->neighbors[i]) == 0) 
        {
            continue;
        }
        else 
        {
            while (index(G->neighbors[i]) != -1) 
            {
                addArc(T, get(G->neighbors[i]), i);
                moveNext(G->neighbors[i]);
            }
        }
    }
    return T;
}

// copyGraph()
// returns a copy of the current graph
Graph copyGraph(Graph G) 
{
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) 
    {
        moveFront(G->neighbors[i]);
        if (length(G->neighbors[i]) == 0)
        {
            continue;
        }
        else
        {
            while (index(G->neighbors[i]) >= 0) 
            {
                addArc(C, i, get(G->neighbors[i]));
                moveNext(G->neighbors[i]);
            }
        }
    }
    return C;
}

// printGraph()
// prints a graph to a file
// or stdout
void printGraph(FILE* out, Graph G)
{
    if (G == NULL)
    {
        printf("Graph error: printGraph() called on NULL Graph reference\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); i++)
    {
        //printf("int printGraph(): i is: %d\n", i);
        List list = G->neighbors[i];
        fprintf(out, "%d:", i);
        moveFront(list);
        //printf("printGraph(): index is: %d\n", index(list));
        while (index(list) != -1)
        {
            fprintf(out, " %d", get(list));
            moveNext(list);
        }
        fprintf(out, "\n");
    }
}