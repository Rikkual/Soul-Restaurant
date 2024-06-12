//
// Created by Rikkual on 2024/6/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Admin_OrderMgr.h" resolved

#include "Admin_OrderMgr.h"
#include "ui_Admin_OrderMgr.h"

#include <QMessageBox>

#include "Config.h"
#include "DataBaseManager.h"
#include "MyQtTools.hpp"


Admin_OrderMgr::Admin_OrderMgr(QWidget *parent) :
        QWidget(parent), ui(new Ui::Admin_OrderMgr) {
    ui->setupUi(this);
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({"订单号", "用户名", "餐桌号", "预约时间", "定金金额"});
    // ui->tableView->resizeColumnToContents(3);
    ui->tableView->setColumnWidth(0, 150);
    ui->tableView->setColumnWidth(3, 120);

    ui->btnUser->hide();

    orderList = DataBaseManager::getAllOrderID();
    updateTableView();

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Admin_OrderMgr::onReturnPressed);
}

Admin_OrderMgr::~Admin_OrderMgr() {
    delete ui;
    delete model;
}

void Admin_OrderMgr::updateTableView() {
    model->removeRows(0, model->rowCount());
    foreach(auto orderID, orderList) {
        int CustomerID = DataBaseManager::getCustomerIDByOrderID(orderID);
        string userName = DataBaseManager::getUserNameByCustomerID(CustomerID);
        string tableID = DataBaseManager::getTableIDByOrderID(orderID);
        string reserveTime = DataBaseManager::getReserveTimeByOrderID(orderID);
        double depositDouble = DataBaseManager::getDepositByOrderID(orderID);
        string deposit = QString::number(depositDouble, 'f', 2);
        model->appendRow(MyQtTools::addItem(orderID, userName, tableID, reserveTime, deposit));
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem({}));
    }
}

void Admin_OrderMgr::onReturnPressed() {
    if(ui->comboBox->currentText() == "订单号") {
        return;
    }
    if(ui->comboBox->currentText() == "用户名") {
        return;
    }
    if(ui->comboBox->currentText() == "姓名") {
        return;
    }
    if(ui->comboBox->currentText() == "手机号") {
        return;
    }
}

void Admin_OrderMgr::on_btnDelete_clicked() {
    int row = getSelectedRow();
    if(row == -1) {
        return;
    }
    QMessageBox::StandardButton button = QMessageBox::question(this, "确认删除", "确认删除该订单？",
                                                               QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::No) return;
    string orderID = model->item(row, 0)->text();
    if(orderID == "20241145141919810") {
        QMessageBox::warning(this, "警告", "这是前辈留下的订单，无法删除！");
        return;
    }
    DataBaseManager::deleteOrderByOrderID(orderID);
    orderList.erase(orderList.begin() + row);
    updateTableView();
}

int Admin_OrderMgr::getSelectedRow() {
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedRows();
    if(indexList.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先选择一行！");
        return -1;
    }
    if(indexList.count() > 1) {
        QMessageBox::warning(this, "警告", "只能选择一行！");
        return -1;
    }
    int row = indexList.first().row();
    return row;
}
