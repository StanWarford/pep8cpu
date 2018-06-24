// File: mainwindow.h
/*
    Pep8CPU is a CPU simulator for executing microcode sequences to
    implement instructions in the instruction set of the Pep/8 computer.

    Copyright (C) 2010  J. Stanley Warford, Pepperdine University

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "byteconverterdec.h"
#include "byteconverterhex.h"
#include "byteconverterbin.h"
#include "byteconverterchar.h"

#include "cpupane.h"
#include "mainmemory.h"
#include "microcodepane.h"
#include "objectcodepane.h"
#include "pep.h"
#include "sim.h"
#include "helpdialog.h"
#include "aboutpep.h"

#include <QDir>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::MainWindow *ui;
    QFont codeFont;
    // Byte converter
    ByteConverterDec *byteConverterDec;
    ByteConverterHex *byteConverterHex;
    ByteConverterBin *byteConverterBin;
    ByteConverterChar *byteConverterChar;

    // Main Memory
    MainMemory *mainMemory;
    CpuPane *cpuPane;
    MicrocodePane *microcodePane;
    ObjectCodePane *objectCodePane;

    HelpDialog *helpDialog;
    AboutPep *aboutPepDialog;

    void readSettings();
    void writeSettings();

    // Save methods
    bool save();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    QString curPath;

private slots:

    // File
    void on_actionFile_New_triggered();
    void on_actionFile_Open_triggered();
    bool on_actionFile_Save_triggered();
    bool on_actionFile_Save_As_triggered();
    // Edit
    void on_actionEdit_Undo_triggered();
    void on_actionEdit_Redo_triggered();
    void on_actionEdit_Cut_triggered();
    void on_actionEdit_Copy_triggered();
    void on_actionEdit_Paste_triggered();
    void on_actionEdit_UnComment_Line_triggered();
    void on_actionEdit_Format_From_Object_Code_triggered();
    void on_actionEdit_Remove_Error_Messages_triggered();
    void on_actionEdit_Font_triggered();
    void on_actionReset_Fonts_to_Defaults_triggered();
    // System
    void on_actionSystem_Run_triggered();
    bool on_actionSystem_Start_Debugging_triggered();
    void on_actionSystem_Stop_Debugging_triggered();
    void on_actionSystem_Clear_CPU_triggered();
    void on_actionSystem_Clear_Memory_triggered();
    // Help
    void on_actionHelp_UsingPep8CPU_triggered();
    void on_actionHelp_InteractiveUse_triggered();
    void on_actionHelp_MicrocodeUse_triggered();
    void on_actionHelp_DebuggingUse_triggered();
    void on_actionHelp_Pep8Reference_triggered();
    void on_actionHelp_Examples_triggered();
    void on_actionHelp_triggered();
    void on_actionHelp_About_Pep8CPU_triggered();
    void on_actionHelp_About_Qt_triggered();

    // Byte converter
    void slotByteConverterDecEdited(const QString &);
    void slotByteConverterHexEdited(const QString &);
    void slotByteConverterBinEdited(const QString &);
    void slotByteConverterCharEdited(const QString &);

    // Focus coloring Undo/Redo/Cut/Copy/Paste activate/deactivate
    void focusChanged(QWidget *, QWidget *);
    void setUndoability(bool b);
    void setRedoability(bool b);

    void updateSimulation();
    void stopSimulation();
    void simulationFinished();
    void appendMicrocodeLine(QString string);

    void helpCopyToMicrocodeButtonClicked();

    void updateMemAddress(int address);
signals:
    void fontChanged(QFont font);
};

#endif // MAINWINDOW_H
