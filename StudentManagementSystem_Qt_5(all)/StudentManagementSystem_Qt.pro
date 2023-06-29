QT       += core gui
QT += core gui sql
Qt += charts
QT += charts
QT       += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core5compat
 QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17



FORMS += \
    fenxi.ui \
    menuwidget.ui \
    addstudentwidget.ui \
    modifywidget.ui \
    searchnoclear.ui \
    sortwidget.ui \
    selectwidget.ui \
    mainwidget.ui \
    tongji.ui

HEADERS += \
    fenxi.h \
    menuwidget.h \
    addstudentwidget.h \
    modifywidget.h \
    searchnoclear.h \
    sortwidget.h \
    selectwidget.h \
    mainwidget.h \
    studentinfo.h \
    tongji.h

SOURCES += \
    fenxi.cpp \
    menuwidget.cpp \
    addstudentwidget.cpp \
    modifywidget.cpp \
    searchnoclear.cpp \
    sortwidget.cpp \
    selectwidget.cpp \
    mainwidget.cpp \
    main.cpp \
    studentinfo.cpp \
    tongji.cpp

QT += widgets

DISTFILES += \
    1.jpg

RESOURCES += \
    photo.qrc
