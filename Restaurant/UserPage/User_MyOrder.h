//
// Created by Rikkual on 2024/6/11.
//

#ifndef User_MyOrder_H
#define User_MyOrder_H

#include <QWidget>
#include <QStandardItemModel>

#include "Customer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class User_MyOrder; }
QT_END_NAMESPACE

class User_MyOrder : public QWidget {
Q_OBJECT

public:
    explicit User_MyOrder(Customer *customer, QWidget *parent = nullptr);

    ~User_MyOrder() override;

private:
    Ui::User_MyOrder *ui;
    Customer *customer;
    QStandardItemModel *model;
    QStringList orderIDList;

    void updateTableView();

public slots:
    void updateOrderIDList();
    void updateMyOrder();

private slots:
    void onSeeMealBtnClicked(const string& orderID);
};


#endif // User_MyOrder_H
