//
// Created by 31320 on 2023/9/30.
//
#include <iostream>
#include <fstream>
#include <string>
#include "../h/AVLTree.h"
#include "../h/BitMap.h"
#include "../h/const.h"
#include "../h/Node.h"
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::DestroyTree(Node *T) {
    if(T == nullptr) return;
    DestroyTree(T->GetLeft());
    DestroyTree(T->GetRight());
    delete T;
}

bool AVLTree::Insert(const string &userName, const string &password,bool isAdminCheck,const Node* thisNode) {
    string newNodeBitMap;

    // the third parameter stand for the user to insert is admin or not
    if(isAdminCheck){
        // insert the admin
        if(!thisNode->GetBitMap().GetBitAt(INSERT_ADMIN_INDEX)){
            cout << "You don't have the permission to insert admin." << endl;
            system("pause");
            return false;
        }
        newNodeBitMap = ADMIN_PERMISSION_DEFAULT;
    }else{
        // insert the user
        if(!thisNode->GetBitMap().GetBitAt(INSERT_USER_INDEX)){
            cout << "You don't have the permission to insert user." << endl;
            system("pause");
            return false;
        }
        newNodeBitMap = USER_PERMISSION_DEFAULT;
    }

    Node* node = new Node(userName, password, 1, isAdminCheck, newNodeBitMap);

    return addNode(this->root, node);
}

bool AVLTree::Insert(const string &userName, const string &password, bool isAdminCheck,const Node* thisNode,
                     const string &bitMapOtherString) {
    // this function is used to explicitly insert a admin with its permission
    if(!isAdminCheck){
        cout << "the permission of users is set by default you cant explicitly set it." << endl;
        system("pause");
        return false;
    }

    // check whether the user has the permission to insert admin
    if(!thisNode->GetBitMap().GetBitAt(INSERT_ADMIN_INDEX)){
        cout << "You don't have the permission to insert admin." << endl;
        system("pause");
        return false;
    }

    // check whether the bitMapOther have more permission than the user
    BitMap bitMapOther(PERMISSION_NUM, bitMapOtherString);
    if(!thisNode->GetBitMap().CanInsertOrChange(bitMapOther)){
        cout << "You don't have the permission to set the permission of the admin." << endl;
        system("pause");
        return false;
    }

    // check if the new admin is root
    if(bitMapOther.IsRoot()){
        cout << "You can't add another root." << endl;
        system("pause");
        return false;
    }

    Node* node = new Node(userName, password, 1, isAdminCheck, bitMapOtherString);

    return addNode(this->root, node);
}

bool AVLTree::addNode(Node *&T, Node *node) {

    // if the tree is empty
    if(this->root == nullptr){
        this->root = node;
        return false;
    }

    // if the tree is not empty
    if(T->GetUserName() > node->GetUserName()){
        if(T->GetLeft() == nullptr){
            T->SetLeft(node);
        }else{
            Node *&temp = GetLeftPtr(T);
            if (!addNode(temp, node)){
                return false;
            }
        }
    } else if(T->GetUserName() < node->GetUserName()) {
        if (T->GetRight() == nullptr) {
            T->SetRight(node);
        } else {
            Node *&temp = GetRightPtr(T);
            if (!addNode(temp, node)) {
                return false;
            }
        }
    }else{
        cout << "The user name has been used." << endl;
        system("pause");
        return false;
    }

    // update the height of the node
    T->SetHeight(this->GetHeight(T));

    // check whether the tree is balanced
    if (abs(GetHeight(T->GetLeft()) - GetHeight(T->GetRight())) > 1) {
        if(GetHeight(T->GetLeft()) - GetHeight(T->GetRight()) > 0){
            if(GetHeight(T->GetLeft()->GetLeft()) - GetHeight(T->GetLeft()->GetRight()) > 0){
                T = this->LL(T);
            }else{
                T = this->LR(T);
            }
        }else{
            if(GetHeight(T->GetRight()->GetLeft()) - GetHeight(T->GetRight()->GetRight()) > 0){
                T = this->RL(T);
            }else{
                T = this->RR(T);
            }
        }
    }

    return true;
}

Node* AVLTree::LL(Node *node) {
    Node* temp = node->GetLeft();
    node->SetLeft(temp->GetRight());
    temp->SetRight(node);
    return temp;
}

