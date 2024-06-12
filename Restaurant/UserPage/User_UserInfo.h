//
// Created by Rikkual on 2024/6/11.
//

#ifndef User_UserInfo_H
#define User_UserInfo_H

#include <QWidget>

#include "Customer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class User_UserInfo; }
QT_END_NAMESPACE

class User_UserInfo : public QWidget {
Q_OBJECT

public:
    explicit User_UserInfo(QWidget *parent = nullptr);
    User_UserInfo(Customer *customer, QWidget *parent = nullptr);

    ~User_UserInfo() override;

private:
    Ui::User_UserInfo *ui;
    Customer *customer;

};


#endif // User_UserInfo_H
