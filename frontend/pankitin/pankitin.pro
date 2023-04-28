QT       += core gui
QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    dialogcardpayment.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    databasemanager.h \
    dialogcardpayment.h \
    mainwindow.h \

FORMS += \
    dialogcardpayment.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../dll_files/ -lcardReaderDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../dll_files/ -lcardReaderDLL
else:unix: LIBS += -L$$PWD/../dll_files/ -lcardReaderDLL

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../dll_files/ -lpankitinDLL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../dll_files/ -lpankitinDLL
else:unix: LIBS += -L$$PWD/../dll_files/ -lpankitinDLL

INCLUDEPATH += $$PWD/../dll_files
DEPENDPATH += $$PWD/../dll_files

DISTFILES +=


