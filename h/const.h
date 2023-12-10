//
// Created by 31320 on 2023/10/15.
//

#ifndef CODE_CONST_H
#define CODE_CONST_H
#include <string>
#define goto(x, y) printf("\033[%d;%dH", (y+2), (x+2))

const std::string USER_FILE_PATH =
    "/Users/jin/Downloads/uni/code/c++/data_structure/zjut/final "
    "work/finalWorkResult/code/txt/user.txt";
const std::string BOOK_FILE_PATH =
    "/Users/jin/Downloads/uni/code/c++/data_structure/zjut/final "
    "work/finalWorkResult/code/txt/book.txt";

const int UI_LOGIN = 1;
const int UI_REGISTER = 2;
const int UI_CLOSE = 3;

const int ADMIN_ADD_BOOK = 1;
const int ADMIN_DELETE_BOOK = 2;
const int ADMIN_QUERY_BOOK = 3;
const int ADMIN_DISPLAY_BOOK = 4;
const int ADMIN_DISPLAY_USER = 5;
const int ADMIN_DELETE_USER = 6;
const int ADMIN_LOGOUT = 7;

const int USER_BORROW_BOOK = 1;
const int USER_RETURN_BOOK = 2;
const int USER_QUERY_BOOK = 3;
const int USER_DELETE_SELF = 4;
const int USER_LOGOUT = 5;

#endif // CODE_CONST_H
