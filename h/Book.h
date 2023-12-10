#ifndef BOOK_H
#define BOOK_H
#include "Node.h"
#include <ostream>
#include <string>

class Book : public Node {
public:
  // Constructor
  Book();
  Book(string ID, string name, string belongUserID);

  // Destructor
  ~Book() = default;

  // getter and setter
  string getName();
  void setName(string name);
  string getBelongUserID();
  void setBelongUserID(string userID);

  // overwrite operater =
  Node &operator=(Node &node);

  // implement virtual function
  void print(ofstream &os);
  void print();

private:
  string name;
  string BelongUserID; // if it's null then it's in the library, otherwise it's
                       // in the user's book list
};

#endif // ndef
