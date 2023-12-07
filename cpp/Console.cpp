//
// Created by 31320 on 2023/9/30.
//

#include "../h/Console.h"
#include "../h/const.h"
#include <iostream>
#include <fstream>
using namespace std;


void Console::WelcomeUI() {
    system("cls");
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                            |           ��ӭ�����û���½��ѯϵͳ                      |" << endl;
    cout << "                            |           1.�û���½                                 |" << endl;
    cout << "                            |           2.ע���û�                                 |" << endl;
    cout << "                            |           3.�ر�ϵͳ                                 |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                                           ��ѡ��(1/2/3):" << endl;
}

int Console::GetUIChoice() {
    int choice;
    cin >> choice;
    return choice;
}

Node *Console::TryLogin(AVLTree &avlTree) {
    // get the userName and check the password
    // return the node if success
    string userName;
    string password;
    cout << "�������û���:" << endl;
    cin >> userName;
    cout << "����������:" << endl;
    cin >> password;
    Node* node = avlTree.FindNodeByUserName(userName);

    if(!node){
        return nullptr;
    }

    if(node->GetPassword() != password){
        return nullptr;
    }

    return node;
}

void Console::LoginFailUI() {
    cout << "��½ʧ��,�û������������!" << endl;
}

Node *Console::Login(AVLTree &avlTree) {
    int tryTime = 0;
    Node* node = this->TryLogin(avlTree);
    while(!node){
        tryTime++;
        if(tryTime == 3){
            cout << "��½ʧ�ܴ�������,���Ժ�����!" << endl;
            exit(1);
        }
        this->LoginFailUI();
        system("pause");
        node = this->TryLogin(avlTree);
    }
    return node;
}

void Console::UserUI(Node *node) {
    system("cls");
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                            |           ��ӭ" << node->GetUserName() << "�û���½��ѯϵͳ" << endl;
    cout << "                            |           1.�޸�����                                 |" << endl;
    cout << "                            |           2.ע��                                    |" << endl;
    cout << "                            |           3.�˳�                                    |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    node->PrintPermission();
    cout << "                                           ��ѡ��(1/2):" << endl;
}

void Console::AdminUI(Node *node) {
    system("cls");
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                            |           ��ӭ" << node->GetUserName() << "����Ա��½��ѯϵͳ" << endl;
    cout << "                            |           1.�޸�����                                 |" << endl;
    cout << "                            |           2.�޸�Ȩ��                                 |" << endl;
    cout << "                            |           3.ע���û�                                 |" << endl;
    cout << "                            |           4.�����û�                                 |" << endl;
    cout << "                            |           5.�˳�                                     |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    node->PrintPermission();
    cout << "                                           ��ѡ��(1/2/3/4/5):" << endl;
}

void Console::DeleteUser(AVLTree &avlTree, Node *thisNode) {
    char choice;
    if(thisNode->GetIsAdmin()){
        cout << "�Ƿ�Ҫע�����˻�(y/n)" << endl;
        cin >> choice;
        if(choice == 'y'){
           if(thisNode->GetBitMap().IsRoot()){
                cout << "���Ǹ��û����޷�ע��" << endl;
               system("pause");
                return ;
           }
           avlTree.Delete(thisNode->GetUserName(), thisNode, avlTree.GetRoot());
            cout << "ע���ɹ�" << endl;
            avlTree.WriteTreeToFile(fileName);
            system("pause");
           nextPage = 1;
        }else if(choice == 'n'){
            cout << "������Ҫע�����û���" << endl;
            string userName;
            cin >> userName;
            avlTree.Delete(userName, thisNode, avlTree.GetRoot());
            avlTree.WriteTreeToFile(fileName);
        }else{
            cout << "�������" << endl;
            system("pause");
        }
    }else{
        cout << "�����ǹ���Ա��ֻ��ע�����˻����Ƿ�ע����(y/n)" << endl;
        cin >> choice;
        if(choice == 'y'){
            avlTree.Delete(thisNode->GetUserName(), thisNode, avlTree.GetRoot());
            cout << "ע���ɹ�" << endl;
            avlTree.WriteTreeToFile(fileName);
            system("pause");
            nextPage = 1;
        }else if(choice == 'n'){
            cout << "�����ǹ���Ա���޷�ע�������û�" << endl;
            system("pause");
        }
    }
}

