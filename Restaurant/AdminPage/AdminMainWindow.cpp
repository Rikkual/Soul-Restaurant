//
// Created by Rikkual on 2024/5/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AdminMainWindow.h" resolved

#include "AdminMainWindow.h"
#include "ui_AdminMainWindow.h"


AdminMainWindow::AdminMainWindow(QWidget *parent):
        QMainWindow(parent), ui(new Ui::AdminMainWindow),
        aboutPage(nullptr),
        orderPage(nullptr), menuPage(nullptr), tablePage(nullptr), userPage(nullptr) {
    ui->setupUi(this);

    initStackedPage();
}

AdminMainWindow::~AdminMainWindow() {
    delete ui;
    delete aboutPage;
    delete orderPage;
    delete menuPage;
    delete tablePage;
    delete userPage;
}

void AdminMainWindow::initStackedPage() {
    aboutPage = new AboutWidget(this);
    orderPage = new Admin_OrderMgr(this);
    menuPage = new Admin_MenuMgr(this);
    tablePage = new Admin_TableMgr(this);
    userPage = new Admin_UserMgr(this);
    ui->stackedWidget->addWidget(aboutPage);
    ui->stackedWidget->addWidget(orderPage);
    ui->stackedWidget->addWidget(menuPage);
    ui->stackedWidget->addWidget(tablePage);
    ui->stackedWidget->addWidget(userPage);
    // ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentWidget(aboutPage);

    auto toolList = ui->toolList->children();
    for(auto it : toolList) {
        if(it->objectName().contains("btn")) {
            connect(dynamic_cast<QPushButton*>(it), &QPushButton::clicked, this, &AdminMainWindow::dealStackedPage);
        }
    }
    connect(ui->btnAbout, &QPushButton::clicked, this, &AdminMainWindow::dealStackedPage);
}

void AdminMainWindow::dealStackedPage() {
    auto str = sender()->objectName();
    if(str == "btnAbout") {
        if(ui->stackedWidget->currentWidget() != aboutPage) {
            ui->stackedWidget->setCurrentWidget(aboutPage);
            goto DBGOUT;
        }
        return;
    }
    if(str == "btnOrder") {
        if(ui->stackedWidget->currentWidget() != orderPage) {
            ui->stackedWidget->setCurrentWidget(orderPage);
            goto DBGOUT;
        }
        return;
    }
    if(str == "btnMenu") {
        if(ui->stackedWidget->currentWidget() != menuPage) {
            ui->stackedWidget->setCurrentWidget(menuPage);
            goto DBGOUT;
        }
        return;
    }
    if(str == "btnTable") {
        if(ui->stackedWidget->currentWidget() != tablePage) {
            ui->stackedWidget->setCurrentWidget(tablePage);
            goto DBGOUT;
        }
        return;
    }
    if(str == "btnUser") {
        if(ui->stackedWidget->currentWidget() != userPage) {
            ui->stackedWidget->setCurrentWidget(userPage);
            goto DBGOUT;
        }
        return;
    }
    DBGOUT:
    qDebug() << "StackedPage: " << str.mid(3);
}

/* 另一种实现方式
void AdminMainWindow::on_btnOrder_clicked() {
    qDebug() << "StackedPage: Order";
    ui->stackedWidget->setCurrentWidget(orderPage);
}

void AdminMainWindow::on_btnMenu_clicked() {
    qDebug() << "StackedPage: Menu";
    ui->stackedWidget->setCurrentWidget(menuPage);
}

void AdminMainWindow::on_btnTable_clicked() {
    qDebug() << "StackedPage: Table";
    ui->stackedWidget->setCurrentWidget(tablePage);
}

void AdminMainWindow::on_btnUser_clicked() {
    qDebug() << "StackedPage: User";
    ui->stackedWidget->setCurrentWidget(userPage);
}
*/