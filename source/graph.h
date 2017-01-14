#ifndef GRAPH_H
#define GRAPH_H

typedef int Item;

class Graph {
  struct Node {
    Item  item;
    Node* next;
    Node (Item x, Node* n) {item = x; next = n;};
  };
  typedef Node* link;
  link* adjList;
  const int nVertex;
  int* visited; //vertex already visited
  void recTraversal (int v);
 public:
  Graph (int n);
  bool addArch (int x, int y);
  void build (const char* v);
  void recDepthFirst (void);
  void itDepthFirst (void);
};

#endif
