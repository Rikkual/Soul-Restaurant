//
// Created by Rikkual on 2024/6/1.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Admin_TableMgr.h" resolved

#include "Admin_TableMgr.h"
#include "ui_Admin_TableMgr.h"

#include <QItemSelectionModel>
#include <QMessageBox>
#include "DataBaseManager.h"
#include "MyQtTools.hpp"

#include "TableMgr_Modify.h"

// #define SHOW_TABLETYPEID


Admin_TableMgr::Admin_TableMgr(QWidget *parent) :
        QWidget(parent), ui(new Ui::Admin_TableMgr) {
    ui->setupUi(this);
    model = new QStandardItemModel;
    ui->tableView->setModel(model);
    // ui->tableView->setSelectionMode(QTableView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
#ifdef SHOW_TABLETYPEID
    model->setHorizontalHeaderLabels({"餐桌编号", "餐桌类型", "餐桌定金", "餐桌代码", "餐桌数量"});
#else
    model->setHorizontalHeaderLabels({"餐桌类型", "餐桌代码", "餐桌定金", "餐桌数量"});
#endif

    // tableList = DataBaseManager::getAllTableCode();
    tableTypeIDList = DataBaseManager::getAllTableTypeID();
    updateTableView();
}

Admin_TableMgr::~Admin_TableMgr() {
    delete ui;
    delete model;
}

void Admin_TableMgr::updateTableView() {
    model->removeRows(0, model->rowCount());
    // foreach(auto tableCode, tableList) {
    foreach(int itemID, tableTypeIDList) {
        string tableTypeID = QString::number(itemID);
        string tableCode = DataBaseManager::getTableCodeByTableTypeID(itemID);
        string tableType = DataBaseManager::getTableTypeByTableCode(tableCode);
        double tableDepositDouble = DataBaseManager::getTableDepositByTableCode(tableCode);
        string tableDeposit = QString::number(tableDepositDouble, 'f', 2);
        int tableNumberInt = DataBaseManager::getTableNumberByTableCode(tableCode);
        string tableNumber = QString::number(tableNumberInt);
    #ifdef SHOW_TABLETYPEID
        model->appendRow(MyQtTools::addItem(tableID, tableType, tableCode, tableDeposit, tableNumber));
    #else
        model->appendRow(MyQtTools::addItem(tableType, tableCode, tableDeposit, tableNumber));
    #endif
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem({}));
    }
}

QT_UI_SLOT void Admin_TableMgr::on_btnAdd_clicked() {
    TableMgr_Modify modifyDialog(this);
    modifyDialog.exec();
    tableTypeIDList = DataBaseManager::getAllTableTypeID();
    updateTableView();
}

QT_UI_SLOT void Admin_TableMgr::on_btnModify_clicked() {
    int row = getSelectedRow();
    if(row == -1) return;
    int tableID = tableTypeIDList[row];
    // string tableCode = DataBaseManager::getTableCodeByTableTypeID(tableID);
    TableMgr_Modify modifyDialog(tableID, this);
    modifyDialog.exec();
    tableTypeIDList = DataBaseManager::getAllTableTypeID();
    updateTableView();
}

QT_UI_SLOT void Admin_TableMgr::on_btnDelete_clicked() {
    int row = getSelectedRow();
    if(row == -1) return;
    int tableID = tableTypeIDList[row];
    string tableCode = DataBaseManager::getTableCodeByTableTypeID(tableID);
    QMessageBox::StandardButton button = QMessageBox::question(this, "确认删除", "确认删除该餐桌吗？",
                                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(button == QMessageBox::No) return;
    DataBaseManager::deleteTable(tableCode);
    // 效率低，优化ed!
    // tableTypeIDList = DataBaseManager::getAllTableTypeID();
    tableTypeIDList.erase(tableTypeIDList.begin() + row);
    updateTableView();
}

int Admin_TableMgr::getSelectedRow() {
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
