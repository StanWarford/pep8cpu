#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(1164, 800);

    mainMemory = new MainMemory(ui->mainSplitter);
    delete ui->memoryFrame;
    cpuPane = new CpuPane(ui->mainSplitter);
    delete ui->cpuFrame;
    microcodePane = new MicrocodePane(ui->codeSplitter);
    delete ui->microcodeFrame;
    objectCodePane = new ObjectCodePane(ui->codeSplitter);
    delete ui->objectCodeFrame;

    ui->mainSplitter->insertWidget(0, mainMemory);
    ui->mainSplitter->insertWidget(1, cpuPane);

    helpDialog = new HelpDialog(this);

    // Byte converter setup
    byteConverterDec = new ByteConverterDec();
    ui->byteConverterToolBar->addWidget(byteConverterDec);
    byteConverterHex = new ByteConverterHex();
    ui->byteConverterToolBar->addWidget(byteConverterHex);
    byteConverterBin = new ByteConverterBin();
    ui->byteConverterToolBar->addWidget(byteConverterBin);
    byteConverterChar = new ByteConverterChar();
    ui->byteConverterToolBar->addWidget(byteConverterChar);
    connect(byteConverterDec, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterDecEdited(const QString &)));
    connect(byteConverterHex, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterHexEdited(const QString &)));
    connect(byteConverterBin, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterBinEdited(const QString &)));
    connect(byteConverterChar, SIGNAL(textEdited(const QString &)), this, SLOT(slotByteConverterCharEdited(const QString &)));

    connect(helpDialog, SIGNAL(clicked()), this, SLOT(helpCopyToMicrocodeButtonClicked()));

    connect(qApp->instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(focusChanged(QWidget*, QWidget*)));
    connect(microcodePane, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(microcodePane, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));

    connect(cpuPane, SIGNAL(updateSimulation()), this, SLOT(updateSimulation()));
    connect(cpuPane, SIGNAL(simulationFinished()), this, SLOT(simulationFinished()));

    Pep::initEnumMnemonMaps();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// File MainWindow triggers
void MainWindow::on_actionFile_New_triggered()
{

}

void MainWindow::on_actionFile_Open_triggered()
{

}

bool MainWindow::on_actionFile_Save_triggered()
{
    return true;
}

bool MainWindow::on_actionFile_Save_As_triggered()
{
    return true;
}

// Edit MainWindow triggers
void MainWindow::on_actionEdit_Undo_triggered()
{
    if (microcodePane->hasFocus()) {
        microcodePane->undo();
    }
    // other panes should not be able to undo
}

void MainWindow::on_actionEdit_Redo_triggered()
{
    if (microcodePane->hasFocus()) {
        microcodePane->redo();
    }
    // other panes should not be able to redo
}

void MainWindow::on_actionEdit_Cut_triggered()
{
    if (microcodePane->hasFocus()) {
        microcodePane->cut();
    }
    // other panes should not be able to cut
}

void MainWindow::on_actionEdit_Copy_triggered()
{
    if (microcodePane->hasFocus()) {
        microcodePane->copy();
    }
    else if (objectCodePane->hasFocus()) {
        objectCodePane->copy();
    }
    // other panes should not be able to copy
}

void MainWindow::on_actionEdit_Paste_triggered()
{
    if (microcodePane->hasFocus()) {
        microcodePane->paste();
    }
    // other panes should not be able to paste
}

void MainWindow::on_actionEdit_Remove_Error_Messages_triggered()
{
    microcodePane->removeErrorMessages();
}

void MainWindow::on_actionEdit_Font_triggered()
{

}

// System MainWindow triggers
void MainWindow::on_actionSystem_Microassemble_triggered()
{
    if (microcodePane->microAssemble()) {
        ui->statusBar->showMessage("MicroAssembly succeeded", 4000);
        objectCodePane->setObjectCode(microcodePane->codeToString());
    }
    else {
        ui->statusBar->showMessage("MicroAssembly failed", 4000);
    }
}

void MainWindow::on_actionSystem_Execute_triggered()
{

}

void MainWindow::on_actionSystem_Run_triggered()
{

}

void MainWindow::on_actionSystem_Start_Debugging_triggered()
{
    // enable the actions available while we're debugging
    ui->actionSystem_Stop_Debugging->setEnabled(true);

    // disable actions related to editing/starting debugging
    ui->actionSystem_Run->setEnabled(false);
    ui->actionSystem_Execute->setEnabled(false);
    ui->actionSystem_Microassemble->setEnabled(false);
    ui->actionSystem_Start_Debugging->setEnabled(false);
    microcodePane->setReadOnly(true);
    cpuPane->startDebugging();
}

