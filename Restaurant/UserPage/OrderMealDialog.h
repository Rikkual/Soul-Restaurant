//
// Created by Rikkual on 2024/6/10.
//

#ifndef OrderMealDialog_H
#define OrderMealDialog_H

#include <QDialog>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class OrderMealDialog; }
QT_END_NAMESPACE

class OrderMealDialog : public QDialog {
Q_OBJECT

public:
    explicit OrderMealDialog(QWidget *parent = nullptr);
    OrderMealDialog(int personNum, QWidget *parent = nullptr);

    ~OrderMealDialog() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::OrderMealDialog *ui;
    QStandardItemModel *model;
    QStandardItemModel *reserveModel;
    QList<int> mealIDList;
    QMap<int, int> reserveMap; // key: mealID, value: reserveNum
    double cntPrice = 0;

    void updateTableView();
    void updateReserveView();

signals:
    // void deleteTableViewSpinBox();

private slots:
    void onReturnPreesed();
    QT_UI_SLOT void on_btnCancel_clicked();
    QT_UI_SLOT void on_btnConfirm_clicked();

public:
    QMap<int, int> getReserveMap();
    double getCntPrice();

};


#endif // OrderMealDialog_H