Node* AVLTree::RR(Node *node) {
    Node* temp = node->GetRight();
    node->SetRight(temp->GetLeft());
    temp->SetLeft(node);
    return temp;
}

Node* AVLTree::LR(Node *node) {
    Node* temp = node->GetLeft()->GetRight();
    Node* tempLeft = temp->GetLeft();
    Node* tempRight = temp->GetRight();
    temp->SetLeft(node->GetLeft());
    temp->SetRight(node);
    node->GetLeft()->SetRight(tempLeft);
    node->SetLeft(tempRight);
    return temp;
}

Node* AVLTree::RL(Node *node) {
    Node* temp = node->GetRight()->GetLeft();
    Node* tempLeft = temp->GetLeft();
    Node* tempRight = temp->GetRight();
    temp->SetRight(node->GetRight());
    temp->SetLeft(node);
    node->GetRight()->SetLeft(tempRight);
    node->SetRight(tempLeft);
    return temp;
}

void AVLTree::PrintTree(Node *node) {
    if(node == nullptr) return;
    PrintTree(node->GetLeft());
    cout << node->GetUserName() << " " << node->GetPassword() << endl;
    PrintTree(node->GetRight());
}

void AVLTree::ReadTreeFromFile(const string &fileName) {
    ifstream fin(fileName);
    if(!fin){
        cout << "Can't open the file." << endl;
        return;
    }
    string userName, password, bitMapString;
    int isAdminInt;
    while(fin >> userName >> password >> isAdminInt >> bitMapString){
        this->InsertFromFile(userName, password, isAdminInt == 1, bitMapString);
    }
    fin.close();
}

Node *AVLTree::GetRoot() const {
    return this->root;
}

int AVLTree::GetHeight(Node *node) {
    if(node == nullptr) return 0;
        return max(GetHeight(node->GetLeft()), GetHeight(node->GetRight())) + 1;
}

void AVLTree::WriteTreeToFile(const string &fileName) {
    ofstream fout(fileName);
    if(!fout){
        cout << "Can't open the file." << endl;
        return;
    }
    printTreeToFile(this->root, fout);
    fout.close();
}

void AVLTree::printTreeToFile(Node *node, ofstream &file) {
    if(node == nullptr) return;
    printTreeToFile(node->GetLeft(), file);
    file << node->GetUserName() << " " << node->GetPassword() << " " << (node->GetIsAdmin() ? 1 : 0) << ' ' << node->GetBitMap() << endl;
    printTreeToFile(node->GetRight(), file);
}

Node *AVLTree::FindNodeByUserName(const string &userName) {
    Node* node = this->root;
    while(node != nullptr){
        if(node->GetUserName() == userName){
            return node;
        }else if(node->GetUserName() > userName){
            node = node->GetLeft();
        }else{
            node = node->GetRight();
        }
    }
    Node* temp= nullptr;
    return temp;
}

void AVLTree::InsertFromFile(const string &userName, const string &password, bool isAdminCheck,
                             const string &bitMapOtherString) {
    // Insert while reading from file
    Node *node = new Node(userName, password, 1, isAdminCheck, bitMapOtherString);
    addNode(this->root, node);
}

void AVLTree::ChangePermission(Node *targetNode, const Node *thisNode, const string &bitMapOtherString) {
    if(targetNode->GetIsAdmin()){
        // current user want to change a admin user's permission
        // check if the current user can change the permission of targeted user
        if(!thisNode->GetBitMap().GetBitAt(CHANGE_ADMIN_INDEX)){
            cout << "You don't have the permission to change the permission of the admin." << endl;
            system("pause");
            return;
        }
        // check if the targeted user's permission is more than the current user
        BitMap bitMapOther(PERMISSION_NUM, bitMapOtherString);
        if(bitMapOther.IsEmpty()){
            return;
        }
        if(!thisNode->GetBitMap().CanInsertOrChange(bitMapOther)){
            cout << "The permission of the admin is more than yours." << endl;
            cout << "Your permission is:" << endl;
            thisNode->PrintPermission();
            cout << "The permission of the admin is:" << endl;
            targetNode->PrintPermission();
            system("pause");
            return;
        }
        // check if the targeted user is root
        if(bitMapOther.IsRoot()){
            cout << "You can't change the permission of another root." << endl;
            system("pause");
            return;
        }
        // change the permission
        targetNode->SetBitMap(bitMapOtherString);
        cout << "The permission of the admin has been changed." << endl;
        system("pause");
    }else{
        // current user want to change a normal user's permission,which is fixed
        cout << "You can't change the permission of a normal user!" << endl;
        system("pause");
        return;
    }
}

