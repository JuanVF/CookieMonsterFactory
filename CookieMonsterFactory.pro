QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    factory_structs/Cookie.cpp \
    factory_structs/CookiePack.cpp \
    factory_structs/DeliveryCar.cpp \
    lists/CircularList.cpp \
    lists/LinkedList.cpp \
    lists/Queue.cpp \
    lists/node.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    factory_structs/Cookie.h \
    factory_structs/CookiePack.h \
    factory_structs/DeliveryCar.h \
    lists/CircularList.h \
    lists/LinkedList.h \
    lists/Queue.h \
    lists/node.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md
