//
// Created by Rikkual on 2024/5/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LoginDialog.h" resolved

#include <QMessageBox>
#include <QRegularExpression>

#include "DataBaseManager.h"

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "RegisterDialog.h"
#include "AboutWidget.h"


LoginDialog::LoginDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::LoginDialog) {
    ui->setupUi(this);

    connect(ui->aboutLabel, &QLabel::linkActivated, this, []() {
        auto *aboutWidget = new AboutWidget;
        aboutWidget->setAttribute(Qt::WA_DeleteOnClose);
        aboutWidget->show();
    });
}

LoginDialog::~LoginDialog() {
    qDebug() << "~LoginDialog()";
    delete ui;
}

QT_UI_SLOT void LoginDialog::on_registerButton_clicked() {
    auto *registerDialog = new RegisterDialog(this);
    connect(registerDialog, &RegisterDialog::registerSignal, this, &LoginDialog::syncRegisterData);
    registerDialog->exec();
    delete registerDialog;
}

QT_UI_SLOT void LoginDialog::on_loginButton_clicked() {
    if(ui->userNameEditor->text().isEmpty() || ui->passwordEditor->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名或密码不能为空！");
        return;
    }
    // 识别是否为手机号登录
    QRegularExpression phoneNumberRegex("^1[3-9]\\d{9}$");
    if(phoneNumberRegex.match(ui->userNameEditor->text()).hasMatch()) {

    } else {
        user = User(ui->userNameEditor->text(), ui->passwordEditor->text());
        if (!DataBaseManager::checkUserName(user)) {
            QMessageBox::warning(this, "警告", "用户名不存在！");
            return;
        }
        if (DataBaseManager::getPasswordByUserName(user) != user.getPassword()) {
            QMessageBox::warning(this, "警告", "密码错误！");
            return;
        }
    }
    user = User(ui->userNameEditor->text(), ui->passwordEditor->text());
    user.setType(DataBaseManager::getTypeByUserName(user));
    return QDialog::accept();
}

QT_UI_SLOT void LoginDialog::on_exitButton_clicked() {
    this->close();
}

QT_UI_SLOT void LoginDialog::on_passwordCheckBox_stateChanged(int arg1) {
    if(arg1 == Qt::Checked) {
        ui->passwordEditor->setEchoMode(QLineEdit::Normal);
    }
    if(arg1 == Qt::Unchecked) {
        ui->passwordEditor->setEchoMode(QLineEdit::Password);
    }
}

void LoginDialog::syncRegisterData(const User &registeredUser) {
    ui->userNameEditor->setText(registeredUser.getUserName());
    ui->passwordEditor->setText(registeredUser.getPassword());
}

User LoginDialog::getUser() const {
    return user;
}