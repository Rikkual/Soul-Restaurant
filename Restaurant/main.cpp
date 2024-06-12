//
// Created by Rikkual on 2024/5/8.
//

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

// QtSql
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "Config.h"
#include "Debug.h"
#include "User.h"

#include "LoginDialog.h"
#include "AdminMainWindow.h"
#include "UserMainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 链接Sqlite数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("RestaurantDatabase.db");
#ifdef DEBUG_MODE
    qDebug() << "Available drivers:" << QSqlDatabase::drivers();
    // qDebug() << "Plugin paths:" << QCoreApplication::libraryPaths();
#endif
    if(!db.open()) {
        qDebug() << "无法打开数据库！";
        qDebug() << db.lastError().text();
        QMessageBox::critical(nullptr, "Error", "无法打开数据库！");
    }

    // 调试代码
    if(Debug::debug()) {
        db.close();
        return 0;
    }

    LoginDialog login;
    login.show();
    if(login.exec() == QDialog::Accepted) {
        User user = login.getUser();
        if(user.getType() == User::ADMIN) {
            // TODO: 打开管理员界面
            qDebug() << "管理员界面" << Qt::endl;
            auto *adminMainWindow = new AdminMainWindow;
            adminMainWindow->setAttribute(Qt::WA_DeleteOnClose);
            adminMainWindow->show();
            // QApplication::exec();
        }
        if(user.getType() == User::USER) {
            // TODO: 打开用户界面
            qDebug() << "用户界面" << Qt::endl;
            auto *userMainWindow = new UserMainWindow(user);
            userMainWindow->setAttribute(Qt::WA_DeleteOnClose);
            userMainWindow->show();
            // QApplication::exec();
        }
    }
    QApplication::exec();
    db.close();
    return 0;
}