#include "graph.h"
#include <iostream>
#include <stack>
#include <queue>

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
    
    if(!visited[v]) {
        std::cout << v << " ";
        visited[v] = 1;
        
        for (link t = adjList[v]; t != 0; t = t->next) {
            if (!visited[t->item]) recTraversal(t->item);
        }
    }
}

void Graph::itDepthFirst (void) {
    
    std::stack<link> s;
    for (int i = 0; i < nVertex; ++i) visited[i] = 0;
    
    //visit first vertex and push its list
    s.push(adjList[0]);
    std::cout << 0 << " ";
    visited[0] = 1;
    
    while (!s.empty()) {
        //pop current vertex
        link t = s.top();
        s.pop();
        
        //push next vertex in the previous list
        if(t->next) s.push(t->next);
        
        //visit current vertex and push its list if not already visited
        if (!visited[t->item]) {
            std::cout << t->item << " ";
            visited[t->item] = 1;
            s.push(adjList[t->item]);
        }
    }
    std::cout << std::endl;
}

void Graph::breadthFirst (void) {
    
    std::queue<int> q;
    for (int i = 0; i < nVertex; ++i) visited[i] = 0;
    q.push(0);
    
    while (!q.empty()) {
        int t = q.front();
        q.pop();
        if(!visited[t]) {
            std::cout << t << " ";
            visited[t] = 1;
            for (link k = adjList[t]; k != 0; k = k->next) q.push(k->item);
        }
    }
}