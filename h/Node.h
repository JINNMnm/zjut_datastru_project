#ifndef NODE_H
#define NODE_H
#include <string>
# include "BitMap.h"
# include "AVLTree.h"
using namespace std;


// Node class
class Node {
public:
    // constructor
    Node(string userName, string password, int height, bool isAdmin, string bitMapString);
    // getter and setter
    const string &GetUserName() const;
    void SetUserName(const string &userName);

    const string &GetPassword() const;
    void SetPassword(const string &password);

    Node *GetLeft() const;
    void SetLeft(Node *left);

    Node *GetRight() const;
    void SetRight(Node *right);

    int GetHeight() const;
    void SetHeight(int height);

    bool GetIsAdmin() const;
    void SetIsAdmin(bool isAdmin);

    const BitMap & GetBitMap() const;
    void SetBitMap(const string& bitMapString);

    // print the permission of the user
    void PrintPermission() const;

    // overload the operator =
    Node& operator=(const Node& node);

    // destructor
    ~Node() = default;
private:
    string userName; // username
    string password; // password
    Node* left;
    Node* right; // left and right child
    bool isAdmin; // whether the user tree is admin tree
    int height; // height of the node in the tree
    BitMap bitMap; // bit map

    // getptr
    friend Node*& AVLTree::GetLeftPtr(Node*& node);
    friend Node*& AVLTree::GetRightPtr(Node*& node);
};

#endif // NODE_H