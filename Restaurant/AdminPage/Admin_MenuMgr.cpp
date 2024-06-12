//
// Created by Rikkual on 2024/5/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MenuMgr.h" resolved

#include "Admin_MenuMgr.h"
#include "ui_Admin_MenuMgr.h"

#include <QMessageBox>

// #include "Config.h"
#include "MyQtTools.hpp"
#include "DataBaseManager.h"

#include "MenuMgr_AddMeal.h"


Admin_MenuMgr::Admin_MenuMgr(QWidget *parent) :
        QWidget(parent), ui(new Ui::Admin_MenuMgr) {
    ui->setupUi(this);

    model = new QStandardItemModel;
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({"菜品编号", "菜品名称", "菜品价格", "菜品描述"});
    // ui->tableView->resizeColumnToContents(3);
    ui->tableView->setColumnWidth(3, 150);
    mealIDList = DataBaseManager::getAllMealID();
    updateTableView();

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &Admin_MenuMgr::onReturnPreesed);
}

Admin_MenuMgr::~Admin_MenuMgr() {
    delete ui;
    delete model;
}

void Admin_MenuMgr::updateTableView() {
    model->removeRows(0, model->rowCount());
    foreach(int itemID, mealIDList) {
        string mealID = QString::number(itemID);
        string mealName = DataBaseManager::getMealNameByMealID(itemID);
        double mealPriceDouble = DataBaseManager::getMealPriceByMealID(itemID);
        string mealPrice = QString::number(mealPriceDouble, 'f', 2);
        string mealDesc = DataBaseManager::getMealDescriptionByMealID(itemID);
        model->appendRow(MyQtTools::addItem(mealID, mealName, mealPrice, mealDesc));
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem({}));
    }
}

void Admin_MenuMgr::onReturnPreesed() {
    string mealName = ui->lineEdit->text();
    mealIDList = DataBaseManager::getMealIDByMealNameContain(mealName);
    updateTableView();
}

QT_UI_SLOT void Admin_MenuMgr::on_btnAddMeal_clicked() {
    MenuMgr_AddMeal addMeal(this);
    addMeal.exec();
    onReturnPreesed();
    updateTableView();
}

QT_UI_SLOT void Admin_MenuMgr::on_btnDeleteMeal_clicked() {
    int row = getSelectedRow();
    if(row == -1) return;
    int mealID = mealIDList[row];
    QMessageBox::StandardButton button = QMessageBox::question(this, "确认删除", "确认删除该菜品吗？",
                                                               QMessageBox::Yes | QMessageBox::No);
    if(button == QMessageBox::No) return;
    if(mealID == 1 || mealID == 2 || mealID == 3) {
        QMessageBox::warning(this, "警告", "不能删除默认菜品！");
        return;
    }
    DataBaseManager::deleteMealByMealID(mealID);
    mealIDList.erase(mealIDList.begin() + row);
    updateTableView();
}

int Admin_MenuMgr::getSelectedRow() {
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