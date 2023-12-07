//
// Created by 31320 on 2023/9/29.
//

#ifndef CODE_AVLTREE_H
#define CODE_AVLTREE_H
#include <string>
#include "BitMap.h"
using namespace std;

class Node;

class AVLTree{
public:
    // constructor
    AVLTree();

    // Insert
    bool Insert(const string& userName, const string& password,bool isAdminCheck,const Node* node);
    bool Insert(const string &userName, const string &password, bool isAdminCheck,const Node* thisNode,
                const string &bitMapOtherString);

    // Delete
    Node* Delete(const string& userName,Node* thisNode, Node *targetedNode);

    // change the permission
    void ChangePermission(Node* targetNode,const Node* thisNode,const std::string &bitMapOtherString);

    // find the node by userName
    Node* FindNodeByUserName(const string& userName);

    // print the tree
    void PrintTree(Node* node);

    // read the tree from file
    void ReadTreeFromFile(const string& fileName);

    // write the tree to file
    void WriteTreeToFile(const string& fileName);

    // getter and setter
    Node* GetRoot() const;
    int GetHeight(Node* node);

    // destructor
    void DestroyTree(Node *T);
    ~AVLTree() = default;

    // Get Node PTr
    Node*& GetLeftPtr(Node*& node);
    Node*& GetRightPtr(Node*& node);

private:
    Node* root; // root of the tree
    // add a node to the tree
    bool addNode(Node *&T, Node* node);
    // Insert while reading from file
    void InsertFromFile(const string& userName, const string& password, bool isAdminCheck,
                        const string &bitMapOtherString);

    // delete a node from the tree
    Node* DeleteNode(Node* node);
    Node* DeleteNode(Node* currentNode, Node* nodeToDelete) ;

    // balance the tree
    Node* LL(Node* node);
    Node* RR(Node* node);
    Node* LR(Node* node);
    Node* RL(Node* node);

    // print the tree into a file
    void printTreeToFile(Node* node, ofstream& file);
};

#endif //CODE_AVLTREE_H
