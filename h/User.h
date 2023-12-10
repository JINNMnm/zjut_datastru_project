#ifndef USER_H
#define USER_H
#include "Node.h"
#include "AVLTree.h"
#include <ostream>

class User: public Node
{
public:
    // Constructor 
    User();
    User(string ID, string password, bool isAdmin);
    User(User& user);

    // Destructor
    ~User() = default;

    // getter and setter
    string getPassword();
    void setPassword(string password);
    bool getAdmin();
    void setAdmin(bool isAdmin);


    // overwrite operater =
    Node& operator=(Node& user);

    // implement virtual function
    void print(ofstream& os);
    void print();
private:
    string password;
    bool isAdmin;
};
#endif // USER_H
