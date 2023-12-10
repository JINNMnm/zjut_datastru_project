//
// Created by 31320 on 2023/9/30.
//
#include "../h/AVLTree.h"
#include "../h/Book.h"
#include "../h/Node.h"
#include "../h/User.h"
#include "../h/const.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Constructor
AVLTree::AVLTree() { this->root = nullptr; }

// Destructor
AVLTree::~AVLTree() { destroy(this->root); }

void AVLTree::destroy(Node *root) {
  if (root == nullptr) {
    return;
  }
  destroy(root->left);
  destroy(root->right);
  delete root;
}

// getter and setter
Node *AVLTree::getRoot() { return this->root; }
void AVLTree::setRoot(Node *root) { this->root = root; }

// insert a node
// prerequisite: LL, RR, LR, RL
// LL
Node *AVLTree::LL(Node *root) {
  Node *temp = root->left;
  root->left = temp->right;
  temp->right = root;
  root->updateHeight();
  temp->updateHeight();

  return temp;
}

// RR
Node *AVLTree::RR(Node *root) {
  Node *temp = root->right;
  root->right = temp->left;
  temp->left = root;
  root->updateHeight();
  temp->updateHeight();
  return temp;
}

// LR
Node *AVLTree::LR(Node *root) {
  root->left = RR(root->left);
  return LL(root);
}

// RL
Node *AVLTree::RL(Node *root) {
  root->right = LL(root->right);
  return RR(root);
}

// after all the prerequisite, we can implement the add function
bool AVLTree::add(Node *newNode, Node *&root) {
  if (root == nullptr) {
    // not sure if node point to a Book or a User
    // so we need to dynamic_cast
    if (dynamic_cast<User *>(newNode)) {
      root = new User(*(dynamic_cast<User *>(newNode)));
    } else if (dynamic_cast<Book *>(newNode)) {
      root = new Book(*(dynamic_cast<Book *>(newNode)));
    }
    return true;
  }
  if (*newNode < *root) {
    if (!add(newNode, root->left)) {
      return false;
    }
    if (needLL(root)) {
      root = LL(root);
    } else if (needLR(root)) {
      root = LR(root);
    }

  } else if (*newNode > *root) {
    if (!add(newNode, root->right)) {
      return false;
    }
    if (needRR(root)) {
      root = RR(root);
    } else if (needRL(root)) {
      root = RL(root);
    }
  } else {
    cout << "ID 已经存在!" << endl;
    return false;
  }
  root->updateHeight();
  return true;
}

bool AVLTree::add(Node *newNode) { return add(newNode, this->root); }

// delete a node
bool AVLTree::del(string targetID, Node *&root) {
  if (root == nullptr) {
    return false;
  }
  if (targetID < root->getID()) {
    if (!del(targetID, root->left)) {
      return false;
    }
    if (needRL(root)) {
      root = RL(root);
    } else if (needRR(root)) {
      root = RR(root);
    }
  } else if (targetID > root->getID()) {
    if (!del(targetID, root->right)) {
      return false;
    }
    if (needLL(root)) {
      root = LL(root);
    } else if (needLR(root)) {
      root = LR(root);
    }
  } else {
    if (root->left == nullptr && root->right == nullptr) {
      delete root;
      root = nullptr;
    } else if (root->left != nullptr && root->right == nullptr) {
      *root = *root->left;
      delete root->left;
      root->left = NULL;
      root->updateHeight();
    } else if (root->left == nullptr && root->right != nullptr) {
      *root = *root->right;
      delete root->right;
      root->right = NULL;
      root->updateHeight();
    } else {
      // the target node has two children
      // find the smallest node in the right subtree
      Node *temp = root->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      *root = *temp;
      if(!del(temp->getID(), root->right)){
          return false;
      }
      // the left tree is not NULL for sure
      if (needLR(root)) {
        root = LR(root);
      } else if (needLL(root)) {
        root = LL(root);
      }
    }
  }
  if (root != nullptr) {
    root->updateHeight();
  }
  return true;
}

bool AVLTree::del(string targetID) { return del(targetID, this->root); }

// write to file
void AVLTree::writeToFile(ofstream &os, Node *root) {
  if (root == nullptr) {
    return;
  }
  writeToFile(os, root->left);
  root->print(os);
  writeToFile(os, root->right);
}

