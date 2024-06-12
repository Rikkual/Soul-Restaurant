//
// Created by Rikkual on 2024/5/21.
//

#ifndef User_H
#define User_H

#include "Config.h"

class User {
protected:
    string username;
    string password;
    int type = USER;

public:
    static const int USER = 0;
    static const int ADMIN = 1;

    User() = default;
    User(string _username, string _password, int _type = USER);
    [[nodiscard]] int getType() const;
    [[nodiscard]] string getUserName() const;
    [[nodiscard]] string getPassword() const;
    void setType(int _type);
};


#endif //User_H