Node* AVLTree::Delete(const string &userName, Node *thisNode, Node* targetedNode) {
    // find the node to delete
    if(targetedNode == nullptr){
        cout << "The user doesn't exist." << endl;
        system("pause");
        return targetedNode;
    }
    if (targetedNode->GetUserName() == userName) {
        // the user to delete is found
        if (targetedNode == thisNode) {
            // the user want to delete himself
            targetedNode = DeleteNode(targetedNode);
            return targetedNode;
        }
        if (targetedNode->GetIsAdmin()) {
            // the user want to delete a admin
            // check if the user has the permission to delete a admin
            if (!thisNode->GetBitMap().GetBitAt(DELETE_ADMIN_INDEX)) {
                cout << "You don't have the permission to delete a admin." << endl;
                system("pause");
                return targetedNode;
            }
            // check if the target user's permission is more than the current user
            if (!thisNode->GetBitMap().CanInsertOrChange(targetedNode->GetBitMap())) {
                cout << "The permission of the admin is more than yours." << endl;
                cout << "Your permission is:" << endl;
                thisNode->PrintPermission();
                cout << "The permission of the admin is:" << endl;
                targetedNode->PrintPermission();
                system("pause");
                return targetedNode;
            }
            // delete the admin
            targetedNode = DeleteNode(targetedNode);
            cout << "The admin has been deleted." << endl;
            system("pause");
        } else {
            // the user want to delete a normal user
            // check if the user has the permission to delete a normal user
            if (!thisNode->GetBitMap().GetBitAt(DELETE_USER_INDEX)) {
                cout << "You don't have the permission to delete a normal user." << endl;
                system("pause");
                return targetedNode;
            }
            // delete the normal user
            targetedNode = DeleteNode(targetedNode);
        }
    }else if(targetedNode->GetUserName() > userName){
        // the user to delete is in the left subtree
        targetedNode->SetLeft(Delete(userName, thisNode, targetedNode->GetLeft()));
    }else{
        // the user to delete is in the right subtree
        targetedNode->SetRight(Delete(userName, thisNode, targetedNode->GetRight()));
    }
}

Node* AVLTree::DeleteNode(Node *node) {
    if(node->GetRight() && node->GetLeft()){
        // the node has two children
        Node* temp = node->GetRight();
        while(temp->GetLeft()){
            temp = temp->GetLeft();
        }
        // temp is the next node of the node to delete
        *node = *temp;
        node->SetRight(DeleteNode(node->GetRight(), temp));
    }else if(node->GetRight()){
        // replace the node with its right child
        Node* temp = node->GetRight();
        *node = *temp;
        delete temp;
        node->SetRight(nullptr);
    }else if(node->GetLeft()){
        // replace the node with its left child
        Node* temp = node->GetLeft();
        *node = *temp;
        delete temp;
        node->SetLeft(nullptr);
    }else{
        // the node is a leaf
        delete node;
        node = nullptr;
    }
    return node;
}

Node *AVLTree::DeleteNode(Node *currentNode, Node *nodeToDelete) {
    // delete a node from the currentNode and return processed currentNode
    // this function must be called by DeleteNode(Node* nodeToDelete)
    if (currentNode == nullptr)
        return nullptr;

    if (currentNode == nodeToDelete) {
        delete currentNode;
        return nullptr;
    }

    if (nodeToDelete->GetUserName() < currentNode->GetUserName()) {
        currentNode->SetLeft(DeleteNode(currentNode->GetLeft(), nodeToDelete));
    } else {
        currentNode->SetRight(DeleteNode(currentNode->GetRight(), nodeToDelete));
    }

    return currentNode;
}

Node *&AVLTree::GetLeftPtr(Node*&node) {
    return node->left;
}

Node *&AVLTree::GetRightPtr(Node*&node) {
    return node->right;
}