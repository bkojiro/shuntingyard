#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
 public:
  Node(char a);
  ~Node();
  char getData();
  Node* getLeft();
  Node* getRight();
  Node* getNext();
  void setLeft(Node* node);
  void setRight(Node* node);
  void setNext(Node* node);
 private:
  char data;
  Node* next;
  Node* left;
  Node* right;
};

#endif
