//
// Created by Rikkual on 2024/6/12.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PayDepositDialog.h" resolved

#include "PayDepositDialog.h"
#include "ui_PayDepositDialog.h"

#include <QMessageBox>


PayDepositDialog::PayDepositDialog(const string &username, const string &orderID,
                                     const QDateTime &orderTime, const QDateTime &reserveTime,
                                     const string &tableID, int personNumber,
                                     double tableDeposit, double cntPrice,
                                     QWidget *parent):
        username(username), orderID(orderID), orderTime(orderTime), reserveTime(reserveTime),
        tableID(tableID), personNumber(personNumber), tableDeposit(tableDeposit), cntPrice(cntPrice),
        QDialog(parent), ui(new Ui::PayDepositDialog) {
    ui->setupUi(this);
    ui->usernameLabel->setText(username);
    ui->orderIDLabel->setText(orderID);
    ui->orderTimeEdit->setDateTime(orderTime);
    ui->orderTimeEdit->setDisabled(true);
    ui->reserveTimeEdit->setDateTime(reserveTime);
    ui->reserveTimeEdit->setDisabled(true);
    ui->tableIDEdit->setText(tableID);
    ui->tableIDEdit->setDisabled(true);
    ui->personNumberSpinBox->setValue(personNumber);
    ui->personNumberSpinBox->setDisabled(true);
    ui->tableDepositLabel->setText(QString::number(tableDeposit, 'f', 2) + " 元");
    ui->cntPriceLabel->setText(QString::number(cntPrice, 'f', 2) + " * 30% = "
                             + QString::number(cntPrice * 0.3, 'f', 2) + " 元");
    double total = tableDeposit + cntPrice * 0.3;
    ui->depositLabel->setText(QString::number(tableDeposit, 'f', 2) + " + "
                             + QString::number(cntPrice * 0.3, 'f', 2) + " = "
                             + QString::number(total, 'f', 2) + " 元");
}

PayDepositDialog::~PayDepositDialog() {
    delete ui;
}

QT_UI_SLOT void PayDepositDialog::on_btnCancel_clicked() {
    return reject();
}

QT_UI_SLOT void PayDepositDialog::on_btnPayDeposit_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "订单支付", "确认支付订单吗？",
                                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        QMessageBox::information(this, "支付成功", "订单支付成功！");
        this->accept();
    }
    if(reply == QMessageBox::No) {
        return;
    }
}

QT_UI_SLOT void PayDepositDialog::on_btnMeal_clicked() {
    QMessageBox::information(this, "提示", "刚点的餐这就忘记了？返回去看吧！");
}
