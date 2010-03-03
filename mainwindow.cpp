#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDesktopWidget *desktop = QApplication::desktop();
    resize(desktop->width() * 0.8, desktop->height() * 0.8);

    mainMemory = new MainMemory(ui->mainSplitter);
    delete ui->memoryFrame;
    cpuPane = new CpuPane(ui->mainSplitter);
    delete ui->cpuFrame;
    microcode = new Microcode(ui->codeSplitter);
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

    connect(qApp->instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(mainWindowUtilities(QWidget*, QWidget*)));
    connect(microcode, SIGNAL(undoAvailable(bool)), this, SLOT(setUndoability(bool)));
    connect(microcode, SIGNAL(redoAvailable(bool)), this, SLOT(setRedoability(bool)));

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

}

void MainWindow::on_actionEdit_Redo_triggered()
{

}

void MainWindow::on_actionEdit_Cut_triggered()
{

}

void MainWindow::on_actionEdit_Copy_triggered()
{

}

void MainWindow::on_actionEdit_Paste_triggered()
{

}

void MainWindow::on_actionEdit_Font_triggered()
{

}

// System MainWindow triggers
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
void MainWindow::mainWindowUtilities(QWidget *, QWidget *)
{
    microcode->highlightOnFocus();
    mainMemory->highlightOnFocus();
    objectCodePane->highlightOnFocus();
    cpuPane->highlightOnFocus();

    if (microcode->hasFocus()) {

    }
    else if (mainMemory->hasFocus()) {

    }
    else if (cpuPane->hasFocus()) {
//        ui->actionEdit_Undo->setDisabled(true);
//        ui->actionEdit_Redo->setDisabled(true);
//        ui->actionEdit_Cut->setDisabled(true);
//        ui->actionEdit_Copy->setDisabled(false);
//        ui->actionEdit_Paste->setDisabled(true);
    }
}

void MainWindow::setUndoability(bool b)
{
    if (microcode->hasFocus()) {
        ui->actionEdit_Undo->setDisabled(!b);
    }
//    else if (mainMemory->hasFocus()) {
//        ui->actionEdit_Undo->setDisabled(!b);
//    }
//    else if (cpuPane->hasFocus()) {
//        ui->actionEdit_Undo->setDisabled(!b);
//    }
}

void MainWindow::setRedoability(bool b)
{
    if (microcode->hasFocus()) {
        ui->actionEdit_Redo->setDisabled(!b);
    }
//    else if (mainMemory->hasFocus()) {
//        ui->actionEdit_Redo->setDisabled(!b);
//    }
//    else if (cpuPane->hasFocus()) {
//        ui->actionEdit_Redo->setDisabled(!b);
//    }
}

void MainWindow::helpCopyToMicrocodeButtonClicked()
{
    microcode->setMicrocode(helpDialog->getExampleText());
    helpDialog->hide();
}
