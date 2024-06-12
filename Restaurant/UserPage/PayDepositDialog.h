//
// Created by Rikkual on 2024/6/12.
//

#ifndef PayDepositDialog_H
#define PayDepositDialog_H

#include <QDialog>
#include <QDateTime>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class PayDepositDialog; }
QT_END_NAMESPACE

class PayDepositDialog : public QDialog {
Q_OBJECT

public:
    explicit PayDepositDialog(const string &username, const string &orderID,
                               const QDateTime &orderTime, const QDateTime &reserveTime,
                               const string &tableID, int personNumber,
                               double tableDeposit, double cntPrice,
                               QWidget *parent = nullptr);

    ~PayDepositDialog() override;

private:
    Ui::PayDepositDialog *ui;
    string username;
    string orderID;
    QDateTime orderTime;
    QDateTime reserveTime;
    string tableID;
    int personNumber;
    double tableDeposit;
    double cntPrice;

private slots:
    QT_UI_SLOT void on_btnCancel_clicked();
    QT_UI_SLOT void on_btnPayDeposit_clicked();
    QT_UI_SLOT void on_btnMeal_clicked();
};


#endif // PayDepositDialog_H
