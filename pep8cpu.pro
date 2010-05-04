# -------------------------------------------------
# Project created by QtCreator 2009-12-01T13:18:25
# -------------------------------------------------
TARGET = pep8cpu
TEMPLATE = app
CONFIG += x86 \
    ppc
QT += webkit
CONFIG += x86 \
    ppc

# Mac icon/plist
ICON = images/icon.icns
QMAKE_INFO_PLIST = app.plist
SOURCES += main.cpp \
    mainwindow.cpp \
    byteconverterhex.cpp \
    byteconverterdec.cpp \
    byteconverterchar.cpp \
    byteconverterbin.cpp \
    mainmemory.cpp \
    sim.cpp \
    pep.cpp \
    microcodepane.cpp \
    cpupane.cpp \
    helpdialog.cpp \
    pephighlighter.cpp \
    microcodeeditor.cpp \
    memoryitemdelegate.cpp \
    objectcodepane.cpp \
    cpupanegraphicsitems.cpp \
    code.cpp \
    asm.cpp \
    tristatelabel.cpp \
    objectcodelabel.cpp
HEADERS += mainwindow.h \
    byteconverterhex.h \
    byteconverterdec.h \
    byteconverterchar.h \
    byteconverterbin.h \
    mainmemory.h \
    sim.h \
    pep.h \
    microcodepane.h \
    cpupane.h \
    helpdialog.h \
    pephighlighter.h \
    enu.h \
    microcodeeditor.h \
    memoryitemdelegate.h \
    objectcodepane.h \
    cpupanegraphicsitems.h \
    code.h \
    asm.h \
    tristatelabel.h \
    objectcodelabel.h
FORMS += mainwindow.ui \
    byteconverterhex.ui \
    byteconverterdec.ui \
    byteconverterchar.ui \
    byteconverterbin.ui \
    mainmemory.ui \
    microcodepane.ui \
    cpupane.ui \
    helpdialog.ui \
    objectcodepane.ui
OTHER_FILES += help/images/registeraddresssignals.png
RESOURCES += pep8cpuresources.qrc \
    helpresources.qrc
