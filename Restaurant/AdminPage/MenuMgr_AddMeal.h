//
// Created by Rikkual on 2024/6/8.
//

#ifndef MenuMgr_AddMeal_H
#define MenuMgr_AddMeal_H

#include <QDialog>

#include "Config.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MenuMgr_AddMeal; }
QT_END_NAMESPACE

class MenuMgr_AddMeal : public QDialog {
Q_OBJECT

public:
    explicit MenuMgr_AddMeal(QWidget *parent = nullptr);
    MenuMgr_AddMeal(int mealID, QWidget *parent = nullptr);

    ~MenuMgr_AddMeal() override;

private:
    Ui::MenuMgr_AddMeal *ui;
    int mealID{};

private slots:
    QT_UI_SLOT void on_btnCancel_clicked();
    QT_UI_SLOT void on_btnConfirm_clicked();
    void addMeal();
    void updateMeal();
};


#endif // MenuMgr_AddMeal_H
