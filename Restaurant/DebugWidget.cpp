//
// Created by Rikkual on 2024/6/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DebugWidget.h" resolved

#include "DebugWidget.h"
#include "ui_DebugWidget.h"

#include "Debug.h"

DebugWidget::DebugWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::DebugWidget) {
    ui->setupUi(this);
}

DebugWidget::~DebugWidget() {
    delete ui;
}

QT_UI_SLOT void DebugWidget::on_btnUserPage_clicked() {
    Debug::userPageDebug();
}

QT_UI_SLOT void DebugWidget::on_btnAdminPage_clicked() {
    Debug::adminPageDebug();
}

QT_UI_SLOT void DebugWidget::on_btnLoginPage_clicked() {
    Debug::loginPageDebug();
}

QT_UI_SLOT void DebugWidget::on_btnAboutPage_clicked() {
    Debug::aboutPageDebug();
}
