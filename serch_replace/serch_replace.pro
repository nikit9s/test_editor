TEMPLATE = app

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD\..\qscintilla\src
CONFIG(debug, debug|release) {
    LIBS += $$PWD\..\..\find_window_out\qscintilla2_qt5d.dll
    PRE_TARGETDEPS += $$PWD\..\..\find_window_out\qscintilla2_qt5d.dll

} else {
    LIBS += $$PWD\..\..\find_window_out\qscintilla2_qt5.dll
    PRE_TARGETDEPS += $$PWD\..\..\find_window_out\qscintilla2_qt5.dll

}

TEMPLATE = app


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    find_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    scintilla.cpp \
    styledeligate.cpp \
    worker.cpp

HEADERS += \
    find_dialog.h \
    mainwindow.h \
    scintilla.h \
    worker.h


# Default rules for deployment.
FORMS += \
    find_dialog.ui \
#    help_window.ui \
#    mainwindow.ui

UI_DIR += $$PWD

DESTDIR = $$PWD\..\..\find_window_out

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
