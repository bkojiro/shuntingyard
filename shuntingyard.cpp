#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

void push(Node* &stack, char c);
int pop(Node* &stack);
void enqueue(Node* &queue, char c);

int main() {
  Node* stack = new Node(0);
  Node* queue = new Node(0);
  cout << "Enter an equation in infix form" << endl << "> ";
  char input[30];
  cin.get(input, 31);
  cin.ignore();
  //CONVERT TO POSTFIX
  for(int a = 0; a < strlen(input); a++) {
    if (input[a] < 58 && input[a] > 48) {//makes sure its an int btw 1-9
      push(stack, input[a]);
    } else if (input[a] == 42 || // *, multiplication
	       input[a] == 43 || // +, addition
	       input[a] == 45 || // -, subtraction
	       input[a] == 47 || // /, division
	       input[a] == 94 || // ^, exponent
	       input[a] == 95) { // _, negation
      enqueue(queue, input[a]);
    }
  }
  cout << pop(stack);
  return 0;
}



void push(Node* &stack, char c) { //create node with value c
  Node* temp = new Node('c');
  Node* current = stack;
  while (current->getNext() != NULL) { //find end of stack LL
    current = current->getNext();
  }
  current->setNext(temp);
}

int pop(Node* &stack) {
  Node* current = stack;
  while (current->getNext() != NULL) {
    if (current->getNext()->getNext() == NULL) { //if next is last in list
      char popData = current->getNext()->getData();
      current->getNext()->~Node();
      current->setNext(NULL);
      delete current->getNext();
      return (int)popData;
    } else {
      current = current->getNext();
    }
  }
  return 0;
}

void enqueue(Node* &queue, char c) { //do the same as push but with queue
  push(queue, c);
}			    
