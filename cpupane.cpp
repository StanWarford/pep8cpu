#include "cpupane.h"
#include "ui_cpupane.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QErrorMessage>

#include <QDebug>

#include "cpupanegraphicsitems.h"
#include "tristatelabel.h"
#include "pep.h"
#include "code.h"
#include "sim.h"

using namespace Enu;

CpuPane::CpuPane(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::CpuPane)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomFactorChanged(int)));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setFont(QFont(Pep::cpuFont, Pep::cpuFontSize));

    cpuPaneItems = new CpuPaneGraphicsItems(ui->graphicsView, 0, scene);

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(cpuPaneItems->loadCk, SIGNAL(clicked()), scene, SLOT(invalidate()));
    connect(cpuPaneItems->cLineEdit, SIGNAL(textChanged(QString)), scene, SLOT(invalidate()));
    connect(cpuPaneItems->bLineEdit, SIGNAL(textChanged(QString)), scene, SLOT(invalidate()));
    connect(cpuPaneItems->aLineEdit, SIGNAL(textChanged(QString)), scene, SLOT(invalidate()));
    connect(cpuPaneItems->MARCk, SIGNAL(clicked()), scene, SLOT(invalidate()));
    connect(cpuPaneItems->MDRCk, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->aMuxTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->aMuxTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->MDRMuxTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->MDRMuxTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->cMuxTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->cMuxTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->ALULineEdit, SIGNAL(textChanged(QString)), scene, SLOT(invalidate()));

    connect(cpuPaneItems->CCkCheckBox, SIGNAL(clicked()), scene, SLOT(invalidate()));
    connect(cpuPaneItems->VCkCheckBox, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->ANDZTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->ANDZTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->ZCkCheckBox, SIGNAL(clicked()), scene, SLOT(invalidate()));
    connect(cpuPaneItems->NCkCheckBox, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->MemReadTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->MemReadTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));
    connect(cpuPaneItems->MemWriteTristateLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->MemWriteTristateLabel, SIGNAL(clicked()), scene, SLOT(invalidate()));

    connect(cpuPaneItems->nBitLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->zBitLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->vBitLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(cpuPaneItems->cBitLabel, SIGNAL(clicked()), this, SLOT(labelClicked()));

    // Simulation control connections
    connect(ui->clockPushButton, SIGNAL(clicked()), this, SLOT(clockButtonPushed()));
    connect(ui->singleStepPushButton, SIGNAL(clicked()), this, SLOT(singleStepButtonPushed()));
    connect(ui->resumePushButton, SIGNAL(clicked()), this, SLOT(resumeButtonPushed()));

    // Register editing connnections
    connect(cpuPaneItems->aRegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->xRegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->spRegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->pcRegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->irRegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t1RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t2RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t3RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t4RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t5RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));
    connect(cpuPaneItems->t6RegLineEdit, SIGNAL(textEdited(QString)), this, SLOT(regTextEdited(QString)));

    connect(cpuPaneItems->ALULineEdit, SIGNAL(textChanged(QString)), this, SLOT(ALUTextEdited(QString)));

    ui->spinBox->hide();
    ui->singleStepPushButton->setEnabled(false);
}

CpuPane::~CpuPane()
{
    delete ui;
}

