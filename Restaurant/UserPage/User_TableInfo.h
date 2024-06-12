//
// Created by Rikkual on 2024/6/9.
//

#ifndef User_TableInfo_H
#define User_TableInfo_H

#include <QWidget>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class User_TableInfo; }
QT_END_NAMESPACE

class User_TableInfo : public QWidget {
Q_OBJECT

public:
    explicit User_TableInfo(QWidget *parent = nullptr);

    ~User_TableInfo() override;

private:
    Ui::User_TableInfo *ui;
    QStandardItemModel *model;
    QList<int> tableIDList;

    void updateTableView();
    void deleteTableViewButton();

signals:
    void createOrder(int tableTypeID);
};


#endif // User_TableInfo_H
