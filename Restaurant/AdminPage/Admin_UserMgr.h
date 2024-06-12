//
// Created by Rikkual on 2024/6/1.
//

#ifndef Admin_UserMgr_H
#define Admin_UserMgr_H

#include <QWidget>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Admin_UserMgr; }
QT_END_NAMESPACE

class Admin_UserMgr : public QWidget {
Q_OBJECT

public:
    explicit Admin_UserMgr(QWidget *parent = nullptr);

    ~Admin_UserMgr() override;

private:
    Ui::Admin_UserMgr *ui;
    QStandardItemModel *model;
    QStringList userNameList;

    void updateTableView();
    int getSelectedRow();

private slots:
    void onReturnPressed();
    QT_UI_SLOT void on_btnAdd_clicked();
    QT_UI_SLOT void on_btnDelete_clicked();

};


#endif // Admin_UserMgr_H
