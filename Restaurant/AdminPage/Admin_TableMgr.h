//
// Created by Rikkual on 2024/6/1.
//

#ifndef Admin_TableMgr_H
#define Admin_TableMgr_H

#include <QWidget>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Admin_TableMgr; }
QT_END_NAMESPACE

class Admin_TableMgr : public QWidget {
Q_OBJECT

public:
    explicit Admin_TableMgr(QWidget *parent = nullptr);

    ~Admin_TableMgr() override;

private:
    Ui::Admin_TableMgr *ui;
    QStandardItemModel *model;
    // QStringList tableList;
    QList<int> tableTypeIDList;

    void updateTableView();
    int getSelectedRow();

private slots:
    QT_UI_SLOT void on_btnAdd_clicked();
    QT_UI_SLOT void on_btnModify_clicked();
    QT_UI_SLOT void on_btnDelete_clicked();
};


#endif // Admin_TableMgr_H
