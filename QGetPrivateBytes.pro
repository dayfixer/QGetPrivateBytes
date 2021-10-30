QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logobject.cpp \
    main.cpp \
    mainwindow.cpp \
    plotobject.cpp \
    qcustomplot.cpp

HEADERS += \
    global.h \
    logobject.h \
    mainwindow.h \
    plotobject.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS    +=  QGetPrivateByte_Zh_cn.ts

CONFIG(release, debug|release){
    MOC_DIR = bin/release/moc
	RCC_DIR = bin/release/rcc
	UI_DIR = bin/release/ui
	OBJECTS_DIR = bin/release/obj
} else {
    MOC_DIR = bin/debug/moc
	RCC_DIR = bin/debug/rcc
	UI_DIR = bin/debug/ui
	OBJECTS_DIR = bin/debug/obj
}
