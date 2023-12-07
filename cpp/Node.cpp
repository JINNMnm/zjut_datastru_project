//
// Created by 31320 on 2023/9/29.
//

# include "../h/Node.h"
#include "../h/BitMap.h"
#include <iostream>
using namespace std;
const int PERMISSION_NUM = 6;

Node::Node(std::string userName, std::string password,int height,bool isAdmin,string bitMapString):
        userName(std::move(userName)),
        password(std::move(password)),
        height(height),
        isAdmin(isAdmin),
        bitMap(BitMap(PERMISSION_NUM,bitMapString)),
        left(nullptr),
        right(nullptr){}

const string &Node::GetUserName() const {
    return this->userName;
}

void Node::SetUserName(const string &userName) {
    this->userName = userName; // use the move semantics
}

const string &Node::GetPassword() const {
    return this->password;
}

void Node::SetPassword(const string &password) {
    this->password = password; // use the move semantics
}

Node *Node::GetLeft() const  {
    return this->left;
}

void Node::SetLeft(Node *left) {
    this->left = left;
}

Node *Node::GetRight() const  {
    return this->right;
}

void Node::SetRight(Node *right) {
    this->right = right;
}

int Node::GetHeight() const {
    return this->height;
}

void Node::SetHeight(int height) {
    this->height = height;
}

bool Node::GetIsAdmin() const {
    return this->isAdmin;
}

void Node::SetIsAdmin(bool isAdmin) {
    this->isAdmin = isAdmin;
}

const BitMap & Node::GetBitMap() const {
    return this->bitMap;
}

void Node::SetBitMap(const string &bitMapString) {
    // bitMapString is a string of 0 and 1
    this->bitMap.SetBitMap(bitMapString);
}

void Node::PrintPermission() const {
    BitMap thisBitMap = this->GetBitMap();
    cout << "您当前的权限为：" << endl;
    this->GetBitMap().PrintBitMap();
    if(thisBitMap.IsRoot()){
        cout << "您当前为超级管理员，拥有所有权限，请注意！！！" << endl;
    }
}

Node &Node::operator=(const Node &node) {
    this->userName = node.userName;
    this->password = node.password;
    this->isAdmin = node.isAdmin;
    this->height = node.height;
    this->bitMap = node.bitMap;
    this->left = node.left;
    this->right = node.right;
    return *this;
}

