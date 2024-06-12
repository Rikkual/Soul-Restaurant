//
// Created by Rikkual on 2024/5/22.
//

#ifndef UserMainWindow_H
#define UserMainWindow_H

#include <QMainWindow>

#include "Customer.h"
#include "Config.h"

#include "AboutWidget.h"
#include "User_TableInfo.h"
#include "User_CreateOrder.h"
#include "User_MyOrder.h"
#include "User_UserInfo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class UserMainWindow; }
QT_END_NAMESPACE

class UserMainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit UserMainWindow(User &_user, QWidget *parent = nullptr);

    ~UserMainWindow() override;

private:
    Ui::UserMainWindow *ui;
    Customer customer;
    AboutWidget *aboutWidget;
    User_TableInfo *tableInfo;
    User_MyOrder *myOrder;
    User_UserInfo *userInfo;

private slots:
    QT_UI_SLOT void on_btnAbout_clicked();
    QT_UI_SLOT void on_btnTable_clicked();
    QT_UI_SLOT void on_btnCreateOrder_clicked();
    QT_UI_SLOT void on_btnOrder_clicked();
    QT_UI_SLOT void on_btnUser_clicked();
    void createOrderWithTable(int tableTypeID);

signals:
    void updateMyOrder();
};


#endif // UserMainWindow_H