//
// Created by Rikkual on 2024/6/5.
//

#ifndef DebugWidget_H
#define DebugWidget_H

#include <QWidget>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DebugWidget; }
QT_END_NAMESPACE

class DebugWidget : public QWidget {
Q_OBJECT

public:
    explicit DebugWidget(QWidget *parent = nullptr);

    ~DebugWidget() override;

private:
    Ui::DebugWidget *ui;

private slots:
    QT_UI_SLOT static void on_btnUserPage_clicked();
    QT_UI_SLOT static void on_btnAdminPage_clicked();
    QT_UI_SLOT static void on_btnLoginPage_clicked();
    QT_UI_SLOT static void on_btnAboutPage_clicked();
};


#endif // DebugWidget_H
