//
// Created by Rikkual on 2024/6/3.
//

#ifndef MyQtTools_HPP
#define MyQtTools_HPP


#include "Config.h"
#include <QStandardItem>

class MyQtTools {
public:
    MyQtTools() = delete;

    static inline void addItemToList(QList<QStandardItem*>* items, const string &arg);
    template<typename... Args>
    static void addItemToList(QList<QStandardItem*>* items, const string &arg, Args... args);

    static inline QList<QStandardItem*> addItem(const string &arg);
    template<typename... Args>
    static QList<QStandardItem*> addItem(const string &arg, Args... args);
};

/*
 * 该函数会导致顺序变反，不使用该函数
QList<QStandardItem*>* MyQtTool::addItem(const string &arg) {
    auto items = new QList<QStandardItem*>;
    items->append(new QStandardItem(arg));
    return items;
}

template<typename... Args>
QList<QStandardItem*>* MyQtTool::addItem(const string &arg, Args... args) {
    auto items = addItem(args...);
    items->append(new QStandardItem(arg));
    return items;
}
*/

void MyQtTools::addItemToList(QList<QStandardItem*>* items, const string &arg) {
    items->append(new QStandardItem(arg));
}

template<typename... Args>
void MyQtTools::addItemToList(QList<QStandardItem*>* items, const string &arg, Args... args) {
    addItemToList(items, arg);
    addItemToList(items, args...);
}

QList<QStandardItem*> MyQtTools::addItem(const string &arg) {
    auto items = new QList<QStandardItem*>;
    addItemToList(items, arg);
    return *items;
}

template<typename... Args>
QList<QStandardItem*> MyQtTools::addItem(const string &arg, Args... args) {
    auto items = new QList<QStandardItem*>;
    addItemToList(items, arg, args...);
    return *items;
}


#endif //MyQtTools_HPP