void MainWindow::on_actionSystem_Stop_Debugging_triggered()
{
    // disable the actions available while we're debugging
    ui->actionSystem_Stop_Debugging->setEnabled(false);

    // enable actions related to editing/starting debugging
    ui->actionSystem_Run->setEnabled(true);
    ui->actionSystem_Execute->setEnabled(true);
    ui->actionSystem_Microassemble->setEnabled(true);
    ui->actionSystem_Start_Debugging->setEnabled(true);
    microcodePane->setReadOnly(false);
    cpuPane->stopDebugging();
}

void MainWindow::on_actionSystem_Clear_CPU_triggered()
{

}

void MainWindow::on_actionSystem_Clear_Memory_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{
    helpDialog->show();
}

// Byte Converter slots
void MainWindow::slotByteConverterDecEdited(const QString &str)
{
    if (str.length() > 0) {
        bool ok;
        int data = str.toInt(&ok, 10);
        byteConverterHex->setValue(data);
        byteConverterBin->setValue(data);
        byteConverterChar->setValue(data);
    }
}

void MainWindow::slotByteConverterHexEdited(const QString &str)
{
    if (str.length() >= 2) {
        if (str.startsWith("0x")) {
            QString hexPart = str;
            hexPart.remove(0, 2);
            if (hexPart.length() > 0) {
                bool ok;
                int data = hexPart.toInt(&ok, 16);
                byteConverterDec->setValue(data);
                byteConverterBin->setValue(data);
                byteConverterChar->setValue(data);
            }
            else {
                // Exactly "0x" remains, so do nothing
            }
        }
        else {
            // Prefix "0x" was mangled
            byteConverterHex->setValue(-1);
        }
    }
    else {
        // Prefix "0x" was shortened
        byteConverterHex->setValue(-1);
    }
}

void MainWindow::slotByteConverterBinEdited(const QString &str)
{
    if (str.length() > 0) {
        bool ok;
        int data = str.toInt(&ok, 2);
        byteConverterDec->setValue(data);
        byteConverterHex->setValue(data);
        byteConverterChar->setValue(data);
    }
}

void MainWindow::slotByteConverterCharEdited(const QString &str)
{
    if (str.length() > 0) {
        int data = (int)str[0].toLatin1();
        byteConverterDec->setValue(data);
        byteConverterHex->setValue(data);
        byteConverterBin->setValue(data);
    }
}

// Focus Coloring. Activates and deactivates undo/redo/cut/copy/paste actions contextually
void MainWindow::focusChanged(QWidget *, QWidget *)
{
    microcodePane->highlightOnFocus();
    mainMemory->highlightOnFocus();
    objectCodePane->highlightOnFocus();
    cpuPane->highlightOnFocus();

    if (microcodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!microcodePane->isUndoable());
        ui->actionEdit_Redo->setDisabled(!microcodePane->isRedoable());
        ui->actionEdit_Cut->setDisabled(false);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(false);
    }
    else if (mainMemory->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(true);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (cpuPane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(true);
        ui->actionEdit_Paste->setDisabled(true);
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(true);
        ui->actionEdit_Redo->setDisabled(true);
        ui->actionEdit_Cut->setDisabled(true);
        ui->actionEdit_Copy->setDisabled(false);
        ui->actionEdit_Paste->setDisabled(true);
    }
}

void MainWindow::setUndoability(bool b)
{
    if (microcodePane->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
    else if (mainMemory->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
    else if (cpuPane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
}

void MainWindow::setRedoability(bool b)
{
    if (microcodePane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
    else if (mainMemory->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
    else if (cpuPane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
    else if (objectCodePane->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(true);
    }
}

void MainWindow::updateSimulation()
{
    microcodePane->updateSimulationView();
    objectCodePane->highlightCurrentInstruction();
}

void MainWindow::simulationFinished()
{
    microcodePane->clearSimulationView();
    objectCodePane->clearSimulationView();
    on_actionSystem_Stop_Debugging_triggered();
}

void MainWindow::helpCopyToMicrocodeButtonClicked()
{
    microcodePane->setMicrocode(helpDialog->getExampleText());
    objectCodePane->setObjectCode("");
    helpDialog->hide();
}

