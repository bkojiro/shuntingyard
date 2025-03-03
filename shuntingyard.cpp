#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

bool isValid(char c);
void push(Node* &stack, char c);
char pop(Node* &stack);
char peek(Node* stack);
void enqueue(Node* &queue, char c);
char dequeue(Node* &queue);

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
  while (queue != NULL) {
    if (queue->getData() < 58 && queue->getData() > 48) {
      push(tree, dequeue(queue));
    } else if (isValid(queue->getData())) {
      if (queue->getData() == 94) { //unary operator
	
      } else { //binary operators
	Node* temp = new Node(dequeue(queue));
	temp->setLeft(pop(tree));
	temp->setRight(pop(tree));
	push(tree, temp);
      }
    }
  }
  
  return 0;
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

void treePush(Node* &tree, Node* branch) {
  //DO THIS
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
      current->getNext()->~Node();
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
    temp->~Node();
    delete temp;
  }
  return c;
}
