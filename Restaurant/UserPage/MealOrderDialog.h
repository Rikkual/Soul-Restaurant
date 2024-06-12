//
// Created by Rikkual on 2024/6/11.
//

#ifndef MealOrderDialog_H
#define MealOrderDialog_H

#include <QDialog>
#include <QStandardItemModel>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MealOrderDialog; }
QT_END_NAMESPACE

class MealOrderDialog : public QDialog {
Q_OBJECT


public:
    explicit MealOrderDialog(const string &orderID, QWidget *parent = nullptr);

    ~MealOrderDialog() override;

private:
    Ui::MealOrderDialog *ui;
    QStandardItemModel *model;
    QMap<int, int> reserveMap;

    void updateTableView();
    void reserveStringToMap(const string &reserveStr);

};


#endif // MealOrderDialog_H
