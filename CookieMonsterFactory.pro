QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    factory_structs/BandasTransportadoras.cpp \
    factory_structs/Cookie.cpp \
    factory_structs/CookiePack.cpp \
    factory_structs/DeliveryCar.cpp \
    factory_structs/Inspectores.cpp \
    factory_structs/PlannerPacks.cpp \
    factory_structs/Transportador.cpp \
    factory_structs/Transportadores.cpp \
    lists/CircularList.cpp \
    lists/LinkedList.cpp \
    lists/Queue.cpp \
    lists/node.cpp \
    machines/Planner.cpp \
    machines/Warehouse.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    factory_structs/BandasTransportadoras.h \
    factory_structs/Cookie.h \
    factory_structs/CookiePack.h \
    factory_structs/DeliveryCar.h \
    factory_structs/Inspectores.h \
    factory_structs/PlannerPacks.h \
    factory_structs/Transportador.h \
    factory_structs/Transportadores.h \
    lists/CircularList.h \
    lists/LinkedList.h \
    lists/Queue.h \
    lists/node.h \
    machines/Planner.h \
    machines/Warehouse.h \
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
