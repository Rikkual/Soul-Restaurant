//
// Created by Rikkual on 2024/6/9.
//

#ifndef User_CreateOrder_H
#define User_CreateOrder_H

#include <QDialog>
#include <QDateTime>
#include <QCloseEvent>

#include "Config.h"
#include "Customer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class User_CreateOrder; }
QT_END_NAMESPACE

class User_CreateOrder : public QDialog {
Q_OBJECT

public:
    explicit User_CreateOrder(const Customer &customer, QWidget *parent = nullptr);
    User_CreateOrder(const Customer &customer, int tableTypeID, QWidget *parent = nullptr);

    ~User_CreateOrder() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::User_CreateOrder *ui;
    Customer customer;
    QDateTime reserveDateTime;
    QMap<int, int> reserveMap;
    string orderID;
    string tableID;
    double cntPrice = 0;
    double tableDeposit = 0;
    bool isTableEnabled = false;
    bool isMealOrderEnabled = false;

    string generateOrderID(QDateTime &dateTime);

private slots:
    void onTableTypeComboBoxTextChanged(const QString &text);
    QT_UI_SLOT void on_btnCancel_clicked();
    QT_UI_SLOT void on_btnConfirm_clicked();
    QT_UI_SLOT void on_btnMeal_clicked();

signals:
    void updateMyOrder();
};


#endif // User_CreateOrder_H
