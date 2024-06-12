//
// Created by Rikkual on 2024/6/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_User_CreateOrder.h" resolved

#include "User_CreateOrder.h"
#include "ui_User_CreateOrder.h"

// #include "Config.h"
#include <QMessageBox>
#include "DataBaseManager.h"
#include "OrderMealDialog.h"
#include "PayDepositDialog.h"


User_CreateOrder::User_CreateOrder(const Customer &customer, QWidget *parent) :
        customer(customer),
        QDialog(parent), ui(new Ui::User_CreateOrder) {
    ui->setupUi(this);
    // 顾客姓名
    ui->usernameLabel->setText(customer.getUserName());
    // 订单ID
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->orderIDLabel->setText(generateOrderID(currentDateTime));
    // 订单时间
    ui->orderTimeEdit->setDateTime(currentDateTime);
    // 禁用时间编辑框，灰色不可编辑显示
    ui->orderTimeEdit->setDisabled(true);
    // 设置时间编辑框为只读，不可编辑
    ui->orderTimeEdit->setReadOnly(true);

    reserveDateTime = currentDateTime
            .addDays(1)
            .addSecs(- currentDateTime.time().hour() * 3600
                     - currentDateTime.time().minute() * 60
                     - currentDateTime.time().second()
                     - currentDateTime.time().msec() / 1000)
            .addSecs(12 * 3600);

    ui->reserveTimeEdit->setDateTime(reserveDateTime);

    auto tableIDList = DataBaseManager::getAllTableTypeID();
    foreach(int tableTypeID, tableIDList) {
        string tableCode = DataBaseManager::getTableCodeByTableTypeID(tableTypeID);
        string tableType = DataBaseManager::getTableTypeByTableCode(tableCode);
        ui->tableTypeComboBox->addItem(tableType, tableTypeID);
    }
    ui->tableTypeComboBox->setCurrentIndex(-1);
    connect(ui->tableTypeComboBox, &QComboBox::currentTextChanged,
            this, &User_CreateOrder::onTableTypeComboBoxTextChanged);

    ui->mealBoolLabel->setText("未完成餐品预订");
    ui->mealBoolLabel->setStyleSheet("color: red;");
}

User_CreateOrder::User_CreateOrder(const Customer &customer, int tableTypeID, QWidget *parent):
        User_CreateOrder(customer, parent) {
    // string tableCode = DataBaseManager::getTableCodeByTableTypeID(tableTypeID);
    // string tableType = DataBaseManager::getTableTypeByTableCode(tableCode);
    // ui->tableTypeComboBox->setCurrentText(tableType);
    ui->tableTypeComboBox->setCurrentIndex(ui->tableTypeComboBox->findData(tableTypeID));
}

User_CreateOrder::~User_CreateOrder() {
    delete ui;
}

void User_CreateOrder::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton btn = QMessageBox::question(
            this,
            tr("确认关闭"),
            tr("预约信息不会保存，您确定关闭吗？"),
            QMessageBox::Yes|QMessageBox::No,
            QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        event->accept();
    }
    if(btn == QMessageBox::No) {
        event->ignore();
    }
}

string User_CreateOrder::generateOrderID(QDateTime &dateTime) {
    orderID = dateTime.toString("yyyyMMddhhmmsszzz");
    return orderID;
}

