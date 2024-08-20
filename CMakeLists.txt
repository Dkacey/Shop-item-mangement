cmake_minimum_required(VERSION 3.5)

project(Shop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h
        lineitem.cpp lineitem.h
        transaction.cpp transaction.h
        treeitem.cpp treeitem.h
        treemodel.cpp treemodel.h
        customers.h customers.cpp
        item.h item.cpp
        book.h book.cpp
        magazine.h magazine.cpp
        itemlist.h itemlist.cpp
        itemdialog.h itemdialog.cpp
        transactiondialog.h transactiondialog.cpp
        itemlistmemento.h itemlistmemento.cpp
        itemfactory.h itemfactory.cpp
        treemodeltoxml.h treemodeltoxml.cpp
        broadcast.h broadcast.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Shop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Shop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Shop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Shop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Shop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Xml Qt6::Network)

set_target_properties(Shop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Shop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Shop)
endif()
