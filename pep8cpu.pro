# -------------------------------------------------
# Project created by QtCreator 2009-12-01T13:18:25
# -------------------------------------------------
TARGET = pep8cpu
TEMPLATE = app
QT += webkit
SOURCES += main.cpp \
    mainwindow.cpp \
    byteconverterhex.cpp \
    byteconverterdec.cpp \
    byteconverterchar.cpp \
    byteconverterbin.cpp \
    mainmemory.cpp \
    sim.cpp \
    pep.cpp \
    microcode.cpp \
    cpupane.cpp \
    helpdialog.cpp \
    pephighlighter.cpp
HEADERS += mainwindow.h \
    byteconverterhex.h \
    byteconverterdec.h \
    byteconverterchar.h \
    byteconverterbin.h \
    mainmemory.h \
    sim.h \
    pep.h \
    microcode.h \
    cpupane.h \
    helpdialog.h \
    pephighlighter.h \
    enu.h
FORMS += mainwindow.ui \
    byteconverterhex.ui \
    byteconverterdec.ui \
    byteconverterchar.ui \
    byteconverterbin.ui \
    mainmemory.ui \
    microcode.ui \
    cpupane.ui \
    helpdialog.ui
OTHER_FILES += help/images/registeraddresssignals.png
RESOURCES += pep8cpuresources.qrc \
    helpresources.qrc
