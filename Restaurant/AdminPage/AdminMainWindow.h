//
// Created by Rikkual on 2024/5/22.
//

#ifndef AdminMainWindow_H
#define AdminMainWindow_H

#include <QMainWindow>

#include "Config.h"

#include "AboutWidget.h"
#include "Admin_OrderMgr.h"
#include "Admin_MenuMgr.h"
#include "Admin_TableMgr.h"
#include "Admin_UserMgr.h"


QT_BEGIN_NAMESPACE
namespace Ui { class AdminMainWindow; }
QT_END_NAMESPACE

class AdminMainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);

    ~AdminMainWindow() override;

private slots:
    // QT_UI_SLOT void on_btnOrder_clicked();
    // QT_UI_SLOT void on_btnMenu_clicked();
    // QT_UI_SLOT void on_btnTable_clicked();
    // QT_UI_SLOT void on_btnUser_clicked();

private:
    Ui::AdminMainWindow *ui;
    AboutWidget *aboutPage;
    Admin_OrderMgr *orderPage;
    Admin_TableMgr *tablePage;
    Admin_MenuMgr *menuPage;
    Admin_UserMgr *userPage;

public:
    void initStackedPage();
    void dealStackedPage();
};


#endif // AdminMainWindow_H
