#include "graph.h"
#include <iostream>

Graph::Graph (int n) :  nVertex(n) {
  adjList = new link[nVertex];
  visited = new int[nVertex];
  for (int i = 0; i < n; ++i) adjList[i] = 0;
}

bool Graph::addArch (int x, int y) {
  if (x < nVertex && y < nVertex) {    
    adjList[x] = new Node(y, adjList[x]);
    adjList[y] = new Node(x, adjList[y]);
    return true;
  }
  return false;
}

void Graph::build (const char* v) {;
  int e[2], i;
  i = 0;
  while (*v != 0) {
    
    if (*v == ' ') v++;

    if (*v >= '0' && *v <= '9') {
      e[i] = *v++ - '0';
      while (*v >= '0' && *v <= '9') {
	e[i] = e[i]*10 + *v++ - '0';
      }
      ++i;
    }

    if (i == 2) {
      addArch(e[0], e[1]);
      i = 0;
    }
    
  }
}

void Graph::recDepthFirst (void) {
  for (int i = 0; i < nVertex; ++i) visited[i] = 0;
  recTraversal(0);
  std::cout << std::endl;
}

void Graph::recTraversal (int v) {
  
  for (int i = v; i < nVertex; ++i) {
   
    link t = adjList[i];
    if(!visited[i]) {
      std::cout << i << " ";
      visited[i] = 1;
    
      while (t != 0) {
	if (!visited[t->item]) {
	recTraversal(t->item);
      }
      t = t->next;
      }
    }
  }
}
