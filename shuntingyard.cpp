#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

bool isValid(char c);
void push(Node* &stack, char c);
void push(Node* &stack, Node* branch);
char pop(Node* &stack);
Node* treePop(Node* &stack);
char peek(Node* stack);
void enqueue(Node* &queue, char c);
char dequeue(Node* &queue);
void printIn(Node* current);
void printPost(Node* current);
void printPre(Node* current);

int main() {
  Node* queue = new Node(0);
  Node* stack = new Node(0);
  cout << "Enter an equation in infix form" << endl << "> ";
  char input[30];
  cin.get(input, 31);
  cin.ignore();
  //CONVERT TO POSTFIX
  for(int a = 0; a < strlen(input); a++) {
    if (input[a] < 58 && input[a] > 48) {//makes sure its an int btw 1-9
      enqueue(queue, input[a]);
    } else if (isValid(input[a])) {
      push(stack, input[a]);
    } else if ((int)input[a] == 41) { // ), right parenthesis
      while (peek(stack) != '(') { //keep adding to queue until left parenthesis
        enqueue(queue, pop(stack));
      }
      char temp = pop(stack);
      temp = 0;
    }
  }
  while (stack->getNext() != NULL) { //if all inputs are pushed/enqueued, push rest of queue
    enqueue(queue, pop(stack));
  }
  
  //CONVERT TO EXPRESSION TREE
  Node* tree = new Node(0); //STACK
  while (queue->getNext() != NULL) {
    char a = dequeue(queue);
    if (a < 58 && a > 48) {
      push(tree, new Node(a));
    } else {
      Node* temp = new Node(a);
      temp->setRight(treePop(tree));
      temp->setLeft(treePop(tree));
      push(tree, temp);
    }
  }
  delete queue;
  delete stack;
  cout << "POSTFIX: ";
  printPost(tree->getNext());
  cout << endl;
  
  //SET UP OUTPUT METHOD
  bool active = true;
  while (active) {
    cout << "Enter INFIX, POSTFIX, or PREFIX to view output, or QUIT to exit" << endl << "> ";
    char outputAction[10];
    cin.get(outputAction, 11);
    cin.ignore();
    if (strcmp(outputAction, "INFIX") == 0) {
      //output infix notation
      printIn(tree->getNext());
      cout << endl;
    } else if (strcmp(outputAction, "POSTFIX") == 0) {
      //output postfix notation
      printPost(tree->getNext());
      cout << endl;
    } else if (strcmp(outputAction, "PREFIX") == 0) {
      //output prefix notation
      printPre(tree->getNext());
      cout << endl;
    } else if (strcmp(outputAction, "QUIT") == 0) {
      //terminate program
      active = false;
    }
  }
  return 0;
}

void printIn(Node* current) {
  if (isValid(current->getData())) {
    cout << "(";
    if (isValid(current->getLeft()->getData())) {
      printIn(current->getLeft());
    } else {
      cout << current->getLeft()->getData(); //<< current->getData();
    }
    cout << current->getData();
    if (isValid(current->getRight()->getData())) {
      printIn(current->getRight());
    } else {
      cout << current->getRight()->getData();
    }
    cout << ")";
  }
}

void printPost(Node* current) {
  if (current->getLeft() != NULL) {
    printPost(current->getLeft());
  }
  if (current->getRight() != NULL) {
    printPost(current->getRight());
  }
  cout << current->getData();
}

void printPre(Node* current) {
  cout << current->getData();
  if (current->getLeft() != NULL) {
    printPre(current->getLeft());
  }
  if (current->getRight() != NULL) {
    printPre(current->getRight());
  }
}

bool isValid(char c) {
  if (c == 42 || //multiplication
      c == 43 || //addition
      c == 45 || //subtraction
      c == 47 || //division
      c == 94 || //exponent
      c == 40) { //left parenthesis
    return true;
  }
  return false;
}

void push(Node* &stack, Node* node) {
  Node* current = stack;
  while (current->getNext() != NULL) {
    current = current->getNext();
  }
  current->setNext(node);
}

void push(Node* &stack, char c) { //create node with value c
  Node* temp = new Node(c);
  Node* current = stack;
  while (current->getNext() != NULL) { //find end of stack LL
    current = current->getNext();
  }
  current->setNext(temp);
}

char pop(Node* &stack) {
  Node* current = stack;
  while (current->getNext() != NULL) {
    if (current->getNext()->getNext() == NULL) { //if next is last in list
      char popData = current->getNext()->getData();
      current->setNext(NULL);
      delete current->getNext();
      return popData;
    } else {
      current = current->getNext();
    }
  }
  return 0;
}

Node* treePop(Node* &stack) {
  Node* current = stack;
  while (current->getNext() != NULL) {
    if (current->getNext()->getNext() == NULL) { //if next is last in list
      Node* popData = current->getNext();
      current->setNext(NULL);
      delete current->getNext();
      return popData;
    } else {
      current = current->getNext();
    }
  }
  return 0;
}
  
char peek(Node* stack) {
  Node* current = stack;
  while (current->getNext() != NULL) {
    if (current->getNext()->getNext() == NULL) { //if next is last in list
      return current->getNext()->getData();
    } else {
      current = current->getNext();
    }
  }
  return 0;
}

void enqueue(Node* &queue, char c) { //do the same as push but with queue
  push(queue, c);
}			    

char dequeue(Node* &queue) {
  char c = 0;
  if (queue->getNext() != NULL) {
    c = queue->getNext()->getData();
    Node* temp = queue->getNext();
    queue->setNext(queue->getNext()->getNext());
    delete temp;
  }
  return c;
}
