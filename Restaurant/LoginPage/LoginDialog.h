//
// Created by Rikkual on 2024/5/21.
//

#ifndef LoginDialog_H
#define LoginDialog_H

#include <QDialog>

#include "Config.h"
#include "User.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog {
Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);

    ~LoginDialog() override;

private slots:
    QT_UI_SLOT void on_loginButton_clicked();
    QT_UI_SLOT void on_registerButton_clicked();
    QT_UI_SLOT void on_exitButton_clicked();
    QT_UI_SLOT void on_passwordCheckBox_stateChanged(int arg1);

private:
    Ui::LoginDialog *ui;
    User user;
    void syncRegisterData(const User &registeredUser);

public:
    [[nodiscard]] User getUser() const;

};


#endif // LoginDialog_H
