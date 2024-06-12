//
// Created by Rikkual on 2024/6/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Admin_UserMgr.h" resolved

#include "Admin_UserMgr.h"
#include "ui_Admin_UserMgr.h"

#include <QMessageBox>

// #include "Config.h"
#include "MyQtTools.hpp"
#include "DataBaseManager.h"

Admin_UserMgr::Admin_UserMgr(QWidget *parent) :
        QWidget(parent), ui(new Ui::Admin_UserMgr) {
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    // 设置表格为只读，不可编辑
    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    // 设置表头内容
    model->setHorizontalHeaderLabels(QStringList({"顾客ID", "用户名", "用户密码", "用户姓名", "手机号"}));
    // model->appendRow(*MyQtTools::addItem("100001", "admin", "123456", "管理员", "13812345678"));

    userNameList = DataBaseManager::getAllCustomerUserName();
    updateTableView();

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Admin_UserMgr::onReturnPressed);
}

Admin_UserMgr::~Admin_UserMgr() {
    delete ui;
    delete model;
}

void Admin_UserMgr::updateTableView() {
    model->removeRows(0, model->rowCount());
    foreach(auto &userName, userNameList) {
        string password = DataBaseManager::getPasswordByUserName(userName);
        string customerId = QString::number(DataBaseManager::getCustomerIDByUserName(userName));
        string Name = DataBaseManager::getNameByUserName(userName);
        string customerPhone = DataBaseManager::getPhoneNumberByUserName(userName);
        model->appendRow(MyQtTools::addItem(customerId, userName, password, Name, customerPhone));
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem("", "", "", "", ""));
    }
}

void Admin_UserMgr::onReturnPressed() {
    if(ui->comboBox->currentText() == "用户名") {
        string userName = ui->lineEdit->text();
        userNameList = DataBaseManager::getCustomerUserNameByUserNameContain(userName);
        updateTableView();
        return;
    }
    if(ui->comboBox->currentText() == "姓名") {
        string name = ui->lineEdit->text();
        userNameList = DataBaseManager::getCustomerUserNameByNameContain(name);
        updateTableView();
        return;
    }
    if(ui->comboBox->currentText() == "手机号") {
        string phoneNumber = ui->lineEdit->text();
        userNameList = DataBaseManager::getCustomerUserNameByPhoneNumberContain(phoneNumber);
        updateTableView();
        return;
    }
}

int Admin_UserMgr::getSelectedRow() {
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedRows();
    if(indexList.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择一行！");
        return -1;
    }
    if(indexList.count() > 1) {
        QMessageBox::warning(this, "警告", "只能选择一行！");
        return -1;
    }
    int row = indexList.first().row();
    return row;
}

QT_UI_SLOT void Admin_UserMgr::on_btnAdd_clicked() {
    QMessageBox::information(this, "提示", "我懒得写了，你自己去注册界面注册吧！");
}

QT_UI_SLOT void Admin_UserMgr::on_btnDelete_clicked() {
    int row = getSelectedRow();
    if(row == -1) return;
    string userName = userNameList[row];
    QMessageBox::StandardButton button = QMessageBox::question(this, "提示", "你确定要删除用户" + userName + "吗？",
                                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(button == QMessageBox::No) return;
    if(userName == Config::TEST_USER_NAME) {
        QMessageBox::warning(this, "警告", "测试用户不能删除！");
        return;
    }
    DataBaseManager::deleteUserByUserName(userName);
    userNameList.erase(userNameList.begin() + row);
    updateTableView();
}