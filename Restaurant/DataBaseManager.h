//
// Created by Rikkual on 2024/5/22.
//

#ifndef DateBaseManager_H
#define DateBaseManager_H

#include "Config.h"
#include "User.h"
#include "Customer.h"

class DataBaseManager {
public:
    /**
     * @brief 构造函数 = delete, 禁止实例化
     */
    DataBaseManager() = delete;

    /**
     * @brief 检查用户名是否存在
     * @param User表
     * @param userName 用户名
     * @return true 存在 false 不存在
     */
    static bool checkUserName(const string& userName);
    static bool checkUserName(const User& user);

    /**
     * @brief 通过用户名获取用户密码
     * @param User表
     * @param userName 用户名
     * @return QString 密码
     */
     static string getPasswordByUserName(const string& userName);
     static string getPasswordByUserName(const User& user);

     /**
      * @brief 通过用户名获取用户类型
      * @param User表
      * @param userName 用户名
      * @return int 用户类型
      */
     static int getTypeByUserName(const string& userName);
     static int getTypeByUserName(const User& user);

    /**
     * @brief 向数据库中添加新用户
     * @param User表
     * @param user 用户信息
     */
    static void insertUser(const User& user);

    /**
     * @brief 通过用户名删除用户
     * @param User表
     * @param userName 用户名
     */
    static void deleteUserByUserName(const string& userName);

    /**
     *  @brief 向顾客表中添加新顾客
     *  @param Customer表
     */
    static void insertCustomer(const Customer& customer);

    /**
     * @brief 通过用户名获取顾客姓名
     * @param Customer表
     * @return QString 姓名
     */
    static string getNameByUserName(const User& user);
    static string getNameByUserName(const string& userName);

    /**
     * @brief 通过用户名获取顾客电话
     * @param Customer表
     * @return QString 电话
     */
    static string getPhoneNumberByUserName(const User& user);
    static string getPhoneNumberByUserName(const string& userName);

    /**
     * @brief 通过用户名获取顾客ID
     * @param Customer表
     * @return int ID
     */
    static int getCustomerIDByUserName(const User& user);
    static int getCustomerIDByUserName(const string& userName);

    /**
     * @brief 获取所有顾客的用户名
     * @param User表
     * @return QStringList 用户名列表
     */
    static QStringList getAllCustomerUserName();

    /**
     * @brief 获取所有用户名包含str的顾客的用户名
     * @param Customer表
     * @param str 要搜索的字符串
     * @return QStringList 用户名列表
     */
    static QStringList getCustomerUserNameByUserNameContain(const string& str);

    /**
     * @brief 获取所有电话包含str的顾客的用户名
     * @param Customer表
     * @param str 要搜索的字符串
     * @return QStringList 用户名列表
     */
    static QStringList getCustomerUserNameByPhoneNumberContain(const string& str);

    /**
     * @brief 获取所有姓名包含str的顾客的用户名
     * @param Customer表
     * @param str 要搜索的字符串
     * @return QStringList 用户名列表
     */
    static QStringList getCustomerUserNameByNameContain(const string& str);

    /**
     * @brief 获取所有菜品ID
     * @param Meal表
     * @return QList<int> 菜品ID列表
     */
    static QList<int> getAllMealID();

     /**
      * @brief 获取所有菜品名称包含str的菜品ID
      * @param Meal表
      * @param str 要搜索的字符串
      * @return QList<int> 菜品ID列表
      */
     static QList<int> getMealIDByMealNameContain(const string& str);

     /**
      * @brief 通过菜品ID获取菜品名称
      * @param Meal表
      * @param mealID 菜品ID
      * @return QString 菜品名称
      */
      static string getMealNameByMealID(int mealID);

     /**
      * @brief 通过菜品ID获取菜品价格
      * @param Meal表
      * @param mealID 菜品ID
      * @return double 菜品价格
      */
     static double getMealPriceByMealID(int mealID);

     /**
      * @brief 通过菜品ID获取菜品描述
      * @param Meal表
      * @param mealID 菜品ID
      * @return QString 菜品描述
      */
     static string getMealDescriptionByMealID(int mealID);

     /**
      * @brief 添加新菜品
      * @param Meal表
      * @param mealName 菜品名称
      * @param mealPrice 菜品价格
      * @param mealDescription 菜品描述
      */
     static void insertMeal(const string& mealName, double mealPrice, const string& mealDescription);

     /**
      * @brief 通过菜品ID删除菜品
      * @param Meal表
      * @param mealID 菜品ID
      */
     static void deleteMealByMealID(int mealID);

     /**
      * @brief 获取所有餐桌编号
      * @param Tables表
      * @return QStringList 餐桌代码列表
      */
     static QList<int> getAllTableTypeID();

     /**
      * @brief 获取所有餐桌代码
      * @param Tables表
      * @return QStringList 餐桌代码列表
      */
     static QStringList getAllTableCode();

