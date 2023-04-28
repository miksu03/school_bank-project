QT -= gui
QT += network
DESTDIR = $$PWD/../dll_files
#QMAKE_POST_LINK += $$quote(copy /Y $${TARGET}*.dll $$DESTDIR)
TEMPLATE = lib
DEFINES += PANKITINDLL_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    card.cpp \
    customers.cpp \
    databaseurl.cpp \
    events.cpp

HEADERS += \
    account.h \
    card.h \
    customers.h \
    databaseurl.h \
    events.h \
    pankitinDLL_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
