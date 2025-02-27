#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(char a) {
  data = a;
  next = NULL;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  data = 0;
  next = NULL;
  left = NULL;
  right = NULL;
}

char Node::getData() {
  return data;
}

Node* Node::getLeft() {
  return left;
}

Node* Node:: getRight() {
  return right;
}

Node* Node::getNext() {
  return next;
}

void Node::setLeft(Node* node) {
  left = node;
}

void Node::setRight(Node* node) {
  right = node;
}

void Node::setNext(Node* node) {
  next = node;
}
			    
