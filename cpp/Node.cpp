//
// Created by 31320 on 2023/9/29.
//

#include "../h/Node.h"
using namespace std;

// Constructor
Node::Node() {
  this->ID = "";
  this->left = nullptr;
  this->right = nullptr;
  this->height = 1;
}

Node::Node(string ID) {
  this->ID = ID;
  this->left = nullptr;
  this->right = nullptr;
  this->height = 1;
}

// Destructor
Node::~Node() {
  this->ID = "";
  this->left = nullptr;
  this->right = nullptr;
  this->height = 0;
}

// getter and setter
string Node::getID() { return this->ID; }

void Node::setID(string ID) { this->ID = ID; }

int Node::getHeight() { return this->height; }

void Node::setHeight(int height) { this->height = height; }

void Node::updateHeight() {
  if (this->left == nullptr && this->right == nullptr) {
    this->height = 1;
  } else if (this->left == nullptr) {
    this->height = this->right->getHeight() + 1;
  } else if (this->right == nullptr) {
    this->height = this->left->getHeight() + 1;
  } else {
    this->height = max(this->left->getHeight(), this->right->getHeight()) + 1;
  }
}

// over write operator: > < = ==
bool Node::operator>(Node &node) { return this->ID > node.getID(); }

bool Node::operator<(Node &node) { return this->ID < node.getID(); }

bool Node::operator==(Node &node) { return this->ID == node.getID(); }

Node &Node::operator=(Node &node) {
  this->ID = node.getID();
  this->left = node.left;
  this->right = node.right;
  this->height = node.getHeight();
  return *this;
}
