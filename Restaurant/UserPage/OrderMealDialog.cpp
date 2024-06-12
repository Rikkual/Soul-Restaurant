//
// Created by Rikkual on 2024/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_OrderMealDialog.h" resolved

#include "OrderMealDialog.h"
#include "ui_OrderMealDialog.h"

#include <QSpinBox>
#include <QMessageBox>
#include <QCloseEvent>

#include "DataBaseManager.h"
#include "MyQtTools.hpp"


OrderMealDialog::OrderMealDialog(QWidget *parent):
        model(nullptr), reserveModel(nullptr),
        QDialog(parent), ui(new Ui::OrderMealDialog) {
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setHorizontalHeaderLabels({"菜品编号", "菜品名称", "菜品价格", "菜品描述", ""});
    ui->tableView->setColumnWidth(3, 150);
    // mealIDList = DataBaseManager::getAllMealID();
    // updateTableView();

    reserveModel = new QStandardItemModel(this);
    ui->reserveView->setModel(reserveModel);
    reserveModel->setHorizontalHeaderLabels({"选菜信息"});
    ui->reserveView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reserveView->horizontalHeader()->hide();
    ui->reserveView->verticalHeader()->hide();
    ui->reserveView->setColumnWidth(0, ui->reserveView->width()); // 设置第一列的宽度为表格宽度
    ui->reserveView->setColumnHidden(1, true); // 如有第二列，将其隐藏

    updateReserveView();
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &OrderMealDialog::onReturnPreesed);
}

OrderMealDialog::OrderMealDialog(int personNum, QWidget *parent):
        OrderMealDialog(parent) {
    reserveMap[1] = personNum;
    updateReserveView();
    onReturnPreesed();
}

OrderMealDialog::~OrderMealDialog() {
    delete ui;
    delete model;
    delete reserveModel;
}

void OrderMealDialog::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton btn = QMessageBox::question(
            this,
            tr("确认关闭"),
            tr("订餐信息不会保存，您确定关闭吗？"),
            QMessageBox::Yes|QMessageBox::No,
            QMessageBox::No);
    if(btn == QMessageBox::Yes) {
        event->accept();
    }
    if(btn == QMessageBox::No) {
        event->ignore();
    }
}

void OrderMealDialog::updateTableView() {
    // emit deleteTableViewSpinBox();
    model->removeRows(0, model->rowCount());
    foreach(int itemID, mealIDList) {
        string mealID = QString::number(itemID);
        string mealName = DataBaseManager::getMealNameByMealID(itemID);
        double mealPriceDouble = DataBaseManager::getMealPriceByMealID(itemID);
        string mealPrice = QString::number(mealPriceDouble, 'f', 2);
        string mealDesc = DataBaseManager::getMealDescriptionByMealID(itemID);
        model->appendRow(MyQtTools::addItem(mealID, mealName, mealPrice, mealDesc, "SpinBox"));

        QModelIndex index = model->index(model->rowCount() - 1, 4);
        auto *spinBox = new QSpinBox(this);
        spinBox->setValue(reserveMap[itemID]);
        spinBox->setProperty("mealID", mealID);
        ui->tableView->setIndexWidget(index, spinBox);
        connect(spinBox, &QSpinBox::valueChanged, this, [spinBox, this](int value) {
            int mealID = spinBox->property("mealID").toInt();
            if(reserveMap[mealID] == value) return;
            reserveMap[mealID] = value;
            updateReserveView();
        });
        // connect(this, &OrderMealDialog::deleteTableViewSpinBox, this, [spinBox, this]() {
        //     delete spinBox;
        // });
    }
    if(model->rowCount() == 0) {
        model->appendRow(MyQtTools::addItem({}));
    }
}

void OrderMealDialog::updateReserveView() {
    reserveModel->removeRows(0, reserveModel->rowCount());
    cntPrice = 0;
    for(auto it = reserveMap.begin(); it != reserveMap.end(); it++) {
        int mealID = it.key();
        int mealNum = it.value();
        if(mealNum == 0) continue;
        string mealName = DataBaseManager::getMealNameByMealID(mealID);
        string res = mealName;
        for(int i = 1; i <=  20 - mealName.length() * 2; i++) {
            res += "-";
        }
        double mealPriceDouble = DataBaseManager::getMealPriceByMealID(mealID);
        string mealPrice = QString::number(mealPriceDouble, 'f', 2);
        res += mealPrice + "元 * " + QString::number(mealNum) + "份";
        reserveModel->appendRow(MyQtTools::addItem(res));
        cntPrice += mealPriceDouble * mealNum;
    }
    ui->priceLabel->setText(QString::number(cntPrice, 'f', 2));
}

void OrderMealDialog::onReturnPreesed() {
    string mealName = ui->lineEdit->text();
    mealIDList = DataBaseManager::getMealIDByMealNameContain(mealName);
    updateTableView();
}

QT_UI_SLOT void OrderMealDialog::on_btnCancel_clicked() {
    this->close();
}

QT_UI_SLOT void OrderMealDialog::on_btnConfirm_clicked() {
    return QDialog::accept();
}

QMap<int, int> OrderMealDialog::getReserveMap() {
    return reserveMap;
}

double OrderMealDialog::getCntPrice() {
    return cntPrice;
}