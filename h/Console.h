//
// Created by 31320 on 2023/9/30.
//

#ifndef CODE_CONSOLE_H
#define CODE_CONSOLE_H
#include "AVLTree.h"
#include "Book.h"
#include "Node.h"
#include "User.h"
#include <string>

class Console {
public:
  // Constructor
  Console();
  // init the console,namely read the data from the file and build the tree
  void init();

  // run the console
  void Run();
  void InitPage();
  void UserPage(); 
  void AdminPage();

  // UI
  static void WelcomeUI();
  static void UserUI(Node *node);
  static void AdminUI(Node *node);

  // other function
  static int GetUIChoice();
  static void CleanWindow();
  static void Pause();

  // main function
  bool Register(AVLTree &avlTree);
  Node *Login(AVLTree &avlTree);
  bool QueryBook( AVLTree &avlTree);

  // Admin
  bool AddBook(AVLTree &avlTree);
  bool DeleteBook(AVLTree &avlTree);
  bool DisplayBook(AVLTree &avlTree, bool isTree);
  bool DisplayUser(AVLTree &avlTree, bool isTree);
  bool DeleteUser(AVLTree& avlUserTree, AVLTree& avlBookTree);

  // Normal User
  bool BorrowBook(AVLTree &avlTree);
  bool ReturnBook(AVLTree &avlTree);
  bool DeleteSelf(AVLTree &avlUserTree, AVLTree& avlBookTree);

  // write User and Book to file
  void writeUserToFile();
  void writeBookToFile();

private:
  // User Tree
  AVLTree avlUserTree;
  AVLTree avlBookTree;

  // current user
  Node *currentUser;

  // next page
  int nextPage;

  // try to log in
  Node *TryLogin(AVLTree &avlTree);

  // UI
  static void LoginFailUI();
  static void ChangePasswordSuccessfullyUI();
  static void CannotChangePermissionUI();
  static void PermisstionBitMapExplainedUI();
};
#endif // CODE_CONSOLE_H
