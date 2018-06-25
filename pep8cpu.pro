# -------------------------------------------------
# Project created by QtCreator 2009-12-01T13:18:25
# -------------------------------------------------
TEMPLATE = app
TARGET = Pep8CPU

QT += webenginewidgets
QT += widgets
QT += printsupport

# Mac icon/plist
ICON = images/icon.icns
QMAKE_INFO_PLIST = app.plist

#Windows RC file for icon:
RC_FILE = pep8resources.rc

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
    objectcodelabel.cpp \
    specification.cpp \
    byteconverterinstr.cpp \
    aboutpep.cpp
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
    objectcodelabel.h \
    specification.h \
    byteconverterinstr.h \
    aboutpep.h
FORMS += mainwindow.ui \
    byteconverterhex.ui \
    byteconverterdec.ui \
    byteconverterchar.ui \
    byteconverterbin.ui \
    mainmemory.ui \
    microcodepane.ui \
    cpupane.ui \
    helpdialog.ui \
    objectcodepane.ui \
    byteconverterinstr.ui \
    aboutpep.ui
OTHER_FILES += help/images/registeraddresssignals.png \
    help/figures/exer1204.pepcpu \
    help/figures/exer1206.pepcpu \
    images/Pep8cpu-icon.png \
    images/Pep8cpu-icon-about.png \
    help/usingpep8cpu.html \
    help/pep8reference.html \
    help/pep8os.txt \
    help/microcode.html \
    help/exercises.html \
    help/examples.html \
    help/debugging.html \
    help/cpu.html
RESOURCES += pep8cpuresources.qrc \
    helpresources.qrc

DISTFILES += \
    ProjectDefs.pri \
    Installer/config/control.js \
    Installer/packages/pep8cpu/installscript.js \
    Installer/InstallerConfig.pri \
    Installer/config/configlinux.xml \
    Installer/config/configwin32.xml \
    Installer/packages/pep8cpu/package.xml \
    Installer/packages/pep8cpu/License.txt

#Add this include to the bottom of your project to enable automated installer creation
#Include the definitions file that sets all variables needed for the InstallerConfig Script
include("ProjectDefs.pri")

#Lastly, include and run the installer config script
include("Installer/InstallerConfig.pri")