     /**
      * @brief 通过餐桌编号获取餐桌代码
      * @param Tables表
      * @param tableID 餐桌ID
      * @return QString 餐桌代码
      */
     static string getTableCodeByTableTypeID(int tableTypeID);

     /**
      * @brief 通过餐桌代码获取餐桌类型
      * @param Tables表
      * @param tableCode 餐桌代码
      * @return QString 餐桌类型
      */
     static string getTableTypeByTableCode(const string& tableCode);

      /**
       * @brief 通过餐桌代码获取餐桌定金
       * @param Tables表
       * @param tableCode 餐桌代码
       * @return double 餐桌定金
       */
      static double getTableDepositByTableCode(const string& tableCode);

      /**
       * @brief 通过餐桌代码获取餐桌数量
       * @param Tables表
       * @param tableCode 餐桌代码
       * @return int 餐桌数量
       */
      static int getTableNumberByTableCode(const string& tableCode);

      /**
       * @brief 通过餐桌类型获取餐桌代码
       * @param Tables表
       * @param tableType 餐桌类型
       * @return QString 餐桌代码
       * @note 若不存在该餐桌类型, 返回空字符串
       */
      static string getTableCodeByTableType(const string& tableType);

      /**
       * @brief 插入新餐桌
       * @param Tables表
       * @param tableType 餐桌类型
       * @param tableCode 餐桌代码
       * @param tableDeposit 餐桌定金
       * @param tableNumber 餐桌数量
       */
      static void insertTable(const string& tableType, const string& tableCode, double tableDeposit, int tableNumber);

      /**
       * @brief 更新餐桌代码为tableCode的餐桌信息
       * @param Tables表
       * @param tableCode 餐桌代码
       * @param tableType 餐桌类型
       * @param tableDeposit 餐桌定金
       * @param tableNumber 餐桌数量
       */
      static void updateTable(const string& tableCode, const string& tableType, double tableDeposit, int tableNumber);

      /**
       * @brief 删除餐桌代码为tableCode的餐桌信息
       * @param Tables表
       * @param tableCode 餐桌代码
       */
      static void deleteTable(const string& tableCode);

      /**
       * @brief 获取所有订单ID
       * @param Orders表
       * @return QStringList 订单ID列表
       */
      static QStringList getAllOrderID();

      /**
       * @brief 通过订单ID获取顾客ID
       * @param Orders表
       * @param orderID 订单ID
       * @return int 顾客ID
       */
      static int getCustomerIDByOrderID(const string& orderID);

      /**
       * @brief 通过顾客ID获取顾客用户名
       * @param Customer表
       * @param customerID 顾客ID
       * @param userName 顾客用户名
       */
      static string getUserNameByCustomerID(int customerID);

      /**
       * @brief 通过订单ID获取餐桌代码
       * @param Orders表
       * @param orderID 订单ID
       * @return QString 餐桌代码
       */
      static string getTableIDByOrderID(const string& orderID);

      /**
       * @brief 通过订单ID获取订单定金
       * @param Orders表
       * @param orderID 订单ID
       * @return double 订单定金
       */
      static double getDepositByOrderID(const string& orderID);

      /**
       * @brief 通过订单ID获取预定时间
       * @param Orders表
       * @param orderID 订单ID
       * @return string 预定时间
       */
      static string getReserveTimeByOrderID(const string& orderID);

      /**
       * @brief 查找在date当天, 餐桌代码为tableCode的所有订单ID
       * @param Orders表
       * @param date 日期
       * @param tableCode 餐桌代码
       * @return QStringList 订单ID列表
       */
      static QStringList getAllOrderIDByDateAndTableCode(const string& date, const string& tableCode);

      /**
       * @brief 通过顾客ID获取订单ID
       * @param Orders表
       * @param customerID 顾客ID
       * @return QStringList 订单ID列表
       */
      static QStringList getAllOrderIDByCustomerID(int customerID);

      /**
       * @brief 通过订单ID获取订餐信息
       * @param Orders表
       * @param orderID 订单ID
       * @return string 订餐信息
       */
      static string getMealInfoByOrderID(const string &orderID);

      /**
       * @brief 添加新订单
       * @param Orders表
       * @param orderID 订单ID
       * @param customerID 顾客ID
       * @param tableID 餐桌ID
       * @param reserveTime 预定时间
       * @param deposit 订单定金
       */
      static void insertOrder(const string& orderID, int customerID, const string& tableID, const string& reserveTime, double deposit);

      /**
       * @brief 通过订单ID删除订单
       * @param Orders表
       * @param orderID 订单ID
       * @note 同时删除MealReserve表中该订单的订餐信息
       */
      static void deleteOrderByOrderID(const string& orderID);

      /**
       * @brief 添加新订餐信息
       * @param MealReserve表
       * @param orderID 订单ID
       * @param mealInfo 订餐信息
       */
      static void insertMealReserve(const string &orderID, const string &mealInfo);
};


#endif //DateBaseManager_H
