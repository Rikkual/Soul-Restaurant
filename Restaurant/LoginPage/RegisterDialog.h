//
// Created by Rikkual on 2024/5/21.
//

#ifndef RegistDialog_H
#define RegistDialog_H

#include <QDialog>

#include "User.h"
#include "Customer.h"
#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialog; }
QT_END_NAMESPACE

class RegisterDialog : public QDialog {
Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);

    ~RegisterDialog() override;

private:
    Ui::RegisterDialog *ui;

signals:
    void registerSignal(User user);

private slots:
    QT_UI_SLOT void on_registerButton_clicked();
};


#endif // RegistDialog_H
