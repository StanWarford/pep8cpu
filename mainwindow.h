#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "byteconverterdec.h"
#include "byteconverterhex.h"
#include "byteconverterbin.h"
#include "byteconverterchar.h"

#include "microcode.h"
#include "pep.h"
#include "sim.h"
#include "mainmemory.h"
#include "cpupane.h"
#include "helpdialog.h"

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

private:
    Ui::MainWindow *ui;

    // Byte converter
    ByteConverterDec *byteConverterDec;
    ByteConverterHex *byteConverterHex;
    ByteConverterBin *byteConverterBin;
    ByteConverterChar *byteConverterChar;

    // Main Memory
    MainMemory *mainMemory;
    CpuPane *cpuPane;
    Microcode *microcode;

    HelpDialog *helpDialog;

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
    void on_actionEdit_Font_triggered();
    // System
    void on_actionSystem_Clear_CPU_triggered();
    void on_actionSystem_Clear_Memory_triggered();
    // Help
    void on_actionHelp_triggered();

    // Byte converter
    void slotByteConverterDecEdited(const QString &);
    void slotByteConverterHexEdited(const QString &);
    void slotByteConverterBinEdited(const QString &);
    void slotByteConverterCharEdited(const QString &);

    // Focus coloring Undo/Redo/Cut/Copy/Paste activate/deactivate
    void mainWindowUtilities(QWidget *, QWidget *);
    void setUndoability(bool b);
    void setRedoability(bool b);

    void helpCopyToMicrocodeButtonClicked();
};

#endif // MAINWINDOW_H
