//
// Created by Rikkual on 2024/6/2.
//

#ifndef Debug_H
#define Debug_H

#include <QWidget>
#include "User.h"

class Debug {
private:
public:
    Debug() = delete;
    static bool debug();
    static void adminPageDebug();
    static void userPageDebug(User user = User("test", "test"));
    static void loginPageDebug();
    static void aboutPageDebug();
};


#endif //Debug_H
