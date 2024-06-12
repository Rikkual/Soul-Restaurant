//
// Created by Rikkual on 2024/6/1.
//

#ifndef Admin_OrderMgr_H
#define Admin_OrderMgr_H

#include <QWidget>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Admin_OrderMgr; }
QT_END_NAMESPACE

class Admin_OrderMgr : public QWidget {
Q_OBJECT

public:
    explicit Admin_OrderMgr(QWidget *parent = nullptr);

    ~Admin_OrderMgr() override;

private:
    Ui::Admin_OrderMgr *ui;
    QStandardItemModel *model;
    QStringList orderList;
    void updateTableView();
    int getSelectedRow();

private slots:
    void onReturnPressed();
    QT_UI_SLOT void on_btnDelete_clicked();
};


#endif // Admin_OrderMgr_H
