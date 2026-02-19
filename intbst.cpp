// intbst.cpp
// Implements class IntBST
// Mu'aaz Shaikh, January 30th, 2026

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
  root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
  clear(root);
  root = nullptr;
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
  if(!n) return;
  clear(n->left);
  clear(n->right);
  delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(!root){
      root = new Node{value};
      return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if(value == n->info) return false;
    if(value < n->info){
      if(!n->left){
        n->left = new Node{value};
	n->left->parent = n;
	return true;
      }
      return insert(value, n->left);
    }
    if(value > n->info){
      if(!n->right){
        n->right = new Node{value};
	n->right->parent = n;
	return true;
      }
      return insert(value, n->right);
    }
    return true;
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n) return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n) return 0;
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n) return nullptr;
    if(n->info == value) return n;
    if(value < n->info) return getNodeFor(value, n->left);
    if(value > n->info) return getNodeFor(value, n->right);
    return nullptr;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(!getNodeFor(value, root)) return false;
    return true;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if(!n) return nullptr;
    Node* curr = n;

    if(curr->left){
      curr = curr->left;
      while(curr->right) curr = curr->right;
      return curr;
    }
    if(!curr->left){
      while(curr->parent && curr->parent->left == curr){
        curr = curr->parent;
      }
      return curr->parent;
    }
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(!getPredecessorNode(value)) return 0;
    return getPredecessorNode(value)->info;    
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if(!n) return nullptr;
    Node* curr = n;

    if(curr->right){
      curr = curr->right;
      while(curr->left) curr = curr->left;
      return curr;
    }
    if(!curr->right){
      while(curr->parent && curr->parent->right == curr){
        curr = curr->parent;
      }
      return curr->parent;
    }
    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if(!getSuccessorNode(value)) return 0;
    return getSuccessorNode(value)->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* n = getNodeFor(value, root);
    if(!n) return false;
    if(!n->parent && !n->left && !n->right){
      delete root;
      root = nullptr;
      return true;
    }

    //0
    if(!n->left && !n->right){
      if(n->parent->left == n) n->parent->left = nullptr;
      else n->parent->right = nullptr;
      delete n;
      return true;
    }
    
    //1
    if(!n->left && n->right){
      if(!n->parent){
        root = n->right;
	root->parent = nullptr;
	delete n;
	return true;
      }
      if(n->parent->left == n){
        n->parent->left = n->right;
	n->right->parent = n->parent;
      }
      else{
        n->parent->right = n->right;
	n->right->parent = n->parent;
      }
      delete n;
      return true;
    }
    if(n->left && !n->right){
      if(!n->parent){
        root = n->left;
	root->parent = nullptr;
	delete n;
	return true;
      }
      if(n->parent->left == n){
        n->parent->left = n->left;
        n->left->parent = n->parent;
      }
      else if(n->parent->right == n){
        n->parent->right = n->left;
        n->left->parent = n->parent;
      }
      delete n;
      return true;
    }
    
    //2
    Node* curr = n->left;
    while(curr->right){
      curr = curr->right;
    }
    n->info = curr->info;
    if(curr->parent->left == curr) curr->parent->left = curr->left;
    else curr->parent->right = curr->left;
    if(curr->left) curr->left->parent = curr->parent;
    delete curr;
    return true;
}
