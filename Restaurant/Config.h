//
// Created by Rikkual on 2024/5/21.
//

#ifndef Config_H
#define Config_H

// 偷懒的宏定义，不建议这么用
#include <QString>
// #define string QString
typedef QString string;

#define CIALLO          // 各种娱乐功能

// #define DEBUG_MODE      // 调试模式
#define DEBUG_WIDGET    // 调试页面

#define ADMIN_DEBUG     // 管理员模式
// #define USER_DEBUG      // 用户模式

#define QT_UI_SLOT [[maybe_unused]]

namespace Config {
    extern const string ADMIN_NAME;
    extern const string ADMIN_PASSWORD;
    extern const string TEST_USER_NAME;
}

#endif //Config_H
