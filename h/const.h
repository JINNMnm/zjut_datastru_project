//
// Created by 31320 on 2023/10/15.
//

#ifndef CODE_CONST_H
#define CODE_CONST_H
#include <string>


const int PERMISSION_NUM = 6;

const int INSERT_USER_INDEX = 0;
const int INSERT_ADMIN_INDEX = 1;
const int DELETE_USER_INDEX = 2;
const int DELETE_ADMIN_INDEX = 3;
const int CHANGE_USER_INDEX = 4;
const int CHANGE_ADMIN_INDEX = 5;

const std::string USER_PERMISSION_DEFAULT = "100000";
const std::string ADMIN_PERMISSION_DEFAULT = "111010";

const std::string PERMISSION_STRING[PERMISSION_NUM] = {"新增用户权限","新增管理员权限",
                                                  "删除其他用户权限","删除其他管理员权限",
                                                  "修改其他用户权限","修改其他管理员权限"};

const std::string USER_FILE_PATH = "../txt/user.txt";

const int UI_LOGIN = 1;
const int UI_REGISTER = 2;
const int UI_CLOSE = 3;

const int ADMIN_UI_CHANGE_PASSWORD = 1;
const int ADMIN_UI_CHANGE_PERMISSION = 2;
const int ADMIN_UI_DESTROY_USER = 3;
const int ADMIN_UI_INSERT_USER = 4;
const int ADMIN_UI_RETURN = 5;

const int USER_UI_CHANGE_PASSWORD = 1;
const int USER_UI_CLOSE = 2;
const int USER_UI_RETURN = 3;

#endif //CODE_CONST_H
