//
// Created by 31320 on 2023/9/30.
//

#ifndef CODE_CONSOLE_H
#define CODE_CONSOLE_H
#include <string>
#include "Node.h"
#include "AVLTree.h"
#include "BitMap.h"

class Console {
public:
    // Constructor
    Console(string fileName);

    // run the console
    void Run();
    void PageOne();
    void PageTwo(); // Admin page

    // UI
    static void WelcomeUI();
    static void UserUI(Node* node);
    static void AdminUI(Node* node);

    // other function
    static int GetUIChoice();
    static void CleanWindow();
    static std::string GetPermissionInput();

    // main function
    void DeleteUser(AVLTree& avlTree, Node* thisNode);
    void Register(AVLTree& avlTree, Node* currentUser);
    void ChangePassword(AVLTree& avlTree, Node* currentUser);
    void ChangePermission(AVLTree& avlTree, Node* currentUser);
    Node* Login(AVLTree& avlTree);

private:
    // User Tree
    AVLTree avlUserTree;

    // current user
    Node* currentUser;

    // default user
    Node* defaultUser;

    // file name
    string fileName;

    // next page
    int nextPage;

    // try to log in
    Node* TryLogin(AVLTree& avlTree);
    static void RegisterUser(AVLTree& avlTree, Node* currentUser);
    static void RegisterAdmin(AVLTree& avlTree, Node* currentUser);

    // UI
    static void LoginFailUI();
    static void ChangePasswordSuccessfullyUI();
    static void CannotChangePermissionUI();
    static void PermisstionBitMapExplainedUI();
};
#endif //CODE_CONSOLE_H
