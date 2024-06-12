//
// Created by Rikkual on 2024/6/2.
//

#include "Debug.h"
#include "Config.h"
#include "User.h"
#include "Test.hpp"

#include <QApplication>
#include <QDebug>

#include "DebugWidget.h"
#include "LoginDialog.h"
#include "AdminMainWindow.h"
#include "UserMainWindow.h"
#include "AboutWidget.h"


bool Debug::debug() {
#ifdef TEST_MODE
    Test::test();
#endif
#ifndef DEBUG_MODE
    return false;
#endif
#ifdef DEBUG_WIDGET
    qDebug() << "Debug Widget" << Qt::endl;
    DebugWidget debugWidget;
    debugWidget.show();
    QApplication::exec();
    return true;
#endif
#ifdef ADMIN_DEBUG
    adminPageDebug();
#endif
#ifdef USER_DEBUG
    userPageDebug();
#endif
    QApplication::exec();
    return true;
}

void Debug::adminPageDebug() {
    qDebug() << "管理员界面" << Qt::endl;
    auto *adminMainWindow = new AdminMainWindow();
    adminMainWindow->setAttribute(Qt::WA_DeleteOnClose);
    adminMainWindow->show();
}

void Debug::userPageDebug(User user) {
    qDebug() << "用户界面" << Qt::endl;
    auto *userMainWindow = new UserMainWindow(user);
    userMainWindow->setAttribute(Qt::WA_DeleteOnClose);
    userMainWindow->show();
}

void Debug::loginPageDebug() {
    qDebug() << "登录界面" << Qt::endl;
    auto *login = new LoginDialog;
    // login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
    if(login->exec() == QDialog::Accepted) {
        User user = login->getUser();
        if(user.getType() == User::ADMIN) {
            adminPageDebug();
        }
        if(user.getType() == User::USER) {
            userPageDebug(user);
        }
    }
    delete login;
}

void Debug::aboutPageDebug() {
    qDebug() << "关于界面" << Qt::endl;
    auto *about = new AboutWidget;
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->show();
}
