//
// Created by Rikkual on 2024/6/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_User_UserInfo.h" resolved

#include "User_UserInfo.h"
#include "ui_User_UserInfo.h"


User_UserInfo::User_UserInfo(QWidget *parent) :
        customer(nullptr),
        QWidget(parent), ui(new Ui::User_UserInfo) {
    ui->setupUi(this);
}

User_UserInfo::User_UserInfo(Customer *customer, QWidget *parent):
        User_UserInfo(parent) {
    this->customer = customer;
}

User_UserInfo::~User_UserInfo() {
    delete ui;
}

