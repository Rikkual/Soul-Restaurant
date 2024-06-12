//
// Created by Rikkual on 2024/6/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MealOrderDialog.h" resolved

#include "MealOrderDialog.h"
#include "ui_MealOrderDialog.h"

#include <QRegularExpression>

#include "DataBaseManager.h"
#include "MyQtTools.hpp"

#define DECOLLATOR_LENTH 30 // 菜名与价格之间的分隔符长度


MealOrderDialog::MealOrderDialog(const string &orderID, QWidget *parent):
        model(nullptr),
        QDialog(parent), ui(new Ui::MealOrderDialog) {
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    ui->tableView->setModel(model);
    model->setHorizontalHeaderLabels({"选菜信息"});
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnWidth(0, ui->tableView->width()); // 设置第一列的宽度为表格宽度
    ui->tableView->setColumnHidden(1, true); // 如有第二列，将其隐藏

    string mealInfo = DataBaseManager::getMealInfoByOrderID(orderID);
    reserveStringToMap(mealInfo);
    updateTableView();
}

MealOrderDialog::~MealOrderDialog() {
    delete ui;
    delete model;
}

void MealOrderDialog::updateTableView() {
    model->removeRows(0, model->rowCount());
    double cntPrice = 0;
    for(auto it = reserveMap.begin(); it != reserveMap.end(); it++) {
        int mealID = it.key();
        int mealNum = it.value();
        if(mealNum == 0) continue;
        string mealName = DataBaseManager::getMealNameByMealID(mealID);
        // qDebug() << "mealName: " << mealName;
        string res = mealName;
        for(int i = 1; i <= DECOLLATOR_LENTH - mealName.length() * 2; i++) {
            res += "-";
        }
        double mealPriceDouble = DataBaseManager::getMealPriceByMealID(mealID);
        string mealPrice = QString::number(mealPriceDouble, 'f', 2);
        res += mealPrice + "元 * " + QString::number(mealNum) + "份";
        model->appendRow(MyQtTools::addItem(res));
        qDebug() << res;
        cntPrice += mealPriceDouble * mealNum;
    }
    ui->priceLabel->setText(QString::number(cntPrice, 'f', 2));
    qDebug() << "total price: " << cntPrice;
}

void MealOrderDialog::reserveStringToMap(const string &reserveStr) {
    QStringList pairs = reserveStr.split(" ", Qt::SkipEmptyParts);
    for(const auto& pair : pairs) {
        QRegularExpression regex("^(\\d+):(\\d+)$");
        QRegularExpressionMatch match = regex.match(pair);
        if(match.hasMatch()) {
            int mealID = match.captured(1).toInt();
            int mealNum = match.captured(2).toInt();
            reserveMap[mealID] = mealNum;
        }
    }
}
