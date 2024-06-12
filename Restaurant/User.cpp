//
// Created by Rikkual on 2024/5/21.
//

#include "User.h"

// NOLINTNEXTLINE
User::User(string _username, string _password, int _type): username(_username), password(_password), type(_type) {}

int User::getType() const {
    return type;
}

string User::getUserName() const {
    return username;
}

string User::getPassword() const {
    return password;
}

void User::setType(int _type) {
    type = _type;
}
