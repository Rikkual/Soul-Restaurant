//
// Created by Rikkual on 2024/6/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_AboutWidget.h" resolved

#include "AboutWidget.h"
#include "ui_AboutWidget.h"


AboutWidget::AboutWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::AboutWidget) {
    ui->setupUi(this);
}

AboutWidget::~AboutWidget() {
    delete ui;
}
