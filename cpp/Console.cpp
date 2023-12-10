//
// Created by 31320 on 2023/9/30.
//

#include "../h/Console.h"
#include "../h/const.h"
#include <assert.h>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

// Constructor
Console::Console() {
  // init the user tree
  avlUserTree = AVLTree();
  avlBookTree = AVLTree();
  nextPage = 1;

  // init the default user
  currentUser = NULL;
}

void Console::init() {
  // read the data from the file
  ifstream userFile;
  userFile.open(USER_FILE_PATH);
  if (userFile.is_open()) {
    avlUserTree.loadFromFile(userFile);
  }
  userFile.close();

  // read the data from the file
  ifstream bookFile;
  bookFile.open(BOOK_FILE_PATH);
  if (bookFile.is_open()) {
    avlBookTree.loadFromFile(bookFile);
    // avlBookTree.displayTree();
  }
  bookFile.close();
}

void Console::Run() {
  switch (nextPage) {
  case 1:
    InitPage();
    break;
  case 2:
    UserPage();
    break;
  case 3:
    AdminPage();
    break;
  case 4:
    // close
    cout << "感谢使用!" << endl;
    Pause();
    exit(0);
  }
}

void Console::InitPage() {
  // welcome ui and get the choice
  CleanWindow();
  Console::WelcomeUI();

  int choice = Console::GetUIChoice();

  switch (choice) {
  case UI_LOGIN:
    // login
    currentUser = Login(avlUserTree);
    if (currentUser != NULL) {
      if (currentUser->getAdmin() == false) {
        nextPage = 2;
      } else {
        nextPage = 3;
      }
    }
    Pause();
    break;
  case UI_REGISTER:
    // register
    Console::Register(avlUserTree);
    Pause();
    break;
  case UI_CLOSE:
    // close
    nextPage = 4;
    break;
  }
}

// User Page
void Console::UserPage() {
  // user ui and get the choice
  CleanWindow();
  Console::UserUI(currentUser);

  int choice = Console::GetUIChoice();

  switch (choice) {
  case USER_BORROW_BOOK:
    // borrow book
    BorrowBook(avlBookTree);
    Pause();
    break;
  case USER_RETURN_BOOK:
    // return book
    ReturnBook(avlBookTree);
    Pause();
    break;
  case USER_QUERY_BOOK:
    // query book
    QueryBook(avlBookTree);
    Pause();
    break;
  case USER_DELETE_SELF:
    // delete self
    if (DeleteSelf(avlUserTree, avlBookTree)) {
      nextPage = 1;
    } else {
      nextPage = 2;
    }
    Pause();
    break;
  case USER_LOGOUT:
    nextPage = 1;
    currentUser = NULL;
    break;
  }
}

void Console::AdminPage() {
  // user ui and get the choice
  CleanWindow();
  Console::AdminUI(currentUser);

  int choice = Console::GetUIChoice();

  switch (choice) {
  case ADMIN_ADD_BOOK:
    // add a new book
    AddBook(avlBookTree);
    Pause();
    break;
  case ADMIN_DELETE_BOOK:
    // delete a book
    DeleteBook(avlBookTree);
    Pause();
    break;
  case ADMIN_QUERY_BOOK:
    // query a book
    QueryBook(avlBookTree);
    Pause();
    break;
  case ADMIN_DISPLAY_BOOK:
    // display all book
    DisplayBook(avlBookTree, true);
    Pause();
    break;
  case ADMIN_DISPLAY_USER:
    // display all user
    DisplayUser(avlUserTree, true);
    Pause();
    break;
  case ADMIN_DELETE_USER:
    // delete a user
    DeleteUser(avlUserTree, avlBookTree);
    Pause();
    break;
  case ADMIN_LOGOUT:
    nextPage = 1;
    currentUser = NULL;
    break;
  }
}

// Register
bool Console::Register(AVLTree &avlTree) {
  // get the user name and password
  string userName, password;
  cout << "请输入用户名:";
  cin >> userName;
  cout << "请输入密码:";
  cin >> password;

  // search for the user
  Node *node = avlTree.search(userName);
  if (node == NULL) {
    User *user = new User(userName, password, false);
    if (avlTree.add(user)) {
      cout << "注册成功!" << endl;
      writeUserToFile();
      return true;
    } else {
      return false;
    }
  } else {
    // register fail
    cout << "注册失败,用户名已存在!" << endl;
    return false;
  }
}

// Login
Node *Console::Login(AVLTree &avlTree) {
  // get the user name and password
  string userName, password;
  cout << "请输入用户名:";
  cin >> userName;
  cout << "请输入密码:";
  cin >> password;

  // search for the user
  Node *node = avlTree.search(userName);
  if (node == NULL) {
    // login fail
    LoginFailUI();
    return NULL;
  } else {
    // login successfully
    if (node->getPassword() == password) {
      cout << "登陆成功!" << endl;
      return node;
    } else {
      LoginFailUI();
      return NULL;
    }
  }
}