void User_CreateOrder::onTableTypeComboBoxTextChanged(const string &tableType) {
    string tableCode = DataBaseManager::getTableCodeByTableType(tableType);
    tableID = tableCode; // + "114";
    tableDeposit = DataBaseManager::getTableDepositByTableCode(tableCode);
    QStringList orderIDList = DataBaseManager::getAllOrderIDByDateAndTableCode(reserveDateTime.toString("yyyy-MM-dd"), tableCode);
    int cnt = 0;
    QDateTime reserveTime = ui->reserveTimeEdit->dateTime();
    int reserveTimeInt = reserveTime.time().hour() * 60 + reserveTime.time().minute();
    // 存储已存在的数字编号，取mex{tableNumList}
    QList<int> tableNumList;
    foreach(string _orderID, orderIDList) {
        string itTimeStr = DataBaseManager::getReserveTimeByOrderID(_orderID);
        QDateTime itTime = QDateTime::fromString(itTimeStr, "yyyy-MM-dd hh:mm");
        int itTimeInt = itTime.time().hour() * 60 + itTime.time().minute();
        if(reserveTimeInt >= itTimeInt && reserveTimeInt < itTimeInt + 120) {
            cnt++;
        }
        else continue;
        string _tableID = DataBaseManager::getTableIDByOrderID(_orderID);
        // qDebug() << tableID << " " << _tableID;
        int number = 0;
        QRegularExpression regex("\\d+");
        QRegularExpressionMatch match = regex.match(_tableID);
        if(match.hasMatch()) {
            // qDebug() << "match: " << match.captured();
            number = match.captured().toInt();
            tableNumList.append(number);
        }
    }
    std::sort(tableNumList.begin(), tableNumList.end());
    int number = 1;
    for(int i = 0; i < tableNumList.size(); i++) {
        if(tableNumList[i] != i + 1) {
            break;
        }
        else number++;
    }
    tableID = tableCode + QString::number(number);
    int tableNumber = DataBaseManager::getTableNumberByTableCode(tableCode);
    if(tableNumber - cnt >= 1) {
        isTableEnabled = true;
        ui->tableStateLabel->setText("可预约，剩余" + QString::number(tableNumber - cnt) + "个位置");
        ui->tableStateLabel->setStyleSheet("color: green;");
    }
    else {
        isTableEnabled = false;
        ui->tableStateLabel->setText("无空位，不可预约");
        ui->tableStateLabel->setStyleSheet("color: red;");
        QMessageBox::warning(this, "警告", "该类餐桌已无空位，请选择其他餐桌或时间");
    }
}

QT_UI_SLOT void User_CreateOrder::on_btnCancel_clicked() {
    this->close();
}

QT_UI_SLOT void User_CreateOrder::on_btnConfirm_clicked() {
    if(!isTableEnabled) {
        QMessageBox::warning(this, "警告", "请先完成餐桌预约");
        return;
    }
    if(!isMealOrderEnabled) {
        QMessageBox::warning(this, "警告", "请先完成餐品预订");
        return;
    }
    string mealInfo = {};
    for(auto it = reserveMap.begin(); it!= reserveMap.end(); it++) {
        mealInfo += QString::number(it.key()) + ":" + QString::number(it.value()) + " ";
    }

    string userName = customer.getUserName();
    // orderID;
    QDateTime orderTime = ui->orderTimeEdit->dateTime();
    QDateTime reserveTime = ui->reserveTimeEdit->dateTime();
    // tableID;
    int personNumber = ui->personNumberSpinBox->value();
    // tableDeposit;
    // cntPrice;
    PayDepositDialog payDepositDialog(userName, orderID, orderTime, reserveTime, tableID, personNumber, tableDeposit, cntPrice);
    // this->hide();
    if(payDepositDialog.exec() == QDialog::Accepted) {
        qDebug() << "PayDeposit Successful!";
        string reserveTimeStr = ui->reserveTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm");
        DataBaseManager::insertOrder(orderID, customer.getCustomerID(), tableID, reserveTimeStr, cntPrice);
        DataBaseManager::insertMealReserve(orderID, mealInfo);
        emit updateMyOrder();
        return QDialog::accept();
    }
    // this->show();
}

QT_UI_SLOT void User_CreateOrder::on_btnMeal_clicked() {
    if(!isTableEnabled) {
        QMessageBox::warning(this, "警告", "请先完成餐桌预订");
        return;
    }
    int personNumber = ui->personNumberSpinBox->value();
    if(personNumber == 0) {
        QMessageBox::warning(this, "警告", "人数至少为1");
        return;
    }
    OrderMealDialog orderMealDialog(personNumber, this);
    if(orderMealDialog.exec() == QDialog::Accepted) {
        qDebug() << "OrderMeal Successful!";
        isMealOrderEnabled = true;
        ui->mealBoolLabel->setText("已完成餐品预订");
        ui->mealBoolLabel->setStyleSheet("color: green;");
    }
    else {
        isMealOrderEnabled = false;
        ui->mealBoolLabel->setText("未完成餐品预订");
        ui->mealBoolLabel->setStyleSheet("color: red;");
        ui->mealStateLabel->setText("未完成餐品预订");
        return;
    }
    reserveMap = orderMealDialog.getReserveMap();
    cntPrice = orderMealDialog.getCntPrice();
    ui->mealStateLabel->setText("餐食总价共计：" + QString::number(cntPrice) + "元");
}