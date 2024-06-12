//
// Created by Rikkual on 2024/6/10.
//

#include <QDateTime>
#include <QDebug>

#include "DataBaseManager.h"

#define TEST_MODE

namespace Test {
    void test() {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        qDebug() << "当前时间:" << currentDateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
        auto list = DataBaseManager::getAllOrderIDByDateAndTableCode("1999-06-30", "D");
        qDebug() << "获取到" << list.size() << "个订单号";
    }
}