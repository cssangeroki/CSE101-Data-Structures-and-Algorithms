
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL 0
#define UNDEF -1
#include "List.h"

typedef struct GraphObj* Graph; // exported type


/** Constructors-Destructors ***/

// newGraph()
// creates a new graph
Graph newGraph(int n);

// freeGraph()
// frees all memory related
// to the graph
void freeGraph(Graph* pG);

/*** Access Functions ***/

// getOrder()
// gets the number of vertices
// of the graph
int getOrder(Graph G);

// getSize()
// get number of edges in the graph
int getSize(Graph G);

// getParent()
// gets the parent of the current vertex
int getParent(Graph G, int u);

// getDiscover()
// gets discover time of vertex
// pre: 1<=u<=getOrder(G);
int getDiscover(Graph G, int u);

// getFinish()
// gets finish time of vertex
// pre: 1<=u<=getOrder(G);
int getFinish(Graph G, int u);

/*** Manipulation Procedures ***/

// addArc()
// adds directed edge to vertex
// pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v);

// addEdge()
// adds undirected edge to vertex
// pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v);

// DFS()
// performs the DFS algorithm presented 
// in class
void DFS(Graph G, List S);

// visit()
// helper function for DFS()
void visit(Graph G, List S, int u, int *time);

/*** Other Functions ***/

// transpose()
// trasposes a directed graph by reversing
// the direction of the the arrows
Graph transpose(Graph G);

// copyGraph()
// makes a copy of the graph
Graph copyGraph(Graph G);

// printGraph()
// prints graph to file or stdout
void printGraph(FILE* out, Graph G);

#endif