// query book
bool Console::QueryBook(AVLTree &avlTree) {
  // get the book ID
  string bookID;
  Node *targetedBook;
  cout << "请输入要查询的书籍ID:";
  cin >> bookID;
  targetedBook = avlTree.search(bookID);
  if (targetedBook != NULL) {
    // book exist
    cout << "书籍ID:" << targetedBook->getID() << endl;
    cout << "书籍名称:" << targetedBook->getName() << endl;
    if (targetedBook->getBelongUserID() == "") {
      cout << "书籍情况:未被借阅" << endl;
    } else {
      cout << "书籍情况:已被用户" << targetedBook->getBelongUserID() << "借阅"
           << endl;
    }
    return true;
  } else {
    // book not exist
    cout << "查询失败,该书不存在!" << endl;
    return false;
  }
  return true;
}

// display book
bool Console::DisplayBook(AVLTree &avlTree, bool isTree) {
  // this is the admin-only function
  if (isTree) {
    assert(currentUser->getAdmin() == true);
    CleanWindow();
    cout << "Book Tree:";
    avlTree.displayTree();
    cout << endl;
  } else {
    avlTree.diaplay();
  }
  return true;
}

// display user
bool Console::DisplayUser(AVLTree &avlTree, bool isTree) {
  // this is the admin-only function
  if (isTree) {
    assert(currentUser->getAdmin() == true);
    CleanWindow();
    cout << "User Tree:";
    avlTree.displayTree();
    cout << endl << endl;
  } else {
    assert(currentUser->getAdmin() == true);
    avlTree.diaplay();
  }
  return true;
}

// Add book
bool Console::AddBook(AVLTree &avlTree) {
  // this is the admin-only function
  assert(currentUser->getAdmin() == true);
  // get the book Info
  string ID, name;
  cout << "请输入书籍ID:";
  cin >> ID;
  cout << "请输入书籍名称:";
  cin >> name;
  // search for the bookID
  Node *targetedBook = avlTree.search(ID);
  if (targetedBook != NULL) {
    // the bookID already exit
    cout << "ID为:" << ID << "的书籍已存在!" << endl;
    return false;
  } else {
    // the bookID not exit
    Book *book = new Book(ID, name, "");
    if (avlTree.add(book)) {
      cout << "添加成功!" << endl;
      writeBookToFile();
      return true;
    } else {
      return false;
    }
  }
}

// Delete Book
bool Console::DeleteBook(AVLTree &avlTree) {
  // this is the admin-only function
  assert(currentUser->getAdmin() == true);
  // get the book ID
  string bookID;
  Node *targetedBook;
  cout << "请输入要删除的书籍ID:";
  cin >> bookID;
  targetedBook = avlTree.search(bookID);
  if (targetedBook != NULL) {
    // book exist
    if (targetedBook->getBelongUserID() == "") {
      // book is not borrowed
      if (avlTree.del(bookID)) {
        cout << "删除成功!" << endl;
        writeBookToFile();
        return true;
      } else {
        return false;
      }
    } else {
      // book is borrowed
      cout << "删除失败,该书已被用户" << targetedBook->getBelongUserID()
           << "借阅!" << endl;
      return false;
    }
  } else {
    // book not exist
    cout << "删除失败,该书不存在!" << endl;
    return false;
  }
}

// delete user
bool Console::DeleteUser(AVLTree& avlUser, AVLTree& avlBook){
  // show all user
  cout << endl;
  cout << "以下是所有用户:" << endl << endl;
  DisplayUser(avlUser, false);
  cout << endl;

  // this is the admin-only function
  assert(currentUser->getAdmin() == true);
  // get the user ID
  string userID;
  Node *targetedUser;
  cout << "请输入要删除的用户ID:";
  cin >> userID;
  targetedUser = avlUser.search(userID);
  if (targetedUser != NULL) {
    // user exist
    if(targetedUser->getAdmin() == true){
      cout << "删除失败,该用户是管理员!" << endl;
      return false;
    }
    if (!avlBook.isUserHaveBook(userID)) {
      // user have returned all the books
      if (avlUser.del(userID)) {
        cout << "删除成功!" << endl;
        writeUserToFile();
        return true;
      } else {
        return false;
      }
    } else {
      // user have not returned all the books
      cout << "删除失败,该用户还有书籍未归还!" << endl;
      return false;
    }
  } else {
    // user not exist
    cout << "删除失败,该用户不存在!" << endl;
    return false;
  }
}

// Borrow Book
bool Console::BorrowBook(AVLTree &avlTree) {
  // display all book
  cout << endl;
  cout << "以下是所有书籍:" << endl << endl;
  DisplayBook(avlTree, false);
  cout << endl;
  // get the book ID
  string bookID;
  Node *targetedBook;
  cout << "请输入要借阅的书籍ID:";
  cin >> bookID;
  targetedBook = avlTree.search(bookID);
  if (targetedBook != NULL) {
    // book exist
    if (targetedBook->getBelongUserID() == "") {
      // book is not borrowed
      targetedBook->setBelongUserID(currentUser->getID());
      cout << "借阅成功!" << endl;
      writeBookToFile();
      return true;
    } else {
      // book is borrowed
      cout << "借阅失败,该书已被借阅!" << endl;
      return false;
    }
  } else {
    // book not exist
    cout << "借阅失败,该书不存在!" << endl;
    return false;
  }
}

