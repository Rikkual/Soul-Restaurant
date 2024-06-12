cmake_minimum_required(VERSION 3.27)
project(Restaurant)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -static")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64")

set(QT_STATIC TRUE)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Sql
        Widgets
        REQUIRED
)

include_directories(.)
include_directories(LoginPage)
include_directories(AdminPage)
include_directories(UserPage)


add_executable(Restaurant
        main.cpp
        Config.cpp
        Debug.cpp
        DataBaseManager.cpp
        User.cpp
        Customer.cpp

        DebugWidget.cpp
        AboutWidget.cpp
        LoginPage/LoginDialog.cpp
        LoginPage/RegisterDialog.cpp
        AdminPage/AdminMainWindow.cpp
        AdminPage/Admin_OrderMgr.cpp
        AdminPage/Admin_MenuMgr.cpp
        AdminPage/Admin_TableMgr.cpp
        AdminPage/Admin_UserMgr.cpp
        AdminPage/MenuMgr_AddMeal.cpp
        AdminPage/TableMgr_Modify.cpp
        UserPage/UserMainWindow.cpp
        UserPage/User_TableInfo.cpp
        UserPage/User_CreateOrder.cpp
        UserPage/User_MyOrder.cpp
        UserPage/User_UserInfo.cpp
        UserPage/OrderMealDialog.cpp
        UserPage/MealOrderDialog.cpp
        UserPage/PayDepositDialog.cpp
)

# Copy the database file to the binary directory
configure_file(RestaurantDataBase.db ${CMAKE_CURRENT_BINARY_DIR}/RestaurantDataBase.db COPYONLY)

target_link_libraries(Restaurant
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Sql)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    file(COPY "${CMAKE_PREFIX_PATH}/plugins/sqldrivers/qsqlite.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/plugins/sqldrivers/")
endif ()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(WIN32)
        if(MSVC)
            set_target_properties(${PROJECT_NAME} PROPERTIES
                    LINKWIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
            )
        elseif(CMAKE_COMPILER_IS_GNUCXX)
            SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
        else()
            message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
        endif(MSVC)
    elseif(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES
                MACOSX_BUNDLE YES
        )
    elseif(UNIX)
        # Nothing special required
    else()
        message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
    endif(WIN32)
endif()

# 查找libstdc++-6.dll文件
find_file(STDCPP_DLL NAMES libstdc++-6.dll HINTS ${CMAKE_SOURCE_DIR}/path/to/dll)

# 添加自定义命令，在构建后复制DLL文件到输出目录
add_custom_command(TARGET Restaurant POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${STDCPP_DLL}
        $<TARGET_FILE_DIR:Restaurant>
)

# 复制DLL文件到输出目录
find_file(GCC_DLL NAMES libgcc_s_seh-1.dll HINTS ${CMAKE_SOURCE_DIR}/path/to/dll)

# 添加自定义命令，在构建后复制DLL文件到输出目录
add_custom_command(TARGET Restaurant POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GCC_DLL}
        $<TARGET_FILE_DIR:Restaurant>
)

install(TARGETS Restaurant
        RUNTIME DESTINATION bin
)

# 安装依赖的DLL
install(FILES ${CMAKE_SOURCE_DIR}/path/to/libstdc++-6.dll
        DESTINATION bin
)