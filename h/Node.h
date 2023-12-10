#ifndef NODE_H
#define NODE_H
#include <ostream>
#include <string>
#include "AVLTree.h"
using namespace std;


// Node class
class Node {
public:
  // Constructor
  Node();
  Node(string ID);

  // Destructor
  virtual ~Node() = 0;

  // getter and setter
  string getID();
  void setID(string ID);

  int getHeight();
  void setHeight(int height);
  void updateHeight();

  // over write operator: > < = ==
  virtual bool operator>(Node &node);
  virtual bool operator<(Node &node);
  virtual bool operator==(Node &node);
  virtual Node &operator=(Node &node);


  // virtual function that need to be implemented in derived class
  virtual void print(ofstream& os) = 0;
  virtual void print() = 0;
  virtual string getPassword(){return "";};
  virtual bool getAdmin(){return false;};
  virtual string getBelongUserID(){return "";};
  virtual void setBelongUserID(string ID){};
  virtual string getName(){return "";};

  // left child
  Node *left;
  // right child
  Node *right;

protected:
  // ID
  string ID;
  // height
  int height;
};

#endif // NODE_H
