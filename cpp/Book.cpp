#include "../h/Book.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
Book::Book() {
  this->ID = "";
  this->name = "";
  this->BelongUserID = "";
}

Book::Book(string ID, string name, string belongUserID) {
  this->ID = ID;
  this->name = name;
  this->BelongUserID = belongUserID;
}

// getter and setter
string Book::getName() { return this->name; }

void Book::setName(string name) { this->name = name; }

string Book::getBelongUserID() { return this->BelongUserID; }

void Book::setBelongUserID(string userID) { this->BelongUserID = userID; }

// overwrite operater =
Node &Book::operator=(Node &book) {
  this->ID = book.getID();
  this->name = book.getName();
  this->BelongUserID = book.getBelongUserID();
  this->height = book.getHeight();
  return *this;
}

// implement the vitrual function
void Book::print(ofstream& os){
  os << this->ID << " " << this->name;
  if(this->BelongUserID != ""){
    os << " " << this->BelongUserID;
  }else{
    os << " " << "0";
  }
  os << endl;
}

void Book::print(){
    cout << "ID:" << this->ID << " " << "书籍名" << this->name << " ";
    if(this->getBelongUserID() == ""){
        cout << "书籍状态：未被借阅" << endl;
    }else{
        cout << "书籍状态：被用户" << this->getBelongUserID() << "借阅" << endl;
    }
}