// load from
void AVLTree::loadFromFile(ifstream &is) {
  string type;
  // the first line of every txt is the type of the node(User or book)
  is >> type;
  if (type == "User") {
    string ID, password;
    int isAdmin;
    bool isAdminBool;
    while (is >> ID >> password >> isAdmin) {
      if (isAdmin == 1) {
        isAdminBool = true;
      } else {
        isAdminBool = false;
      }
      User *user = new User(ID, password, isAdminBool);
      add(user, root);
    }
  } else if (type == "Book") {
    string ID, name, belongUserID;
    while (is >> ID >> name >> belongUserID) {
      if (belongUserID == "0") {
        belongUserID = "";
      }
      Book *book = new Book(ID, name, belongUserID);
      add(book, root);
    }
  }
}

// search for a Node
Node *AVLTree::search(string targetID, Node *root) {
  if (root == NULL) {
    return NULL;
  }
  if (root->getID() == targetID) {
    return root;
  } else if (root->getID() > targetID) {
    return search(targetID, root->left);
  } else {
    return search(targetID, root->right);
  }
}

Node *AVLTree::search(string targetID) { return search(targetID, this->root); }

// displayTree
bool AVLTree::displayTree(Node *T, int depth, int right, int tap) {
  if (T == NULL)
    return false;

  // 获取一次树的初始高度，用于计算相对偏移数量
  static int treeDepth = this->root->getHeight();
  // 记录当前光标位置，用于在递归中记录当前递归时树的位置
  int x, y;
  // 拆分树，将树的左右子树拆分开来
  // BiTree L, R;
  // BreakBiTree(T, L, R);
  Node *L = T->left, *R = T->right;

  // 计算父树的偏移量
  int tap1 = tap * pow(2, treeDepth - depth)-1;
  // 计算子树的偏移量
  int tap2 = right * (pow(2, treeDepth - depth));
  // 计算半偏移量
  int tap3 = pow(2, treeDepth - depth - 1);

  // 获取根的坐标
  // x 计算方法为：父偏移量 + 子偏移量 + 半偏移量 - 1
  // y 计算方法为：目前打印的层数 * 2
  x = tap1 + tap2 + tap3;
  y = depth * 2;

  // 打印根的位置
  goto(x * 2, y);
  // printf("%d", T->data);
  cout << T->getID();

  // 在打印子树时，当前层数+1
  depth++;
  // 计算子树的父偏移量
  tap = tap * 2 + (right == 1 ? 2 : 0);
  if (L == NULL && R == NULL)
    return true;
  else if (R == NULL) {
    // 打印左子树的位置
    goto(x * 2 - tap3, y + 1);
    printf("┏");
    for (int i = 0; i < tap3 - 1; i++)
      printf("━");
    printf("┛");
    displayTree(L, depth, 0, tap);
  } else if (L == NULL) {
    // 打印右子树的位置
    goto(x * 2, y + 1);
    printf("┗");
    for (int i = 0; i < tap3 - 1; i++)
      printf("━");
    printf("┓");
    displayTree(R, depth, 1, tap);
  } else {
    // 打印左右子树的位置
    goto(x * 2 - tap3, y + 1);
    printf("┏");
    for (int i = 0; i < tap3 - 1; i++)
      printf("━");
    printf("┻");
    for (int i = 0; i < tap3 - 1; i++)
      printf("━");
    printf("┓");
    displayTree(L, depth, 0, tap);
    displayTree(R, depth, 1, tap);
  }
  cout << endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return true;
}

bool AVLTree::displayTree() { return displayTree(this->root, 0, 0, 0); }

// display
bool AVLTree::display(Node* root){
  if(root == nullptr){
    return false;
  }
  display(root->left);
  root->print();
  display(root->right);
  return true;
}

bool AVLTree::diaplay() { return display(this->root); }

// check if user have books
bool AVLTree::isUserHaveBook(string userID, Node *root) {
  if(root == NULL){
    return false;
  }
  if(root->getBelongUserID() == userID){
    return true;
  }
  if(isUserHaveBook(userID, root->left) || isUserHaveBook(userID, root->right)){
    return true;
  }
  return false;
}

bool AVLTree::isUserHaveBook(string userID) {
  return isUserHaveBook(userID, this->root);
}

