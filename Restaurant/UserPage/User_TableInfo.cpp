//
// Created by Rikkual on 2024/6/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_User_TableInfo.h" resolved

#include "User_TableInfo.h"
#include "ui_User_TableInfo.h"

#include <QPushButton>

#include "Config.h"
#include "MyQtTools.hpp"
#include "DataBaseManager.h"


User_TableInfo::User_TableInfo(QWidget *parent) :
        QWidget(parent), ui(new Ui::User_TableInfo) {
    ui->setupUi(this);
    model = new QStandardItemModel;
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({"餐桌名称", "餐桌定金", "餐桌代码", "餐桌数量", ""});
    tableIDList = DataBaseManager::getAllTableTypeID();
    updateTableView();
}

User_TableInfo::~User_TableInfo() {
    delete ui;
    delete model;
}

void User_TableInfo::updateTableView() {
    model->removeRows(0, model->rowCount());
    foreach(int itemID, tableIDList) {
        string tableID = QString::number(itemID);
        string tableCode = DataBaseManager::getTableCodeByTableTypeID(itemID);
        string tableType = DataBaseManager::getTableTypeByTableCode(tableCode);
        double tableDepositDouble = DataBaseManager::getTableDepositByTableCode(tableCode);
        string tableDeposit = QString::number(tableDepositDouble, 'f', 2);
        int tableNumberInt = DataBaseManager::getTableNumberByTableCode(tableCode);
        string tableNumber = QString::number(tableNumberInt);
        model->appendRow(MyQtTools::addItem(tableType, tableDeposit, tableCode, tableNumber, "Button"));

        QModelIndex index = model->index(model->rowCount() - 1, 4);
        auto *button = new QPushButton("预定");
        button->setProperty("tableID", tableID);
        ui->tableView->setIndexWidget(index, button);
        connect(button, &QPushButton::clicked, this, [button, this]() {
            int tableTypeID = button->property("tableID").toInt();
            emit createOrder(tableTypeID);
        });
    }
    if(model->rowCount() == 0) {
        model->appendRow({});
    }
}

void User_TableInfo::deleteTableViewButton() {

}