void Console::Register(AVLTree &avlTree, Node *currentUser) {
    if(currentUser->GetIsAdmin()){
        bool isAdmin;
        cout << "�Ƿ�ע�����Ա(y/n)" << endl;
        string choice;
        cin >> choice;
        if(choice == "y"){
            isAdmin = true;
        }else if(choice == "n"){
            isAdmin = false;
        }else{
            cout << "�������" << endl;
            system("pause");
            return;
        }
        if(isAdmin){
            RegisterAdmin(avlTree, currentUser);
        }else{
            RegisterUser(avlTree, currentUser);
        }
    }else{
        RegisterUser(avlTree, currentUser);
    }
    avlTree.WriteTreeToFile(fileName);
}

void Console::RegisterUser(AVLTree &avlTree, Node *currentUser) {
    // get the userName and check the password
    string userName, password, passwordCheck;
    cout << "�������û���:" << endl;
    cin >> userName;
    cout << "����������:" << endl;
    cin >> password;
    // check if the userName exist
    Node* node = avlTree.FindNodeByUserName(userName);
    if(node){
        cout << "�û����Ѵ���!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "���ٴ���������:" << endl;
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "������������벻һ��!" << endl;
        system("pause");
        return;
    }
    // register the user
    avlTree.Insert(userName, password, false, currentUser);
}

void Console::RegisterAdmin(AVLTree &avlTree, Node *currentUser) {
    // get the userName and check the password
    string userName, password, passwordCheck;
    cout << "�������û���:" << endl;
    cin >> userName;
    cout << "����������:" << endl;
    cin >> password;
    // check if the userName exist
    Node* node = avlTree.FindNodeByUserName(userName);
    if(node){
        cout << "�û����Ѵ���!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "���ٴ���������:";
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "������������벻һ��!";
        system("pause");
        return;
    }
    // ask if you need to set the permission
    cout << "�Ƿ���Ҫ����Ȩ�ޣ���������ʹ�ù���ԱĬ��Ȩ�ޣ�(y/n)" ;
    string choice;
    cin >> choice;
    string bitMapString;
    if(choice == "y"){
        cout << "������6����Ȩ���ַ���:" << endl;
        PermisstionBitMapExplainedUI();
        cin >> bitMapString;
    }else{
        bitMapString = ADMIN_PERMISSION_DEFAULT;
    }
    // register the user
    if(avlTree.Insert(userName, password, true, currentUser, bitMapString)){
        cout << "ע��ɹ�!" << endl;
        system("pause");
    }
}

void Console::CleanWindow() {
    system("cls");
}

void Console::Run() {
    switch (nextPage) {
        case 1:
            PageOne();
            break;
        case 2:
            PageTwo();
            break;
    }
}

Console::Console(string fileName) {
    // read the file and init the tree
    avlUserTree.ReadTreeFromFile(fileName);

    this->fileName = fileName;
    nextPage = 1;

    // init the default user
    defaultUser = new Node("1","1",1,false,"100000");
    currentUser = nullptr;
}

void Console::PageOne() {
    // welcome ui and get the choice
    CleanWindow();
    Console::WelcomeUI();

    int choice = Console::GetUIChoice();

    switch (choice) {
        case UI_LOGIN:
            // login
            currentUser = Login(avlUserTree);
            if(currentUser->GetIsAdmin()){
                // admin page
                PageTwo();
            }else{
                // user page
                Console::UserUI(currentUser);
            }
            break;
        case UI_REGISTER:
            // register
            Console::Register(avlUserTree, defaultUser);
            break;
        case UI_CLOSE:
            // close
            break;
    }
}

