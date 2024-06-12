//
// Created by Rikkual on 2024/5/22.
//

// QtSql
#include <QSqlQuery>
#include <QSqlError>

#include "DataBaseManager.h"

bool DataBaseManager::checkUserName(const User& user) {
    return checkUserName(user.getUserName());
}

bool DataBaseManager::checkUserName(const string& userName) {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM User WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return false;
    }
    return query.next();
}

string DataBaseManager::getPasswordByUserName(const User &user) {
    return getPasswordByUserName(user.getUserName());
}

string DataBaseManager::getPasswordByUserName(const string &userName) {
    QSqlQuery query;
    query.prepare("SELECT Password FROM user WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString password = {};
    if(query.next()) {
        password = query.value(0).toString();
    }
    return password;
}

int DataBaseManager::getTypeByUserName(const User &user) {
    return getTypeByUserName(user.getUserName());
}

int DataBaseManager::getTypeByUserName(const string &userName) {
    QSqlQuery query;
    query.prepare("SELECT Type FROM user WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    int type = -1;
    if(query.next()) {
        type = query.value(0).toInt();
    }
    return type;
}

void DataBaseManager::insertUser(const User &user) {
    QSqlQuery query;
    query.prepare("INSERT INTO User (UserName, Password, Type) VALUES (:UserName, :Password, :Type)");
    query.bindValue(":UserName", user.getUserName());
    query.bindValue(":Password", user.getPassword());
    query.bindValue(":Type", user.getType());
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "User added successfully";
}

void DataBaseManager::deleteUserByUserName(const string& userName) {
    QSqlQuery query;
    query.prepare("DELETE FROM User WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "User deleted successfully";
}

void DataBaseManager::insertCustomer(const Customer &customer) {
    QSqlQuery query;
    query.prepare("INSERT INTO Customer (UserName, Name, PhoneNumber) VALUES (:UserName, :Name, :PhoneNumber)");
    query.bindValue(":UserName", customer.getUserName());
    query.bindValue(":Name", customer.getName());
    query.bindValue(":PhoneNumber", customer.getPhoneNumber());
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Customer added successfully";
}

string DataBaseManager::getNameByUserName(const User &user) {
    return getNameByUserName(user.getUserName());
}

string DataBaseManager::getNameByUserName(const string &userName) {
    QSqlQuery query;
    query.prepare("SELECT Name FROM Customer WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString name = {};
    if(query.next()) {
        name = query.value(0).toString();
    }
    // qDebug() << "Name: " << name;
    return name;
}

string DataBaseManager::getPhoneNumberByUserName(const User &user) {
    return getPhoneNumberByUserName(user.getUserName());
}

string DataBaseManager::getPhoneNumberByUserName(const string &userName) {
    QSqlQuery query;
    query.prepare("SELECT PhoneNumber FROM Customer WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString phoneNumber = {};
    if(query.next()) {
        phoneNumber = query.value(0).toString();
    }
    // qDebug() << "PhoneNumber: " << phoneNumber;
    return phoneNumber;
}

int DataBaseManager::getCustomerIDByUserName(const User &user) {
    return getCustomerIDByUserName(user.getUserName());
}

int DataBaseManager::getCustomerIDByUserName(const string &userName) {
    QSqlQuery query;
    query.prepare("SELECT CustomerID FROM Customer WHERE UserName = :UserName");
    query.bindValue(":UserName", userName);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    int customerID = -1;
    if(query.next()) {
        customerID = query.value(0).toInt();
    }
    // qDebug() << "CustomerID: " << customerID;
    return customerID;
}

QStringList DataBaseManager::getAllCustomerUserName() {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM User Where Type = 0");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList userNameList;
    while(query.next()) {
        userNameList.append(query.value(0).toString());
    }
    return userNameList;
}

QStringList DataBaseManager::getCustomerUserNameByUserNameContain(const string &str) {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM Customer WHERE UserName LIKE :UserName");
    query.bindValue(":UserName", "%" + str + "%");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList userNameList;
    while(query.next()) {
        userNameList.append(query.value(0).toString());
    }
    return userNameList;
}

QStringList DataBaseManager::getCustomerUserNameByPhoneNumberContain(const string &str) {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM Customer WHERE PhoneNumber LIKE :PhoneNumber");
    query.bindValue(":PhoneNumber", "%" + str + "%");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList userNameList;
    while(query.next()) {
        userNameList.append(query.value(0).toString());
    }
    return userNameList;
}

QStringList DataBaseManager::getCustomerUserNameByNameContain(const string &str) {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM Customer WHERE Name LIKE :Name");
    query.bindValue(":Name", "%" + str + "%");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList userNameList;
    while(query.next()) {
        userNameList.append(query.value(0).toString());
    }
    return userNameList;
}

QList<int> DataBaseManager::getAllMealID() {
    QSqlQuery query;
    query.prepare("SELECT MealId FROM Meal");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QList<int> mealIDList;
    while(query.next()) {
        mealIDList.append(query.value(0).toInt());
    }
    return mealIDList;
}

QList<int> DataBaseManager::getMealIDByMealNameContain(const string &str) {
    QSqlQuery query;
    query.prepare("SELECT MealId FROM Meal WHERE MealName LIKE :MealName");
    query.bindValue(":MealName", "%" + str + "%");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QList<int> mealIDList;
    while(query.next()) {
        mealIDList.append(query.value(0).toInt());
    }
    return mealIDList;
}

string DataBaseManager::getMealNameByMealID(int mealID) {
    QSqlQuery query;
    query.prepare("SELECT MealName FROM Meal WHERE MealId = :MealId");
    query.bindValue(":MealId", mealID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString mealName = {};
    if(query.next()) {
        mealName = query.value(0).toString();
    }
    return mealName;
}

double DataBaseManager::getMealPriceByMealID(int mealID) {
    QSqlQuery query;
    query.prepare("SELECT MealPrice FROM Meal WHERE MealId = :MealId");
    query.bindValue(":MealId", mealID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    double mealPrice = -1;
    if(query.next()) {
        mealPrice = query.value(0).toDouble();
    }
    return mealPrice;
}

string DataBaseManager::getMealDescriptionByMealID(int mealID) {
    QSqlQuery query;
    query.prepare("SELECT MealDescription FROM Meal WHERE MealId = :MealId");
    query.bindValue(":MealId", mealID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString mealDescription = {};
    if(query.next()) {
        mealDescription = query.value(0).toString();
    }
    return mealDescription;
}

void DataBaseManager::insertMeal(const string &mealName, double mealPrice, const string &mealDescription) {
    QSqlQuery query;
    query.prepare("INSERT INTO Meal (MealName, MealPrice, MealDescription) VALUES (:MealName, :MealPrice, :MealDescription)");
    query.bindValue(":MealName", mealName);
    query.bindValue(":MealPrice", mealPrice);
    query.bindValue(":MealDescription", mealDescription);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Meal added successfully";
}

void DataBaseManager::deleteMealByMealID(int mealID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Meal WHERE MealId = :MealId");
    query.bindValue(":MealId", mealID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Meal deleted successfully";
}

QList<int> DataBaseManager::getAllTableTypeID() {
    QSqlQuery query;
    query.prepare("SELECT TableTypeID FROM Tables");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QList<int> tableIDList;
    while(query.next()) {
        tableIDList.append(query.value(0).toInt());
    }
    return tableIDList;
}

QStringList DataBaseManager::getAllTableCode() {
    QSqlQuery query;
    query.prepare("SELECT TableCode FROM Tables");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList tableCodeList;
    while(query.next()) {
        tableCodeList.append(query.value(0).toString());
    }
    return tableCodeList;
}

string DataBaseManager::getTableCodeByTableTypeID(int tableTypeID) {
    QSqlQuery query;
    query.prepare("SELECT TableCode FROM Tables WHERE TableTypeID = :TableTypeID");
    query.bindValue(":TableTypeID", tableTypeID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    string tableCode = {};
    if(query.next()) {
        tableCode = query.value(0).toString();
    }
    return tableCode;
}

string DataBaseManager::getTableTypeByTableCode(const string &tableCode) {
    QSqlQuery query;
    query.prepare("SELECT TableType FROM Tables WHERE TableCode = :TableCode");
    query.bindValue(":TableCode", tableCode);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString tableType = {};
    if(query.next()) {
        tableType = query.value(0).toString();
    }
    return tableType;
}

double DataBaseManager::getTableDepositByTableCode(const string &tableCode) {
    QSqlQuery query;
    query.prepare("SELECT TableDeposit FROM Tables WHERE TableCode = :TableCode");
    query.bindValue(":TableCode", tableCode);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    double tableDeposit = -1;
    if(query.next()) {
        tableDeposit = query.value(0).toDouble();
    }
    return tableDeposit;
}

int DataBaseManager::getTableNumberByTableCode(const string &tableCode) {
    QSqlQuery query;
    query.prepare("SELECT TableNumber FROM Tables WHERE TableCode = :TableCode");
    query.bindValue(":TableCode", tableCode);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    int tableNumber = -1;
    if(query.next()) {
        tableNumber = query.value(0).toInt();
    }
    return tableNumber;
}

string DataBaseManager::getTableCodeByTableType(const string& tableType) {
    QSqlQuery query;
    query.prepare("SELECT TableCode FROM Tables WHERE TableType = :TableType");
    query.bindValue(":TableType", tableType);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString tableCode = {};
    if(query.next()) {
        tableCode = query.value(0).toString();
    }
    return tableCode;
}

void DataBaseManager::insertTable(const string& tableType, const string& tableCode, double tableDeposit, int tableNumber) {
    QSqlQuery query;
    query.prepare("INSERT INTO Tables (TableType, TableCode, TableDeposit, TableNumber) VALUES (:TableType, :TableCode, :TableDeposit, :TableNumber)");
    query.bindValue(":TableType", tableType);
    query.bindValue(":TableCode", tableCode);
    query.bindValue(":TableDeposit", tableDeposit);
    query.bindValue(":TableNumber", tableNumber);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Table added successfully";
}

void DataBaseManager::updateTable(const string& tableCode, const string& tableType, double tableDeposit, int tableNumber) {
    QSqlQuery query;
    query.prepare("UPDATE Tables SET "
                  "TableType = :TableType, "
                  "TableDeposit = :TableDeposit, "
                  "TableNumber = :TableNumber "
                  "WHERE TableCode = :TableCode");
    query.bindValue(":TableType", tableType);
    query.bindValue(":TableDeposit", tableDeposit);
    query.bindValue(":TableNumber", tableNumber);
    query.bindValue(":TableCode", tableCode);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Table updated successfully";
}

void DataBaseManager::deleteTable(const string& tableCode) {
    QSqlQuery query;
    query.prepare("DELETE FROM Tables WHERE TableCode = :TableCode");
    query.bindValue(":TableCode", tableCode);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Table deleted successfully";
}

QStringList DataBaseManager::getAllOrderID() {
    QSqlQuery query;
    query.prepare("SELECT OrderID FROM Orders");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList orderIDList;
    while(query.next()) {
        orderIDList.append(query.value(0).toString());
    }
    return orderIDList;
}

int DataBaseManager::getCustomerIDByOrderID(const string &orderID) {
    QSqlQuery query;
    query.prepare("SELECT CustomerID FROM Orders WHERE OrderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    int customerID = -1;
    if(query.next()) {
        customerID = query.value(0).toInt();
    }
    return customerID;
}

string DataBaseManager::getUserNameByCustomerID(int customerID) {
    QSqlQuery query;
    query.prepare("SELECT UserName FROM Customer WHERE CustomerID = :CustomerID");
    query.bindValue(":CustomerID", customerID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    string userName = {};
    if(query.next()) {
        userName = query.value(0).toString();
    }
    return userName;
}

string DataBaseManager::getTableIDByOrderID(const string &orderID) {
    QSqlQuery query;
    query.prepare("SELECT TableID FROM Orders WHERE OrderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    string tableID = {};
    if(query.next()) {
        tableID = query.value(0).toString();
    }
    return tableID;
}

double DataBaseManager::getDepositByOrderID(const string &orderID) {
    QSqlQuery query;
    query.prepare("SELECT Deposit FROM Orders WHERE OrderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return -1;
    }
    double deposit = -1;
    if(query.next()) {
        deposit = query.value(0).toDouble();
    }
    return deposit;
}

string DataBaseManager::getReserveTimeByOrderID(const string& orderID) {
    QSqlQuery query;
    query.prepare("SELECT ReserveTime FROM Orders WHERE OrderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    string reserveTime = {};
    if(query.next()) {
        reserveTime = query.value(0).toString();
    }
    return reserveTime;
}

QStringList DataBaseManager::getAllOrderIDByDateAndTableCode(const string& date, const string& tableCode) {
    QSqlQuery query;
    query.prepare("SELECT OrderID FROM Orders WHERE ReserveTime LIKE :Date AND TableID LIKE :TableID");
    query.bindValue(":Date", date + "%");
    query.bindValue(":TableID", tableCode + "%");
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList orderIDList;
    while(query.next()) {
        orderIDList.append(query.value(0).toString());
    }
    return orderIDList;
}

QStringList DataBaseManager::getAllOrderIDByCustomerID(int customerID) {
    QSqlQuery query;
    query.prepare("SELECT OrderID FROM Orders WHERE CustomerID = :CustomerID");
    query.bindValue(":CustomerID", customerID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QStringList orderIDList;
    while(query.next()) {
        orderIDList.append(query.value(0).toString());
    }
    return orderIDList;
}

string DataBaseManager::getMealInfoByOrderID(const string &orderID) {
    QSqlQuery query;
    query.prepare("SELECT MealInfo FROM MealReserve WHERE orderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return {};
    }
    QString mealInfo = {};
    if(query.next()) {
        mealInfo = query.value(0).toString();
    }
    return mealInfo;
}

void
DataBaseManager::insertOrder(const string &orderID, int customerID, const string &tableID, const string &reserveTime,
                             double deposit) {
    QSqlQuery query;
    query.prepare("INSERT INTO Orders (OrderID, CustomerID, TableID, ReserveTime, Deposit) "
                  "VALUES (:OrderID, :CustomerID, :TableID, :ReserveTime, :Deposit)");
    query.bindValue(":OrderID", orderID);
    query.bindValue(":CustomerID", customerID);
    query.bindValue(":TableID", tableID);
    query.bindValue(":ReserveTime", reserveTime);
    query.bindValue(":Deposit", deposit);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Order added successfully";
}

void DataBaseManager::deleteOrderByOrderID(const string& orderID) {
    QSqlQuery query;
    query.prepare("DELETE FROM Orders WHERE OrderID = :OrderID");
    query.bindValue(":OrderID", orderID);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Order deleted successfully";
}

void DataBaseManager::insertMealReserve(const string &orderID, const string &mealInfo) {
    QSqlQuery query;
    query.prepare("INSERT INTO MealReserve (orderID, MealInfo) VALUES (:OrderID, :MealInfo)");
    query.bindValue(":OrderID", orderID);
    query.bindValue(":MealInfo", mealInfo);
    if(!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }
    qDebug() << "Meal reserve added successfully";
}
