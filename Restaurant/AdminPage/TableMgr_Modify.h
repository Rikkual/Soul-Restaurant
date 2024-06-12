//
// Created by Rikkual on 2024/6/10.
//

#ifndef TableMgr_Modify_H
#define TableMgr_Modify_H

#include <QDialog>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TableMgr_Modify; }
QT_END_NAMESPACE

class TableMgr_Modify : public QDialog {
Q_OBJECT

public:
    explicit TableMgr_Modify(QWidget *parent = nullptr);
    TableMgr_Modify(int tableTypeID, QWidget *parent = nullptr);

    ~TableMgr_Modify() override;

private:
    Ui::TableMgr_Modify *ui;
    void addTable();
    void modifyTable();

private slots:
    QT_UI_SLOT void on_btnCancel_clicked();
    QT_UI_SLOT void on_btnConfirm_clicked();
};


#endif // TableMgr_Modify_H
