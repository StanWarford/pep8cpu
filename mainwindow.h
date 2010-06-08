#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    MicrocodePane *microcodePane;
    ObjectCodePane *objectCodePane;

    HelpDialog *helpDialog;

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
    void on_actionEdit_Format_From_Object_Code_triggered();
    void on_actionEdit_Remove_Error_Messages_triggered();
    void on_actionEdit_Font_triggered();
    // System
    void on_actionSystem_Run_triggered();
    void on_actionSystem_Start_Debugging_triggered();
    void on_actionSystem_Stop_Debugging_triggered();
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
    void focusChanged(QWidget *, QWidget *);
    void setUndoability(bool b);
    void setRedoability(bool b);

    void updateSimulation();
    void simulationFinished();
    void appendMicrocodeLine(QString string);

    void helpCopyToMicrocodeButtonClicked();

    void updateMemAddress(int address);
};

#endif // MAINWINDOW_H