// Return book
bool Console::ReturnBook(AVLTree &avlTree) {
  // get the book ID
  string bookID;
  Node *targetedBook;
  cout << "请输入要归还的书籍ID:";
  cin >> bookID;
  targetedBook = avlTree.search(bookID);
  if (targetedBook != NULL) {
    // book exist
    if (targetedBook->getBelongUserID() == currentUser->getID()) {
      // book is not borrowed
      targetedBook->setBelongUserID("");
      cout << "归还成功!" << endl;
      writeBookToFile();
      return true;
    } else {
      // book is borrowed
      cout << "归还失败,您似乎没有借阅该书籍!" << endl;
      return false;
    }
  } else {
    // book not exist
    cout << "归还失败,该书不存在!" << endl;
    return false;
  }
}

// Delete self
bool Console::DeleteSelf(AVLTree &avlUser, AVLTree &avlBook) {
  // check if the user have returned all the books
  if (avlBook.isUserHaveBook(currentUser->getID())) {
    cout << "注销失败,您还有书籍未归还!" << endl;
    return false;
  }
  cout << "请输入密码:";
  string password;
  cin >> password;
  if (password == currentUser->getPassword()) {
    if (avlUser.del(currentUser->getID())) {
      cout << "注销成功!" << endl;
      writeUserToFile();
      return true;
    } else {
      cout << "注销失败!" << endl;
      return false;
    }
  } else {
    cout << "注销失败,密码错误!" << endl;
    return false;
  }
}

// write User and Book to file
void Console::writeBookToFile() {
  ofstream bookFile;
  bookFile.open(BOOK_FILE_PATH);
  if (bookFile.is_open()) {
    bookFile << "Book" << endl;
    avlBookTree.writeToFile(bookFile, avlBookTree.getRoot());
  }
  bookFile.close();
}

void Console::writeUserToFile() {
  ofstream userFile;
  userFile.open(USER_FILE_PATH);
  if (userFile.is_open()) {
    userFile << "User" << endl;
    avlUserTree.writeToFile(userFile, avlUserTree.getRoot());
  }
  userFile.close();
}

int Console::GetUIChoice() {
  int choice;
  cin >> choice;
  return choice;
}

void Console::LoginFailUI() { cout << "登陆失败,用户名或密码错误!" << endl; }

void Console::WelcomeUI() {
  system("clear");
  cout << "                            "
          "------------------------------------------------------"
       << endl;
  cout << "                            |           欢迎进入用户登陆查询系统    "
          "              |"
       << endl;
  cout << "                            |           1.用户登陆                  "
          "              |"
       << endl;
  cout << "                            |           2.注册用户                  "
          "              |"
       << endl;
  cout << "                            |           3.关闭系统                  "
          "              |"
       << endl;
  cout << "                            "
          "------------------------------------------------------"
       << endl;
  cout << "                                           请选择(1/2/3):" << endl;
}

void Console::UserUI(Node *node) {
  system("clear");
  cout << "                            "
          "------------------------------------------------------"
       << endl;
  cout << "                           |           欢迎" << node->getID()
       << "用户登陆查询系统" << endl;
  cout << "                           |           1.借阅书籍                  "
          "              |"
       << endl;
  cout << "                           |           2.归还书籍                  "
          "              |"
       << endl;
  cout << "                           |           3.查询书籍                  "
          "              |"
       << endl;
  cout << "                           |           4.注销账号                  "
          "              |"
       << endl;
  cout << "                           |           5.退出登陆                  "
          "              |"
       << endl;
  cout << "                           "
          "------------------------------------------------------"
       << endl;
  cout << "                                           请选择(1/2/3/4/5):"
       << endl;
}

void Console::AdminUI(Node *node) {
  system("clear");
  cout << "                            "
          "------------------------------------------------------"
       << endl;
  cout << "                            |           欢迎" << node->getID()
       << "管理员登陆查询系统" << endl;
  cout << "                            |           1.添加新书                  "
          "              |"
       << endl;
  cout << "                            |           2.删除旧书                  "
          "              |"
       << endl;
  cout << "                            |           3.查询书籍                  "
          "              |"
       << endl;
  cout << "                            |           4.展示书籍树                "
          "              |"
       << endl;
  cout << "                            |           5.展示用户树                "
          "              |"
       << endl;
  cout << "                            |           6.删除用户                  "
          "              |"
       << endl;
  cout << "                            |           7.退出登陆                  "
          "              |"
       << endl;
  cout << "                            "
          "------------------------------------------------------"
       << endl;
  cout << "                                           请选择(1/2/3/4/5/6/7):"
       << endl;
}

void Console::CleanWindow() { system("clear"); }

void Console::Pause() {
  cout << "按任意键继续..." << endl;
  system("read");
}
