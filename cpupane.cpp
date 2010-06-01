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

struct Bus
{
    int value;
    enum BusState state;
};

struct MainBus
{
    int addr;
    int data;
    enum MainBusState state;
    enum MainBusState prevState;
};

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
}

void CpuPane::singleStepButtonPushed()
{
    if (!Sim::atEndOfSim()) {
        Code *code = Sim::codeList.at(Sim::microCodeCurrentLine);
        while (!Sim::atEndOfSim() && !code->isMicrocode()) {
            Sim::microCodeCurrentLine++;
            code = Sim::codeList.at(Sim::microCodeCurrentLine);
        }
        if (!Sim::atEndOfSim()) {
            Sim::memReadPrevStep = cpuPaneItems->MemReadTristateLabel->text() == "1";
            Sim::memWritePrevStep = cpuPaneItems->MemWriteTristateLabel->text() == "1";

            code->setCpuLabels(cpuPaneItems);

            emit updateSimulation();

            Sim::microProgramCounter++;
            Sim::microCodeCurrentLine++;
        }
        else {
            qDebug() << "simulation completed";
            emit simulationFinished();
            ui->singleStepPushButton->setEnabled(false);
            ui->resumePushButton->setEnabled(false);
        }
    }
    else {
        qDebug() << "simulation completed";
        emit simulationFinished();
        ui->singleStepPushButton->setEnabled(false);
        ui->resumePushButton->setEnabled(false);
    }
}

void CpuPane::resumeButtonPushed()
{

}