void Console::PageTwo() {
    CleanWindow();
    nextPage = 2;
    int choice;
    Console::AdminUI(currentUser);
    choice = Console::GetUIChoice();
    switch (choice) {
        case ADMIN_UI_CHANGE_PASSWORD:
            // change password
            ChangePassword(avlUserTree, currentUser);
            break;
        case ADMIN_UI_CHANGE_PERMISSION:
            // change permission
            ChangePermission(avlUserTree, currentUser);
            break;
        case ADMIN_UI_DESTROY_USER:
            // delete user
            DeleteUser(avlUserTree, currentUser);
            break;
        case ADMIN_UI_INSERT_USER:
            // insert user
            Register(avlUserTree, currentUser);
            break;
        case ADMIN_UI_RETURN:
            // return
            nextPage = 1;
            break;
    }
}

void Console::ChangePassword(AVLTree &avlTree, Node *currentUser) {
    // get the password and check the password
    string password, passwordCheck;
    cout << "������ԭ����:" << endl;
    cin >> password;
    if(password != currentUser->GetPassword()){
        cout << "�������!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "������������:" << endl;
    cin >> password;
    cout << "���ٴ�����������:" << endl;
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "������������벻һ��!" << endl;
        system("pause");
        return;
    }
    // change the password
    currentUser->SetPassword(password);
    // write the tree to file
    avlTree.WriteTreeToFile(fileName);
    // change password successfully
    ChangePasswordSuccessfullyUI();
    // pause
    system("pause");
}

void Console::ChangePasswordSuccessfullyUI() {
    cout << "�����޸ĳɹ�!" << endl;
}

void Console::ChangePermission(AVLTree &avlTree, Node *currentUser) {
    // first check if the user is admin
    if(!currentUser->GetIsAdmin()){
        cout << "�����ǹ���Ա���޷��޸�Ȩ��!" << endl;
        system("pause");
        return;
    }
    // get the userName
    string userName;
    cout << "������Ҫ�޸�Ȩ�޵��û���:" << endl;
    cin >> userName;
    // check if the user exist
    Node* targetedUser = avlTree.FindNodeByUserName(userName);
    if(!targetedUser){
        cout << "���û�������!" << endl;
        system("pause");
        return;
    }
    std::string otherPermissionString = GetPermissionInput();
    if(otherPermissionString.empty()){
        return;
    }
    avlTree.ChangePermission(targetedUser, currentUser, otherPermissionString);
    avlTree.WriteTreeToFile(fileName);
}

void Console::CannotChangePermissionUI() {
    cout << "�޸�Ȩ��ʧ��!" << endl;
}

void Console::PermisstionBitMapExplainedUI() {
    // explain the permission bit map
    cout << "Ȩ��λͼ˵��(1��ʾ�С�0��ʾ��):" << endl;
    cout << "��һλ:�����û�Ȩ��;" << endl;
    cout << "�ڶ�λ:��������ԱȨ��;" << endl;
    cout << "����λ:ɾ���û�Ȩ��;" << endl;
    cout << "����λ:ɾ������ԱȨ��;" << endl;
    cout << "����λ:�޸��û�Ȩ��;" << endl;
    cout << "����λ:�޸Ĺ���ԱȨ��;" << endl;
}

std::string Console::GetPermissionInput() {
    Console::PermisstionBitMapExplainedUI();
    string bitMapString;
    cout << "������6����Ȩ��01�ַ���:" << endl;
    cin >> bitMapString;
    if(bitMapString.length() != 6){
        cout << "������ַ������Ȳ�Ϊ6!" << endl;
        system("pause");
        return "";
    }else if(bitMapString.find_first_not_of("01") != string::npos){
        cout << "������ַ�������01�ַ���!" << endl;
        system("pause");
        return "";
    }
    return bitMapString;
}