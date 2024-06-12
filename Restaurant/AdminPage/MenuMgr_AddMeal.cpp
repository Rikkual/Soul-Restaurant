//
// Created by Rikkual on 2024/6/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MenuMgr_AddMeal.h" resolved

#include "MenuMgr_AddMeal.h"
#include "ui_MenuMgr_AddMeal.h"

#include <QMessageBox>
#include "DataBaseManager.h"


MenuMgr_AddMeal::MenuMgr_AddMeal(QWidget *parent) :
        QDialog(parent), ui(new Ui::MenuMgr_AddMeal) {
    ui->setupUi(this);
    this->setWindowTitle("菜品添加");
}

MenuMgr_AddMeal::MenuMgr_AddMeal(int mealID, QWidget *parent):
        MenuMgr_AddMeal(parent) {
    this->mealID = mealID;
    ui->nameEdit->text() = DataBaseManager::getMealNameByMealID(mealID);
    ui->priceSpinBox->setValue(DataBaseManager::getMealPriceByMealID(mealID));
    ui->describeEdit->setPlainText(DataBaseManager::getMealDescriptionByMealID(mealID));
    this->setWindowTitle("菜品修改");
}

MenuMgr_AddMeal::~MenuMgr_AddMeal() {
    delete ui;
}

QT_UI_SLOT void MenuMgr_AddMeal::on_btnCancel_clicked() {
    this->close();
}

QT_UI_SLOT void MenuMgr_AddMeal::on_btnConfirm_clicked() {
    if(this->windowTitle() == "菜品添加") {
        addMeal();
        return;
    }
    if(this->windowTitle() == "菜品修改") {
        updateMeal();
        return;
    }
}

void MenuMgr_AddMeal::addMeal() {
    string mealName = ui->nameEdit->text();
    if(mealName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入菜品名称！");
        return;
    }
    double mealPrice = ui->priceSpinBox->value();
    string maalDesc = ui->describeEdit->toPlainText();
    DataBaseManager::insertMeal(mealName, mealPrice, maalDesc);
    this->close();
}

void MenuMgr_AddMeal::updateMeal() {

}
