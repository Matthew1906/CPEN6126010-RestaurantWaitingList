QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcustomerdialog.cpp \
    filltabledialog.cpp \
    main.cpp \
    mainwindow.cpp \
    tablehistorydialog.cpp

HEADERS += \
    addcustomerdialog.h \
    customer.h \
    filltabledialog.h \
    mainwindow.h \
    tablehistorydialog.h

FORMS += \
    addcustomerdialog.ui \
    filltabledialog.ui \
    mainwindow.ui \
    tablehistorydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    tableListResources.qrc
