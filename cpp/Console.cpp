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
    cout << "                            |           欢迎进入用户登陆查询系统                      |" << endl;
    cout << "                            |           1.用户登陆                                 |" << endl;
    cout << "                            |           2.注册用户                                 |" << endl;
    cout << "                            |           3.关闭系统                                 |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                                           请选择(1/2/3):" << endl;
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
    cout << "请输入用户名:" << endl;
    cin >> userName;
    cout << "请输入密码:" << endl;
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
    cout << "登陆失败,用户名或密码错误!" << endl;
}

Node *Console::Login(AVLTree &avlTree) {
    int tryTime = 0;
    Node* node = this->TryLogin(avlTree);
    while(!node){
        tryTime++;
        if(tryTime == 3){
            cout << "登陆失败次数过多,请稍后再试!" << endl;
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
    cout << "                            |           欢迎" << node->GetUserName() << "用户登陆查询系统" << endl;
    cout << "                            |           1.修改密码                                 |" << endl;
    cout << "                            |           2.注销                                    |" << endl;
    cout << "                            |           3.退出                                    |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    node->PrintPermission();
    cout << "                                           请选择(1/2):" << endl;
}

void Console::AdminUI(Node *node) {
    system("cls");
    cout << "                            ------------------------------------------------------" << endl;
    cout << "                            |           欢迎" << node->GetUserName() << "管理员登陆查询系统" << endl;
    cout << "                            |           1.修改密码                                 |" << endl;
    cout << "                            |           2.修改权限                                 |" << endl;
    cout << "                            |           3.注销用户                                 |" << endl;
    cout << "                            |           4.新增用户                                 |" << endl;
    cout << "                            |           5.退出                                     |" << endl;
    cout << "                            ------------------------------------------------------" << endl;
    node->PrintPermission();
    cout << "                                           请选择(1/2/3/4/5):" << endl;
}

void Console::DeleteUser(AVLTree &avlTree, Node *thisNode) {
    char choice;
    if(thisNode->GetIsAdmin()){
        cout << "是否要注销本账户(y/n)" << endl;
        cin >> choice;
        if(choice == 'y'){
           if(thisNode->GetBitMap().IsRoot()){
                cout << "您是根用户，无法注销" << endl;
               system("pause");
                return ;
           }
           avlTree.Delete(thisNode->GetUserName(), thisNode, avlTree.GetRoot());
            cout << "注销成功" << endl;
            avlTree.WriteTreeToFile(fileName);
            system("pause");
           nextPage = 1;
        }else if(choice == 'n'){
            cout << "请输入要注销的用户名" << endl;
            string userName;
            cin >> userName;
            avlTree.Delete(userName, thisNode, avlTree.GetRoot());
            avlTree.WriteTreeToFile(fileName);
        }else{
            cout << "输入错误" << endl;
            system("pause");
        }
    }else{
        cout << "您不是管理员，只能注销本账户，是否注销？(y/n)" << endl;
        cin >> choice;
        if(choice == 'y'){
            avlTree.Delete(thisNode->GetUserName(), thisNode, avlTree.GetRoot());
            cout << "注销成功" << endl;
            avlTree.WriteTreeToFile(fileName);
            system("pause");
            nextPage = 1;
        }else if(choice == 'n'){
            cout << "您不是管理员，无法注销其他用户" << endl;
            system("pause");
        }
    }
}

void Console::Register(AVLTree &avlTree, Node *currentUser) {
    if(currentUser->GetIsAdmin()){
        bool isAdmin;
        cout << "是否注册管理员(y/n)" << endl;
        string choice;
        cin >> choice;
        if(choice == "y"){
            isAdmin = true;
        }else if(choice == "n"){
            isAdmin = false;
        }else{
            cout << "输入错误" << endl;
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
    cout << "请输入用户名:" << endl;
    cin >> userName;
    cout << "请输入密码:" << endl;
    cin >> password;
    // check if the userName exist
    Node* node = avlTree.FindNodeByUserName(userName);
    if(node){
        cout << "用户名已存在!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "请再次输入密码:" << endl;
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "两次输入的密码不一致!" << endl;
        system("pause");
        return;
    }
    // register the user
    avlTree.Insert(userName, password, false, currentUser);
}

void Console::RegisterAdmin(AVLTree &avlTree, Node *currentUser) {
    // get the userName and check the password
    string userName, password, passwordCheck;
    cout << "请输入用户名:" << endl;
    cin >> userName;
    cout << "请输入密码:" << endl;
    cin >> password;
    // check if the userName exist
    Node* node = avlTree.FindNodeByUserName(userName);
    if(node){
        cout << "用户名已存在!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "请再次输入密码:";
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "两次输入的密码不一致!";
        system("pause");
        return;
    }
    // ask if you need to set the permission
    cout << "是否需要设置权限，不设置则将使用管理员默认权限？(y/n)" ;
    string choice;
    cin >> choice;
    string bitMapString;
    if(choice == "y"){
        cout << "请输入6比特权限字符串:" << endl;
        PermisstionBitMapExplainedUI();
        cin >> bitMapString;
    }else{
        bitMapString = ADMIN_PERMISSION_DEFAULT;
    }
    // register the user
    if(avlTree.Insert(userName, password, true, currentUser, bitMapString)){
        cout << "注册成功!" << endl;
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
    cout << "请输入原密码:" << endl;
    cin >> password;
    if(password != currentUser->GetPassword()){
        cout << "密码错误!" << endl;
        system("pause");
        return;
    }
    // double-check the password
    cout << "请输入新密码:" << endl;
    cin >> password;
    cout << "请再次输入新密码:" << endl;
    cin >> passwordCheck;
    if(password != passwordCheck){
        cout << "两次输入的密码不一致!" << endl;
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
    cout << "密码修改成功!" << endl;
}

void Console::ChangePermission(AVLTree &avlTree, Node *currentUser) {
    // first check if the user is admin
    if(!currentUser->GetIsAdmin()){
        cout << "您不是管理员，无法修改权限!" << endl;
        system("pause");
        return;
    }
    // get the userName
    string userName;
    cout << "请输入要修改权限的用户名:" << endl;
    cin >> userName;
    // check if the user exist
    Node* targetedUser = avlTree.FindNodeByUserName(userName);
    if(!targetedUser){
        cout << "该用户不存在!" << endl;
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
    cout << "修改权限失败!" << endl;
}

void Console::PermisstionBitMapExplainedUI() {
    // explain the permission bit map
    cout << "权限位图说明(1表示有、0表示无):" << endl;
    cout << "第一位:新增用户权限;" << endl;
    cout << "第二位:新增管理员权限;" << endl;
    cout << "第三位:删除用户权限;" << endl;
    cout << "第四位:删除管理员权限;" << endl;
    cout << "第五位:修改用户权限;" << endl;
    cout << "第六位:修改管理员权限;" << endl;
}

std::string Console::GetPermissionInput() {
    Console::PermisstionBitMapExplainedUI();
    string bitMapString;
    cout << "请输入6比特权限01字符串:" << endl;
    cin >> bitMapString;
    if(bitMapString.length() != 6){
        cout << "输入的字符串长度不为6!" << endl;
        system("pause");
        return "";
    }else if(bitMapString.find_first_not_of("01") != string::npos){
        cout << "输入的字符串不是01字符串!" << endl;
        system("pause");
        return "";
    }
    return bitMapString;
}