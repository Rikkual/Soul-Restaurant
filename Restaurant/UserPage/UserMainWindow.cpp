//
// Created by Rikkual on 2024/5/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserMainWindow.h" resolved

#include "UserMainWindow.h"
#include "ui_UserMainWindow.h"

#include <QMessageBox>

#include "DataBaseManager.h"


UserMainWindow::UserMainWindow(User &_user, QWidget *parent):
        aboutWidget(nullptr),
        tableInfo(nullptr), myOrder(nullptr), userInfo(nullptr),
        customer(_user),
        QMainWindow(parent), ui(new Ui::UserMainWindow) {
    ui->setupUi(this);
    customer.setCustomerID(DataBaseManager::getCustomerIDByUserName(customer));
    customer.setName(DataBaseManager::getNameByUserName(customer));
    customer.setPhoneNumber(DataBaseManager::getPhoneNumberByUserName(customer));
    qDebug() << "Customer ID: " << customer.getCustomerID();
    qDebug() << "Name: " << customer.getName();
    qDebug() << "PhoneNumber: " << customer.getPhoneNumber();
    this->setWindowTitle(this->windowTitle() + " - 用户名：" + customer.getUserName());

    aboutWidget = new AboutWidget(this);
    tableInfo = new User_TableInfo(this);
    myOrder = new User_MyOrder(&customer, this);
    userInfo = new User_UserInfo(&customer, this);

    ui->stackedWidget->addWidget(aboutWidget);
    ui->stackedWidget->addWidget(tableInfo);
    ui->stackedWidget->addWidget(myOrder);
    ui->stackedWidget->addWidget(userInfo);

    connect(tableInfo, &User_TableInfo::createOrder, this, &UserMainWindow::createOrderWithTable);
}

UserMainWindow::~UserMainWindow() {
    delete ui;
    delete aboutWidget;
    delete tableInfo;
}

QT_UI_SLOT void UserMainWindow::on_btnAbout_clicked() {
    qDebug() << "StackedPage: About";
    ui->stackedWidget->setCurrentWidget(aboutWidget);
}

QT_UI_SLOT void UserMainWindow::on_btnTable_clicked() {
    qDebug() << "StackedPage: Table";
    ui->stackedWidget->setCurrentWidget(tableInfo);
}

QT_UI_SLOT void UserMainWindow::on_btnCreateOrder_clicked() {
    // auto *createOrder = new User_CreateOrder(customer,this);
    // connect(&createOrder, &User_CreateOrder::updateMyOrder, myOrder, &User_MyOrder::updateMyOrder);
    // connect(createOrder, &User_CreateOrder::updateMyOrder, this, [this]() {
    //     myOrder->updateMyOrder();
    // });
    // createOrder->exec();
    // delete createOrder;
    User_CreateOrder createOrder(customer, this);
    if(createOrder.exec() == QDialog::Accepted) {
        qDebug() << "Create Order Success!";
        myOrder->updateOrderIDList();
        myOrder->updateMyOrder();
    }
}

QT_UI_SLOT void UserMainWindow::on_btnOrder_clicked() {
    qDebug() << "StackedPage: MyOrder";
    ui->stackedWidget->setCurrentWidget(myOrder);
}

QT_UI_SLOT void UserMainWindow::on_btnUser_clicked() {
    QMessageBox::information(this, "提示", "功能暂未开放, 修改请联系管理员！");
    qDebug() << "StackedPage: UserInfo";
    ui->stackedWidget->setCurrentWidget(userInfo);
}

void UserMainWindow::createOrderWithTable(int tableTypeID) {
    auto *createOrder = new User_CreateOrder(customer, tableTypeID, this);
    connect(createOrder, &User_CreateOrder::updateMyOrder, this, [this]() {
        myOrder->updateOrderIDList();
        myOrder->updateMyOrder();
    });
    createOrder->exec();
    disconnect(createOrder, &User_CreateOrder::updateMyOrder, this, nullptr);
    delete createOrder;
}