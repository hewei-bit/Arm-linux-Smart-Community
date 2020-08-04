#-------------------------------------------------
#
# Project created by QtCreator 2020-07-27T17:29:32
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = intelligent_community
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        LED.cpp \
        advertisement.cpp \
        business_center.cpp \
        caular.cpp \
        character_calc_mainwindow.cpp \
        community_service.cpp \
        edit_table_model.cpp \
        for_business.cpp \
        keybutton.cpp \
        leisure.cpp \
        login.cpp \
        main.cpp \
        intelligent_community.cpp \
        mange_business.cpp \
        mange_owner.cpp \
        mylabel.cpp \
        new_owner.cpp \
        news.cpp \
        nodepad.cpp \
        photoview.cpp \
        result_mainwindow.cpp \
        runningtime.cpp \
        selfinfo.cpp \
        softkey.cpp \
        v4l2.cpp \
        videodisplay.cpp \
        weatherinfo.cpp

HEADERS += \
        LED.h \
        advertisement.h \
        business_center.h \
        caular.h \
        character_calc_mainwindow.h \
        community_service.h \
        connect_database.h \
        countdata.h \
        database_table.h \
        edit_table_model.h \
        for_business.h \
        intelligent_community.h \
        keybutton.h \
        leisure.h \
        login.h \
        mange_business.h \
        mange_owner.h \
        mylabel.h \
        new_owner.h \
        news.h \
        nodepad.h \
        photoview.h \
        result_mainwindow.h \
        runningtime.h \
        selfinfo.h \
        softkey.h \
        v4l2.h \
        videodisplay.h \
        weatherinfo.h

FORMS += \
        LED.ui \
        advertisement.ui \
        business_center.ui \
        caular.ui \
        character_calc_mainwindow.ui \
        community_service.ui \
        for_business.ui \
        intelligent_community.ui \
        leisure.ui \
        login.ui \
        mange_business.ui \
        mange_owner.ui \
        new_owner.ui \
        news.ui \
        nodepad.ui \
        photoview.ui \
        result_mainwindow.ui \
        runningtime.ui \
        selfinfo.ui \
        softkey.ui \
        videodisplay.ui \
        weatherinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
