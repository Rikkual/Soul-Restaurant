//
// Created by Rikkual on 2024/5/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RegistDialog.h" resolved

#include <QMessageBox>
#include <QRegularExpression>

#include "DataBaseManager.h"

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"


RegisterDialog::RegisterDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::RegisterDialog) {
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog() {
    delete ui;
}

QT_UI_SLOT void RegisterDialog::on_registerButton_clicked() {
    if(ui->usernameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入用户名!");
        return;
    }
    if(ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入密码!");
        return;
    }
    if(ui->passwordEdit->text() != ui->confirmPasswordEdit->text()) {
        QMessageBox::warning(this, "警告", "两次输入的密码不一致!");
        return;
    }

    QRegularExpression usernameRegex("^[a-zA-Z][a-zA-Z0-9_]*$");
    if(!usernameRegex.match(ui->usernameEdit->text()).hasMatch()) {
        QMessageBox::warning(this, "警告", "用户名只能包含字母、数字和下划线，且以字母开头!");
        return;
    }
    if(ui->phoneNumberEdit->text().length() != 11) {
        QMessageBox::warning(this, "警告", "手机号码长度不正确!");
        return;
    }
    QRegularExpression phoneNumberRegex("^1[3-9]\\d{9}$");
    if(!phoneNumberRegex.match(ui->phoneNumberEdit->text()).hasMatch()) {
        QMessageBox::warning(this, "警告", "手机号码格式不正确!");
        return;
    }

    User user = User(ui->usernameEdit->text(), ui->passwordEdit->text());
    if(DataBaseManager::checkUserName(user)) {
        QMessageBox::warning(this, "警告", "用户名已存在!");
        return;
    }

    Customer customer = Customer(user, ui->nameEdit->text(), ui->phoneNumberEdit->text());
    DataBaseManager::insertUser(customer);
    DataBaseManager::insertCustomer(customer);

    QMessageBox::information(this, "提示", "注册成功!");
    emit registerSignal(user);
    this->close();
}