// tell if tree need LL? RR? LR? RL?
bool AVLTree::needLL(Node *root) {
  if (root == nullptr) {
    return false;
  }
  if (root->left != NULL && root->right != NULL) {
    if (root->left->getHeight() - root->right->getHeight() > 1) {
      if (root->left->left != NULL && root->left->right != NULL) {
        if (root->left->left->getHeight() > root->left->right->getHeight()) {
          return true;
        }
      } else if (root->left->left != NULL && root->left->right == NULL) {
        return true;
      } else if (root->left->left == NULL && root->left->right != NULL) {
        return false;
      }
    }
  } else if (root->left != NULL && root->right == NULL) {
    if (root->left->getHeight() > 1) {
      if (root->left->left != NULL && root->left->right != NULL) {
        if (root->left->left->getHeight() > root->left->right->getHeight()) {
          return true;
        }else if(root->left->left->getHeight() == root->left->right->getHeight()){
            // they are equal so both LL or LR works
            return true;
        }
      } else if (root->left->left != NULL && root->left->right == NULL) {
        return true;
      } else if (root->left->left == NULL && root->left->right != NULL) {
        return false;
      }
    }
  } else if (root->left == NULL && root->right != NULL) {
    return false;
  }
  return false;
}

bool AVLTree::needRR(Node *root) {
  if (root == nullptr) {
    return false;
  }
  if (root->left != NULL && root->right != NULL) {
    if (root->right->getHeight() - root->left->getHeight() > 1) {
      if (root->right->left != NULL && root->right->right != NULL) {
        if (root->right->left->getHeight() < root->right->right->getHeight()) {
          return true;
        }else if (root->right->left->getHeight() == root->right->right->getHeight()){
            // ther are equal so both RR or RL works here
            return true;
        }
      } else if (root->right->left != NULL && root->right->right == NULL) {
        return false;
      } else if (root->right->left == NULL && root->right->right != NULL) {
        return true;
      }
    }
  } else if (root->left != NULL && root->right == NULL) {
    return false;
  } else if (root->left == NULL && root->right != NULL) {
    if (root->right->getHeight() > 1) {
      if (root->right->left != NULL && root->right->right != NULL) {
        if (root->right->left->getHeight() < root->right->right->getHeight()) {
          return true;
        }
      } else if (root->right->left != NULL && root->right->right == NULL) {
        return false;
      } else if (root->right->left == NULL && root->right->right != NULL) {
        return true;
      }
    }
  }
  return false;
}

bool AVLTree::needLR(Node *root) {
  if (root == nullptr) {
    return false;
  }
  if (root->left != NULL && root->right != NULL) {
    if (root->left->getHeight() - root->right->getHeight() > 1) {
      if (root->left->left != NULL && root->left->right != NULL) {
        if (root->left->left->getHeight() < root->left->right->getHeight()) {
          return true;
        }
      } else if (root->left->left != NULL && root->left->right == NULL) {
        return false;
      } else if (root->left->left == NULL && root->left->right != NULL) {
        return true;
      }
    }
  } else if (root->left != NULL && root->right == NULL) {
    if (root->left->getHeight() > 1) {
      if (root->left->left != NULL && root->left->right != NULL) {
        if (root->left->left->getHeight() < root->left->right->getHeight()) {
          return true;
        }
      } else if (root->left->left != NULL && root->left->right == NULL) {
        return false;
      } else if (root->left->left == NULL && root->left->right != NULL) {
        return true;
      }
    }
  } else if (root->left == NULL && root->right != NULL) {
    return false;
  }
  return false;
}

bool AVLTree::needRL(Node *root) {
  if (root == nullptr) {
    return false;
  }
  if (root->left != NULL && root->right != NULL) {
    if (root->right->getHeight() - root->left->getHeight() > 1) {
      if (root->right->left != NULL && root->right->right != NULL) {
        if (root->right->left->getHeight() > root->right->right->getHeight()) {
          return true;
        }
      } else if (root->right->left != NULL && root->right->right == NULL) {
        return true;
      } else if (root->right->left == NULL && root->right->right != NULL) {
        return false;
      }
    }
  } else if (root->left != NULL && root->right == NULL) {
    return false;
  } else if (root->left == NULL && root->right != NULL) {
    if (root->right->getHeight() > 1) {
      if (root->right->left != NULL && root->right->right != NULL) {
        if (root->right->left->getHeight() > root->right->right->getHeight()) {
          return true;
        }
      } else if (root->right->left != NULL && root->right->right == NULL) {
        return true;
      } else if (root->right->left == NULL && root->right->right != NULL) {
        return false;
      }
    }
  }
  return false;
}
