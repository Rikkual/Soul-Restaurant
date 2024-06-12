//
// Created by Rikkual on 2024/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TableMgr_Modify.h" resolved

#include "TableMgr_Modify.h"
#include "ui_TableMgr_Modify.h"

#include <QMessageBox>

#include "DataBaseManager.h"


TableMgr_Modify::TableMgr_Modify(QWidget *parent) :
        QDialog(parent), ui(new Ui::TableMgr_Modify) {
    ui->setupUi(this);
    this->setWindowTitle("餐桌添加");
}

TableMgr_Modify::TableMgr_Modify(int tableID, QWidget *parent):
        TableMgr_Modify(parent) {
    this->setWindowTitle("餐桌修改");
    string tableCode = DataBaseManager::getTableCodeByTableTypeID(tableID);
    string tableType = DataBaseManager::getTableTypeByTableCode(tableCode);
    double tableDeposit = DataBaseManager::getTableDepositByTableCode(tableCode);
    int tableNumber = DataBaseManager::getTableNumberByTableCode(tableCode);
    ui->tableTypeEdit->setText(tableType);
    ui->tableTypeEdit->setDisabled(true);
    ui->tableCodeEdit->setText(tableCode);
    ui->tableCodeEdit->setDisabled(true);
    ui->depositSpinBox->setValue(tableDeposit);
    ui->numberSpinBox->setValue(tableNumber);
}

TableMgr_Modify::~TableMgr_Modify() {
    delete ui;
}

QT_UI_SLOT void TableMgr_Modify::on_btnCancel_clicked() {
    this->close();
}

QT_UI_SLOT void TableMgr_Modify::on_btnConfirm_clicked() {
    if(this->windowTitle() == "餐桌添加") {
        addTable();
        this->close();
    }
    if(this->windowTitle() == "餐桌修改") {
        modifyTable();
        this->close();
    }
}

void TableMgr_Modify::addTable() {
    string tableType = ui->tableTypeEdit->text();
    if(tableType == "") {
        QMessageBox::warning(this, "警告", "餐桌类型不能为空！");
        return;
    }
    string tableCode = ui->tableCodeEdit->text();
    if(tableCode == "") {
        QMessageBox::warning(this, "警告", "餐桌编号不能为空！");
        return;
    }
    double tableDeposit = ui->depositSpinBox->value();
    int tableNumber = ui->numberSpinBox->value();
    DataBaseManager::insertTable(tableType, tableCode, tableDeposit, tableNumber);
}

void TableMgr_Modify::modifyTable() {
    string tableType = ui->tableTypeEdit->text();
    string tableCode = ui->tableCodeEdit->text();
    double tableDeposit = ui->depositSpinBox->value();
    int tableNumber = ui->numberSpinBox->value();
    DataBaseManager::updateTable(tableCode, tableType, tableDeposit, tableNumber);
}