void CpuPane::highlightOnFocus()
{
    if (ui->graphicsView->hasFocus() || ui->spinBox->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

bool CpuPane::hasFocus()
{
    return ui->graphicsView->hasFocus() || ui->spinBox->hasFocus();
}

void CpuPane::startDebugging()
{
    ui->resumePushButton->setEnabled(true);
    ui->singleStepPushButton->setEnabled(true);

    ui->clockPushButton->setEnabled(false);
    ui->copyToMicrocodePushButton->setEnabled(false);

    Sim::microProgramCounter = 0;
    Sim::microCodeCurrentLine = 0;
    Code *code = Sim::codeList.at(Sim::microCodeCurrentLine);
    while (!Sim::atEndOfSim() && !code->isMicrocode()) {
        Sim::microCodeCurrentLine++;
        code = Sim::codeList.at(Sim::microCodeCurrentLine);
    }
    code->setCpuLabels(cpuPaneItems);
    emit updateSimulation();
    Sim::microProgramCounter++;
    Sim::microCodeCurrentLine++;
}

void CpuPane::stopDebugging()
{
    ui->resumePushButton->setEnabled(false);
    ui->singleStepPushButton->setEnabled(false);

    ui->clockPushButton->setEnabled(true);
    ui->copyToMicrocodePushButton->setEnabled(true);
}

void CpuPane::setRegister(Enu::EMnemonic reg, int value) {
    switch (reg) {
    case Enu::A:
        Sim::aReg = value;
        cpuPaneItems->aRegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::X:
        Sim::xReg = value;
        cpuPaneItems->xRegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::SP:
        Sim::spReg = value;
        cpuPaneItems->spRegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::PC:
        Sim::pcReg = value;
        cpuPaneItems->pcRegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::IR:
        Sim::irReg = value;
        cpuPaneItems->irRegLineEdit->setText(QString("0x%1").arg(value, 6, 16, QLatin1Char('0')));
        break;
    case Enu::T1:
        Sim::t1Reg = value;
        cpuPaneItems->t1RegLineEdit->setText(QString("0x%1").arg(value, 2, 16, QLatin1Char('0')));
        break;
    case Enu::T2:
        Sim::t2Reg = value;
        cpuPaneItems->t2RegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::T3:
        Sim::t3Reg = value;
        cpuPaneItems->t3RegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::T4:
        Sim::t4Reg = value;
        cpuPaneItems->t4RegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::T5:
        Sim::t5Reg = value;
        cpuPaneItems->t5RegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::T6:
        Sim::t6Reg = value;
        cpuPaneItems->t6RegLineEdit->setText(QString("0x%1").arg(value, 4, 16, QLatin1Char('0')));
        break;
    case Enu::MARA:
        Sim::MARA = value;
        cpuPaneItems->MARALabel->setText(QString("0x%1").arg(value, 2, 16, QLatin1Char('0')));
        break;
    case Enu::MARB:
        Sim::MARB = value;
        cpuPaneItems->MARBLabel->setText(QString("0x%1").arg(value, 2, 16, QLatin1Char('0')));
        break;
    case Enu::MDR:
        Sim::MDR = value;
        cpuPaneItems->MDRLabel->setText(QString("0x%1").arg(value, 2, 16, QLatin1Char('0')));
        break;
    default:
        break;
    }
}

void CpuPane::setStatusBit(Enu::EMnemonic bit, bool value)
{
    switch (bit) {
    case Enu::N:
        Sim::nBit = value;
        cpuPaneItems->nBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::Z:
        Sim::zBit = value;
        cpuPaneItems->zBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::V:
        Sim::vBit = value;
        cpuPaneItems->vBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::C:
        Sim::cBit = value;
        cpuPaneItems->cBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    default:
        break;
    }
}

void CpuPane::setRegPrecondition(Enu::EMnemonic reg, int value)
{
    setRegister(reg, value);
}

void CpuPane::setStatusPrecondition(Enu::EMnemonic bit, bool value)
{
    setStatusBit(bit, value);
}

bool CpuPane::testRegPostcondition(Enu::EMnemonic reg, int value) {
    (void)value;
    switch (reg) {
    case Enu::A:
        return Sim::aReg == value;
    case Enu::X:
        return Sim::xReg == value;
    case Enu::SP:
        return Sim::spReg == value;
    case Enu::PC:
        return Sim::pcReg == value;
    case Enu::IR:
        return Sim::irReg == value;
    case Enu::T1:
        return Sim::t1Reg == value;
    case Enu::T2:
        return Sim::t2Reg == value;
    case Enu::T3:
        return Sim::t3Reg == value;
    case Enu::T4:
        return Sim::t4Reg == value;
    case Enu::T5:
        return Sim::t5Reg == value;
    case Enu::T6:
        return Sim::t6Reg == value;
    case Enu::MARA:
        return Sim::MARA == value;
    case Enu::MARB:
        return Sim::MARB == value;
    case Enu::MDR:
        return Sim::MDR == value;
    default:
        break;
    }

    return true;
}

bool CpuPane::testStatusPostcondition(Enu::EMnemonic bit, bool value) {
    switch (bit) {
    case Enu::N:
        return Sim::nBit == value;
    case Enu::Z:
        return Sim::zBit == value;
    case Enu::V:
        return Sim::vBit == value;
    case Enu::C:
        return Sim::cBit == value;
    default:
        break;
    }

    return true;
}

void CpuPane::clearCpu()
{
    cpuPaneItems->loadCk->setChecked(false);
    cpuPaneItems->cLineEdit->setText("");
    cpuPaneItems->bLineEdit->setText("");
    cpuPaneItems->aLineEdit->setText("");
    cpuPaneItems->MARCk->setChecked(false);
    cpuPaneItems->MDRCk->setChecked(false);
    cpuPaneItems->aMuxTristateLabel->setText("");
    cpuPaneItems->MDRMuxTristateLabel->setText("");
    cpuPaneItems->cMuxTristateLabel->setText("");
    cpuPaneItems->ALULineEdit->setText("");
    cpuPaneItems->CCkCheckBox->setChecked(false);
    cpuPaneItems->VCkCheckBox->setChecked(false);
    cpuPaneItems->ANDZTristateLabel->setText("");
    cpuPaneItems->ZCkCheckBox->setChecked(false);
    cpuPaneItems->NCkCheckBox->setChecked(false);
    cpuPaneItems->MemReadTristateLabel->setText("");
    cpuPaneItems->MemWriteTristateLabel->setText("");

    setRegister(Enu::A, 0);
    setRegister(Enu::X, 0);
    setRegister(Enu::SP, 0);
    setRegister(Enu::PC, 0);
    setRegister(Enu::IR, 0);
    setRegister(Enu::T1, 0);
    setRegister(Enu::T2, 0);
    setRegister(Enu::T3, 0);
    setRegister(Enu::T4, 0);
    setRegister(Enu::T5, 0);
    setRegister(Enu::T6, 0);

    setRegister(Enu::MARA, 0);
    setRegister(Enu::MARB, 0);
    setRegister(Enu::MDR, 0);

    setStatusBit(Enu::C, false);
    setStatusBit(Enu::V, false);
    setStatusBit(Enu::Z, false);
    setStatusBit(Enu::N, false);
}

void CpuPane::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CpuPane::regTextEdited(QString str)
{
    qDebug() << "str: " << str;
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(sender());

    // Make sure the string isn't mangled
    if (str == "0") {
        str = "0x";
        lineEdit->setText(str);
    }
    else if (!str.startsWith("0x")) {
        str = str.toUpper();
        str.prepend("0x");
        lineEdit->setText(str);
    }
    else {
        str.remove(0, 2);
        str = str.toUpper();
        str.prepend("0x");
        int pos = lineEdit->cursorPosition();
        lineEdit->setText(str);
        lineEdit->setCursorPosition(pos);
    }

    // Get the hex value of the string
    int regValue = 0;
    str.remove(0, 2);
    if (str.length() > 0) {
        bool ok;
        regValue = str.toInt(&ok, 16);
    }
    else {
        // Exactly "0x" remains, so do nothing
        return;
    }

    if (lineEdit == cpuPaneItems->aRegLineEdit) {
        Sim::aReg = regValue;
    }
    else if (lineEdit == cpuPaneItems->xRegLineEdit) {
        Sim::xReg = regValue;
    }
    else if (lineEdit == cpuPaneItems->spRegLineEdit) {
        Sim::spReg = regValue;
    }
    else if (lineEdit == cpuPaneItems->pcRegLineEdit) {
        Sim::pcReg = regValue;
    }
    else if (lineEdit == cpuPaneItems->irRegLineEdit) {
        Sim::irReg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t1RegLineEdit) {
        Sim::t1Reg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t2RegLineEdit) {
        Sim::t2Reg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t3RegLineEdit) {
        Sim::t3Reg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t4RegLineEdit) {
        Sim::t4Reg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t5RegLineEdit) {
        Sim::t5Reg = regValue;
    }
    else if (lineEdit == cpuPaneItems->t6RegLineEdit) {
        Sim::t6Reg = regValue;
    }
}

void CpuPane::zoomFactorChanged(int factor)
{
    QMatrix matrix;
    matrix.scale(factor * .01, factor * .01);
    ui->graphicsView->setMatrix(matrix);
    ui->graphicsView->update();
}

void CpuPane::labelClicked()
{
    TristateLabel *label = qobject_cast<TristateLabel *>(sender());
    label->toggle();

    Sim::nBit = cpuPaneItems->nBitLabel->text().toInt() == 0 ? false : true;
    Sim::zBit = cpuPaneItems->zBitLabel->text().toInt() == 0 ? false : true;
    Sim::vBit = cpuPaneItems->vBitLabel->text().toInt() == 0 ? false : true;
    Sim::cBit = cpuPaneItems->cBitLabel->text().toInt() == 0 ? false : true;
}

void CpuPane::clockButtonPushed()
{
#warning "temp - change later"
    Sim::codeList.clear();
    singleStepButtonPushed();

}

void CpuPane::singleStepButtonPushed()
{
    // Update Bus State
    setMainBusState(); // FSM that sets Sim::mainBusState to Enu::BusState - 5 possible states

    if (Sim::mainBusState == Enu::MemReadReady) { // we are performing a 2nd consecutive MemRead
        bool ok;
        int a = cpuPaneItems->MARALabel->text().remove(0, 2).toInt(&ok, 16) * 256;
        int b = cpuPaneItems->MARBLabel->text().remove(0, 2).toInt(&ok, 16);
        int address = a + b;
        if (cpuPaneItems->MDRMuxTristateLabel->text() == "0" && cpuPaneItems->MDRCk->isChecked()) {
            setRegister(Enu::MDR, Sim::Mem[address]);
            emit readByte(address);
        }
    }
    else if (Sim::mainBusState == Enu::MemWriteReady) { // we are performing a 2nd consecutive MemWrite
        bool ok;
        int a = cpuPaneItems->MARALabel->text().remove(0, 2).toInt(&ok, 16) * 256;
        int b = cpuPaneItems->MARBLabel->text().remove(0, 2).toInt(&ok, 16);
        int address = a + b;
#warning "does the MDR need to be checked to do a memWrite?"
        if (cpuPaneItems->MDRCk->isChecked()) {
            int byteToWrite = cpuPaneItems->MDRLabel->text().remove(0, 2).toInt(&ok, 16);
            Sim::Mem[address] = byteToWrite;
            emit writeByte(address);
        }
    }

    // MARCk
    if (cpuPaneItems->MARCk->isChecked()) {
        if (cpuPaneItems->aLineEdit->text() != "" && cpuPaneItems->bLineEdit->text() != "") {
            setRegister(Enu::MARA, Sim::readRegByte(cpuPaneItems->aLineEdit->text().toInt()));
            setRegister(Enu::MARB, Sim::readRegByte(cpuPaneItems->bLineEdit->text().toInt()));
        }
        else {
            // error: MARCk is checked but we have incorrect input
        }
    }

    // LoadCk
    if (cpuPaneItems->loadCk->isChecked() && cpuPaneItems->cLineEdit->text() != "") {
        int cDest = cpuPaneItems->cLineEdit->text().toInt();
        if (cpuPaneItems->cMuxTristateLabel->text() == "0") {
            int nzvc = (Sim::nBit ? 8 : 0) + (Sim::zBit ? 4 : 0) + (Sim::vBit ? 2 : 0) + (Sim::cBit ? 1 : 0);
            switch(cDest) {
            case 0:
                setRegister(Enu::A, (Sim::aReg & 0x00FF) | nzvc * 256);
                break;
            case 1:
                setRegister(Enu::A, (Sim::aReg & 0xFF00) | nzvc);
                break;
            case 2:
                setRegister(Enu::X, (Sim::xReg & 0x00FF) | nzvc * 256);
                break;
            case 3:
                setRegister(Enu::X, (Sim::xReg & 0xFF00) | nzvc);
                break;
            case 4:
                setRegister(Enu::SP, (Sim::spReg & 0x00FF) | nzvc * 256);
                break;
            case 5:
                setRegister(Enu::SP, (Sim::spReg & 0xFF00) | nzvc);
                break;
            case 6:
                setRegister(Enu::PC, (Sim::pcReg & 0x00FF) | nzvc * 256);
                break;
            case 7:
                setRegister(Enu::PC, (Sim::pcReg & 0xFF00) | nzvc);
                break;
            case 8:
                setRegister(Enu::IR, (Sim::irReg & 0x00FFFF) | nzvc * 65536);
                break;
            case 9:
                setRegister(Enu::IR, (Sim::irReg & 0xFF00FF) | nzvc * 256);
                break;
            case 10:
                setRegister(Enu::IR, (Sim::irReg & 0xFFFF00) | nzvc);
                break;
            case 11:
                setRegister(Enu::T1, nzvc);
                break;
            case 12:
                setRegister(Enu::T2, (Sim::t2Reg & 0x00FF) | nzvc * 256);
                break;
            case 13:
                setRegister(Enu::T2, (Sim::t2Reg & 0xFF00) | nzvc);
                break;
            case 14:
                setRegister(Enu::T3, (Sim::t3Reg & 0x00FF) | nzvc * 256);
                break;
            case 15:
                setRegister(Enu::T3, (Sim::t3Reg & 0xFF00) | nzvc);
                break;
            case 16:
                setRegister(Enu::T4, (Sim::t4Reg & 0x00FF) | nzvc * 256);
                break;
            case 17:
                setRegister(Enu::T4, (Sim::t4Reg & 0xFF00) | nzvc);
                break;
            case 18:
                setRegister(Enu::T5, (Sim::t5Reg & 0x00FF) | nzvc * 256);
                break;
            case 19:
                setRegister(Enu::T5, (Sim::t5Reg & 0xFF00) | nzvc);
                break;
            case 20:
                setRegister(Enu::T6, (Sim::t6Reg & 0x00FF) | nzvc * 256);
                break;
            case 21:
                setRegister(Enu::T6, (Sim::t6Reg & 0xFF00) | nzvc);
            default:
                break;
            }
        }
        else if (cpuPaneItems->cMuxTristateLabel->text() == "1") {
            int aluOut = getALUOutput(); // ALSO sets status bits if the clocks are checked

            if (aluOut != -1) {
                switch(cDest) {
                case 0:
                    setRegister(Enu::A, (Sim::aReg & 0x00FF) | aluOut * 256); // or | aluOut << 8, need to check syntax
                    break;
                case 1:
                    setRegister(Enu::A, (Sim::aReg & 0xFF00) | aluOut);
                    break;
                case 2:
                    setRegister(Enu::X, (Sim::xReg & 0x00FF) | aluOut * 256);
                    break;
                case 3:
                    setRegister(Enu::X, (Sim::xReg & 0xFF00) | aluOut);
                    break;
                case 4:
                    setRegister(Enu::SP, (Sim::spReg & 0x00FF) | aluOut * 256);
                    break;
                case 5:
                    setRegister(Enu::SP, (Sim::spReg & 0xFF00) | aluOut);
                    break;
                case 6:
                    setRegister(Enu::PC, (Sim::pcReg & 0x00FF) | aluOut * 256);
                    break;
                case 7:
                    setRegister(Enu::PC, (Sim::pcReg & 0xFF00) | aluOut);
                    break;
                case 8:
                    setRegister(Enu::IR, (Sim::irReg & 0x00FFFF) | aluOut * 65536);
                    break;
                case 9:
                    setRegister(Enu::IR, (Sim::irReg & 0xFF00FF) | aluOut * 256);
                    break;
                case 10:
                    setRegister(Enu::IR, (Sim::irReg & 0xFFFF00) | aluOut);
                    break;
                case 11:
                    setRegister(Enu::T1, aluOut);
                    break;
                case 12:
                    setRegister(Enu::T2, (Sim::t2Reg & 0x00FF) | aluOut * 256);
                    break;
                case 13:
                    setRegister(Enu::T2, (Sim::t2Reg & 0xFF00) | aluOut);
                    break;
                case 14:
                    setRegister(Enu::T3, (Sim::t3Reg & 0x00FF) | aluOut * 256);
                    break;
                case 15:
                    setRegister(Enu::T3, (Sim::t3Reg & 0xFF00) | aluOut);
                    break;
                case 16:
                    setRegister(Enu::T4, (Sim::t4Reg & 0x00FF) | aluOut * 256);
                    break;
                case 17:
                    setRegister(Enu::T4, (Sim::t4Reg & 0xFF00) | aluOut);
                    break;
                case 18:
                    setRegister(Enu::T5, (Sim::t5Reg & 0x00FF) | aluOut * 256);
                    break;
                case 19:
                    setRegister(Enu::T5, (Sim::t5Reg & 0xFF00) | aluOut);
                    break;
                case 20:
                    setRegister(Enu::T6, (Sim::t6Reg & 0x00FF) | aluOut * 256);
                    break;
                case 21:
                    setRegister(Enu::T6, (Sim::t6Reg & 0xFF00) | aluOut);
                    break;
                default:
                    break;
                }
            }
        }
        else {
            // error: CMux isn't set but we're trying to loadCk
        }
    }

    // MDRCk
    if (cpuPaneItems->MDRCk->isChecked()) {
        if (cpuPaneItems->MDRMuxTristateLabel->text() == "0") { // read from memory
            bool ok = false;
            int mara = cpuPaneItems->MARALabel->text().toInt(&ok, 16);
            int marb = cpuPaneItems->MARBLabel->text().toInt(&ok, 16);
            int address = mara * 256 + marb;
            cpuPaneItems->MDRMuxerDataLabel->setText(QString("0x%1").arg(Sim::Mem[address] % 256, 2, 16, QLatin1Char('0')));
        }
        else if (cpuPaneItems->MDRMuxTristateLabel->text() == "1") { // read through the C bus
            if (cpuPaneItems->cMuxTristateLabel->text() == "0") { // CMux is set to 0, read in NZVC
                int nzvc = (Sim::nBit ? 8 : 0) + (Sim::zBit ? 4 : 0) + (Sim::vBit ? 2 : 0) + (Sim::cBit ? 1 : 0);
//                qDebug() << QString("0x%1").arg(nzvc, 4, 16, QLatin1Char('0'));
                setRegister(Enu::MDR, nzvc);
            }
            else if (cpuPaneItems->cMuxTristateLabel->text() == "1") {
                int aluOut = getALUOutput();

                if (aluOut != -1) {
                    setRegister(Enu::MDR, aluOut);
                }
            }
        }
        else {
            // Error: CMux isn't set but we're trying to MDRCk
        }
    }

    if (cpuPaneItems->ALULineEdit->text() == "15") { // NZVC A alu function
        if (cpuPaneItems->aMuxTristateLabel->text() == "0" || (cpuPaneItems->aMuxTristateLabel->text() == "1" && cpuPaneItems->aLineEdit->text() != "")) {
            getALUOutput();
        }
    }

    Sim::memReadPrevStep = cpuPaneItems->MemReadTristateLabel->text() == "1";
    Sim::memWritePrevStep = cpuPaneItems->MemWriteTristateLabel->text() == "1";

    if (!Sim::atEndOfSim()) {
        Sim::microProgramCounter++;
        Sim::microCodeCurrentLine++;
        Code *code = Sim::codeList.at(Sim::microCodeCurrentLine);
        while (!Sim::atEndOfSim() && !code->isMicrocode()) {
            Sim::microCodeCurrentLine++;
            code = Sim::codeList.at(Sim::microCodeCurrentLine);
        }
        code->setCpuLabels(cpuPaneItems);
    }

    emit updateSimulation();
}

void CpuPane::resumeButtonPushed()
{

}

void CpuPane::on_copyToMicrocodePushButton_clicked()
{
    MicroCode code;
    if (cpuPaneItems->loadCk->isChecked()) {
        code.set(Enu::LoadCk, 1);
    }
    if (cpuPaneItems->cLineEdit->text() != "") {
        code.set(Enu::C, cpuPaneItems->cLineEdit->text().toInt());
    }
    if (cpuPaneItems->bLineEdit->text() != "") {
        code.set(Enu::B, cpuPaneItems->bLineEdit->text().toInt());
    }
    if (cpuPaneItems->aLineEdit->text() != "") {
        code.set(Enu::A, cpuPaneItems->aLineEdit->text().toInt());
    }
    if (cpuPaneItems->MARCk->isChecked()) {
        code.set(Enu::MARCk, 1);
    }
    if (cpuPaneItems->MDRCk->isChecked()) {
        code.set(Enu::MDRCk, 1);
    }
    if (cpuPaneItems->aMuxTristateLabel->text() != "") {
        code.set(Enu::MDRCk, cpuPaneItems->aMuxTristateLabel->text().toInt());
    }
    if (cpuPaneItems->MDRMuxTristateLabel->text() != "") {
        code.set(Enu::MDRCk, cpuPaneItems->MDRMuxTristateLabel->text().toInt());
    }
    if (cpuPaneItems->cMuxTristateLabel->text() != "") {
        code.set(Enu::CMux, cpuPaneItems->cMuxTristateLabel->text().toInt());
    }
    if (cpuPaneItems->ALULineEdit->text() != "") {
        code.set(Enu::ALU, cpuPaneItems->ALULineEdit->text().toInt());
    }
    if (cpuPaneItems->CCkCheckBox->isChecked()) {
        code.set(Enu::CCk, 1);
    }
    if (cpuPaneItems->VCkCheckBox->isChecked()) {
        code.set(Enu::VCk, 1);
    }
    if (cpuPaneItems->ANDZTristateLabel->text() != "") {
        code.set(Enu::CCk, cpuPaneItems->ANDZTristateLabel->text().toInt());
    }
    if (cpuPaneItems->ZCkCheckBox->isChecked()) {
        code.set(Enu::ZCk, 1);
    }
    if (cpuPaneItems->NCkCheckBox->isChecked()) {
        code.set(Enu::NCk, 1);
    }
    if (cpuPaneItems->MemReadTristateLabel->text() != "") {
        code.set(Enu::MemRead, cpuPaneItems->MemReadTristateLabel->text().toInt());
    }
    if (cpuPaneItems->MemWriteTristateLabel->text() != "") {
        code.set(Enu::MemWrite, cpuPaneItems->MemWriteTristateLabel->text().toInt());
    }
    emit appendMicrocodeLine(code.getSourceCode());
}

void CpuPane::ALUTextEdited(QString str)
{
    if (str == "") {
        cpuPaneItems->ALUFunctionLabel->setText("");
    }
    else {
        int num = str.toInt();
        switch (num) {
        case 0:
            cpuPaneItems->ALUFunctionLabel->setText("A");
            break;
        case 1:
            cpuPaneItems->ALUFunctionLabel->setText("A plus B");
            break;
        case 2:
            cpuPaneItems->ALUFunctionLabel->setText("A plus B plus Cin");
            break;
        case 3:
            cpuPaneItems->ALUFunctionLabel->setText("A plus \xAC B plus 1");
            break;
        case 4:
            cpuPaneItems->ALUFunctionLabel->setText("A plus \xAC B plus Cin");
            break;
        case 5:
            cpuPaneItems->ALUFunctionLabel->setText("A \xb7 B");
            break;
        case 6:
            cpuPaneItems->ALUFunctionLabel->setText("\xAC (A \xb7 B)");
            break;
        case 7:
            cpuPaneItems->ALUFunctionLabel->setText("A + B");
            break;
        case 8:
            cpuPaneItems->ALUFunctionLabel->setText("\xAC (A + B)");
            break;
        case 9:
            cpuPaneItems->ALUFunctionLabel->setText("A XOR B");
            break;
        case 10:
            cpuPaneItems->ALUFunctionLabel->setText("\xAC A");
            break;
        case 11:
            cpuPaneItems->ALUFunctionLabel->setText("ASL A");
            break;
        case 12:
            cpuPaneItems->ALUFunctionLabel->setText("ROL A");
            break;
        case 13:
            cpuPaneItems->ALUFunctionLabel->setText("ASR A");
            break;
        case 14:
            cpuPaneItems->ALUFunctionLabel->setText("ROR A");
            break;
        case 15:
            cpuPaneItems->ALUFunctionLabel->setText("NZVC A");
            break;
        default:
            break;
        }
    }
}

void CpuPane::setMainBusState()
{
    int a, b;

    bool marUnchanged = true;
    if (cpuPaneItems->MARCk->isChecked()) {
        if (cpuPaneItems->aLineEdit->text() != "" && cpuPaneItems->bLineEdit->text() != "") {
            a = cpuPaneItems->aLineEdit->text().toInt();
            b = cpuPaneItems->bLineEdit->text().toInt();

            marUnchanged = a == Sim::MARA && b == Sim::MARB;
        }
        else {
            // error: MARCk is checked but we have incorrect input
        }
    }

    switch (Sim::mainBusState) {
    case Enu::None:
        if (cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead (1st)
            Sim::mainBusState = Enu::MemReadWait;
        }
        else if (cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (1st)
            Sim::mainBusState = Enu::MemWriteWait;
        }
        break;
    case Enu::MemReadWait:
        if (marUnchanged && cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead (2nd with unchanged MAR)
            Sim::mainBusState = Enu::MemReadReady;
        }
        else if (!marUnchanged && cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead
            // do nothing, already MemReadWait - need another MemRead because the MAR changed
        }
        else if (cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (after a sinle MemRead)
            Sim::mainBusState = Enu::MemWriteWait;
        }
        break;
    case Enu::MemReadReady:
        if (marUnchanged && cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead again (more than 2 in a row)
            // do nothing, already MemReadReady
        }
        else if (!marUnchanged && cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead
            Sim::mainBusState = Enu::MemReadWait; // go back to MemReadWait because the MAR changed
        }
        else if (cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (after 2+ MemReads)
            Sim::mainBusState = Enu::MemWriteWait;
        }
        break;
    case Enu::MemWriteWait:
        if (cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead (after a MemWrite)
            Sim::mainBusState = Enu::MemReadWait;
        }
        else if (marUnchanged && cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (2nd in a row)
            Sim::mainBusState = Enu::MemWriteReady;
        }
        else if (!marUnchanged && cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (with changed MAR)
            // do nothing, MAR changed, still MemReadWait
        }
        break;
    case Enu::MemWriteReady:
        if (cpuPaneItems->MemReadTristateLabel->text() == "1") { // MemRead (after 2+ MemWrites)
            Sim::mainBusState = Enu::MemReadWait;
        }
        else if (marUnchanged && cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (after 2+ in a row)
            // do nothing, already MemWriteReady
        }
        else if (!marUnchanged && cpuPaneItems->MemWriteTristateLabel->text() == "1") { // MemWrite (with changed MAR)
            Sim::mainBusState = Enu::MemWriteWait;
        }
        break;
    default:
        break;
    }
}

int CpuPane::getALUOutput()
{
    int a = -1;
    int b = -1;
    if (cpuPaneItems->aMuxTristateLabel->text() == "0") {
        a = Sim::MDR;
    }
    else if (cpuPaneItems->aMuxTristateLabel->text() == "1" && cpuPaneItems->aLineEdit->text() != "") {
        a = Sim::readRegByte(cpuPaneItems->aLineEdit->text().toInt());
    }

    if (cpuPaneItems->bLineEdit->text() != "") {
        b = Sim::readRegByte(cpuPaneItems->bLineEdit->text().toInt());
    }

    int ALUFn;
    bool ok;
    ALUFn = cpuPaneItems->ALULineEdit->text().toInt(&ok);

    if (!ok) {
        qDebug() << "no ALU input";
        return -1;
    }

    int c;
    int carry;

    switch(ALUFn) {
    case 0: // A
        if (a != -1) {
            c = a;
            aluSetStatusBits(a, 0, a, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 1: // A plus B
        if (a != -1 && b != -1) {
            c = a + b;
            carry = ((c & 0x1ff) >> 8 ) & 0x1 == 1;
            aluSetStatusBits(a, b, c, carry, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 2: // A plus B plus Cin
        if (a != -1 && b != -1) {
            c = a + b + Sim::cBit ? 1 : 0;
            carry = ((c & 0x1ff) >> 8) & 0x1;
            aluSetStatusBits(a, b, c, carry, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 3: // A plus ~B plus 1
        if (a != -1 && b != -1) {
            int busVal = (a & 0xff) + (~b & 0xff) + 1;
            c = busVal & 0xff;
            carry = ((busVal & 0x1ff) >> 8 ) & 0x1;
            aluSetStatusBits(a, b, c, carry, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 4: // A plus ~B plus Cin
        if (a != -1 && b != -1) {
            int busVal = (a & 0xff) + (~b & 0xff) + Sim::cBit ? 1 : 0;
            c = busVal & 0xff;
            carry = ((busVal & 0x1ff) >> 8 ) & 0x1;
            aluSetStatusBits(a, b, c, carry, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 5: // A and B
        if (a != -1 && b != -1) {
            c = a & b;
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 6: // ~(A and B)
        if (a != -1 && b != -1) {
            c = ~(a & b) & 0xff;
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 7: // A + B
        if (a != -1 && b != -1) {
            c = a | b;
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 8: // ~(A + B)
        if (a != -1 && b != -1) {
            c = ~(a | b);
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 9: // A xor B
        if (a != -1 && b != -1) {
            c = (a ^ b) & 0xff; // or ((a & ~b) | (~a & b)) & 0xff
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask);
            return c;
        }
        break;
    case 10: // ~A
        if (a != -1) {
            c = ~a;
            aluSetStatusBits(a, b, c, 0, Enu::NMask|Enu::ZMask, Enu::eUNARY);
            return c;
        }
        break;
    case 11: // ASL A
        if (a != -1) {
            c = (a << 1) & 254; // 254 because 0 gets shifted in
            aluSetStatusBits(a, b, c, (a & 128) / 128, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask, Enu::eUNARY);
            return c;
        }
        break;
    case 12: // ROL A
        if (a != -1) {
            c = ((a << 1) & 254) + Sim::cBit ? 1 : 0;
            aluSetStatusBits(a, b, c, (a & 128) / 128, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask, Enu::eUNARY);
            return (a >> 1) + Sim::cBit;
        }
        break;
    case 13: // ASR A
        if (a != -1) {
            c = ((a >> 1) & 127) | (a & 128);
            aluSetStatusBits(a, b, c, a & 1, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask, Enu::eUNARY);
            return c;
        }
        break;
    case 14: // ROR A
        if (a != -1) {
            c = ((a >> 1) & 127) | (Sim::cBit * 128);
            aluSetStatusBits(a, b, c, a & 1, Enu::CMask|Enu::VMask|Enu::NMask|Enu::ZMask, Enu::eUNARY);
            return c;
        }
        break;
    case 15: // NZVC A
        if (a != -1) {
            c = -1;
            setStatusBit(Enu::N, (a & Enu::NMask) != 0);
            setStatusBit(Enu::Z, (a & Enu::ZMask) != 0);
            setStatusBit(Enu::V, (a & Enu::VMask) != 0);
            setStatusBit(Enu::C, (a & Enu::CMask) != 0);
            return c;
        }
        break;
    default:
        break;
    }
    return -1;
}

void CpuPane::aluSetStatusBits(int a, int b, int c, int carry, int bitMask, int unary)
{
    if (cpuPaneItems->NCkCheckBox->isChecked()) {
        Sim::nBit = false;
        if (bitMask & Enu::NMask && c > 127) {
            Sim::nBit = true;
        }
        setStatusBit(Enu::N, Sim::nBit);
    }

#warning "we should check this carefully - I'm not sure I'm handling the andz correctly"
    if (cpuPaneItems->ZCkCheckBox->isChecked()) {
        if (cpuPaneItems->ANDZTristateLabel->text() == "0") { // zOut from ALU goes straight through
            Sim::zBit = false;
            if (bitMask & Enu::ZMask && c == 0) {
                Sim::zBit = true;
            }
            setStatusBit(Enu::Z, Sim::zBit);
        } else if (cpuPaneItems->ANDZTristateLabel->text() == "1") { // zOut && zCurr
            if (bitMask & Enu::ZMask) {
                Sim::zBit = c == 0 && Sim::zBit;
            }
            setStatusBit(Enu::Z, Sim::zBit);
        }
        else {
            Sim::zBit = false;
            setStatusBit(Enu::Z, Sim::zBit);
        }

        // previously:
//        Sim::nBit = false;
//        if (bitMask & Enu::NMask && c > 127) {
//            Sim::nBit = true;
//        }
//        setStatusBit(Enu::N, Sim::nBit);
    }

    if (cpuPaneItems->CCkCheckBox->isChecked()) {
        Sim::cBit = false;
        if (bitMask & Enu::CMask && carry & 0x1) {
            Sim::cBit = true;
        }
        setStatusBit(Enu::C, Sim::cBit);
    }

    if (cpuPaneItems->VCkCheckBox->isChecked()) {
        Sim::vBit = false;
        if (bitMask & Enu::VMask) {
            switch(unary) {
            case 0:
                if (((c > 127 && a < 128 && b < 128) || (c < 128 && a > 127 && b > 127)))
                    Sim::vBit = true;
                break;
            case 1:
                if (((c > 127 && a < 128) || (c < 128 && a > 127)))
                    Sim::vBit = true;
                break;
            default:
                break;
            }
        }
        setStatusBit(Enu::V, Sim::vBit);
    }

}
