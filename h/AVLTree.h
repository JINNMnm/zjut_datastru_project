//
// Created by 31320 on 2023/9/29.
//

#ifndef CODE_AVLTREE_H
#define CODE_AVLTREE_H
#include <string>
using namespace std;

class Node;

class AVLTree {
public:
  // constructor
  AVLTree();

  // destructor
  ~AVLTree();
  void destroy(Node *root);

  // getter and setter
  Node *getRoot();
  void setRoot(Node *root);
  int getDepth();

  // insert a node
  bool add(Node *newNode);
  // delete a node
  bool del(string targetID);

  // traverse the tree to display
  // Write to file
  void writeToFile(ofstream &outFile, Node *root);

  // load from file
  void loadFromFile(ifstream &inFile);

  // display the tree
  bool displayTree();
  bool diaplay();

  // when deleye a user, we need to check if the user have returned all the books
  bool isUserHaveBook(string userID);

  // search for a node
  Node* search(string targetID);
private:
  Node *root; // root of the tree
  
  // insert a node
  bool add(Node *newNode, Node *&root);
  // delete a node
  bool del(string targetID, Node* &root);
  // search for a node
  Node* search(string targetID, Node *root);
  // displayTree
  bool displayTree(Node* T, int depth, int right, int tap);
  bool display(Node* T);
  // check if the user have books
  bool isUserHaveBook(string userID, Node* root);
  

  // rotare the tree
  Node *LL(Node* root);
  Node *RR(Node* root);
  Node *LR(Node* root);
  Node *RL(Node* root);

  // tell if tree need LL? RR? LR? RL?
  bool needLL(Node *root);
  bool needRR(Node *root);
  bool needLR(Node *root);
  bool needRL(Node *root);
};

#endif // CODE_AVLTREE_H
