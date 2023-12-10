#include "../h/User.h"
#include <iostream>
#include <ostream>
#include <fstream>
using namespace std;


// Constructor
User::User() {
  this->ID = "";
  this->password = "";
  this->left = nullptr;
  this->right = nullptr;
  this->isAdmin = false;
  this->height = 1;
}

User::User(string ID, string password, bool isAdmin) {
  this->ID = ID;
  this->password = password;
  this->isAdmin = isAdmin;
  this->left = nullptr;
  this->right = nullptr;
  this->height = 1;
}
 
User::User(User& user){
  this->ID = user.ID;
  this->password = user.password;
  this->left = user.left;
  this->right = user.right;
  this->isAdmin = user.isAdmin;
  this->height = user.height;
}

// overwrite operater =
Node& User::operator=(Node& user){
  this->ID = user.getID();
  this->password = user.getPassword();
  this->isAdmin = user.getAdmin();
  this->height = user.getHeight();
  return *this;
}

// getter and setter
string User::getPassword() { return this->password; }
void User::setPassword(string password) { this->password = password; }
bool User::getAdmin() { return this->isAdmin; }
void User::setAdmin(bool isAdmin) { this->isAdmin = isAdmin; }

// implement virtual function
void User::print(ofstream& os){
  os << this->ID << " " << this->password;
  if(this->isAdmin){
    os << " " << "1";
  }else{
    os << " " << "0";
  }
  os << endl;
}

void User::print(){
  cout << "ID: " << this->ID << ' ' << "password: " << this->password << ' ' << "isAdmin: " << this->isAdmin << endl;
}
