//
// Created by Rikkual on 2024/6/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_User_MyOrder.h" resolved

#include "User_MyOrder.h"
#include "ui_User_MyOrder.h"

#include <QPushButton>

#include "DataBaseManager.h"
#include "MyQtTools.hpp"

#include "MealOrderDialog.h"


User_MyOrder::User_MyOrder(Customer *customer, QWidget *parent):
        model(nullptr),
        customer(customer),
        QWidget(parent), ui(new Ui::User_MyOrder) {
    ui->setupUi(this);
    model = new QStandardItemModel;
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({"订单号", "预定时间", "餐桌号", "定金", ""});
    ui->tableView->setColumnWidth(0, 150);
    ui->tableView->setColumnWidth(1, 120);

    orderIDList = DataBaseManager::getAllOrderIDByCustomerID(customer->getCustomerID());
    updateTableView();
}

User_MyOrder::~User_MyOrder() {
    delete ui;
    delete model;
}

void User_MyOrder::updateTableView() {
    model->removeRows(0, model->rowCount());
    foreach(string orderID, orderIDList) {
        string reserveTime = DataBaseManager::getReserveTimeByOrderID(orderID);
        string tableID = DataBaseManager::getTableIDByOrderID(orderID);
        double depositDouble = DataBaseManager::getDepositByOrderID(orderID);
        string deposit = QString::number(depositDouble, 'f', 2);
        model->appendRow(MyQtTools::addItem(orderID, reserveTime, tableID, deposit, "Meal"));

        QModelIndex index = model->index(model->rowCount() - 1, 4);
        auto *button = new QPushButton("订餐信息");
        button->setProperty("orderID", orderID);
        ui->tableView->setIndexWidget(index, button);
        connect(button, &QPushButton::clicked, this, [button, this]() {
            string orderID = button->property("orderID").toString();
            emit onSeeMealBtnClicked(orderID);
        });
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem({}));
    }
}

void User_MyOrder::onSeeMealBtnClicked(const string &orderID) {
    MealOrderDialog mealOrder(orderID, this);
    mealOrder.exec();
}

void User_MyOrder::updateMyOrder() {
    updateTableView();
}

void User_MyOrder::updateOrderIDList() {
    orderIDList = DataBaseManager::getAllOrderIDByCustomerID(customer->getCustomerID());
}
