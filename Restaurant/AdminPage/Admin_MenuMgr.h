//
// Created by Rikkual on 2024/5/31.
//

#ifndef Admin_MenuMgr_H
#define Admin_MenuMgr_H

#include <QWidget>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Admin_MenuMgr; }
QT_END_NAMESPACE

class Admin_MenuMgr : public QWidget {
Q_OBJECT

public:
    explicit Admin_MenuMgr(QWidget *parent = nullptr);

    ~Admin_MenuMgr() override;

private:
    Ui::Admin_MenuMgr *ui;
    QStandardItemModel *model;
    QList<int> mealIDList;

    void updateTableView();
    int getSelectedRow();

private slots:
    void onReturnPreesed();
    QT_UI_SLOT void on_btnAddMeal_clicked();
    QT_UI_SLOT void on_btnDeleteMeal_clicked();
};


#endif // Admin_MenuMgr_H
