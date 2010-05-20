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
    case Enu::E_A:
        Sim::aReg = value;
        cpuPaneItems->aRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_X:
        Sim::xReg = value;
        cpuPaneItems->xRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_SP:
        Sim::spReg = value;
        cpuPaneItems->spRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_PC:
        Sim::pcReg = value;
        cpuPaneItems->pcRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_IR:
        Sim::irReg = value;
        cpuPaneItems->irRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T1:
        Sim::t1Reg = value;
        cpuPaneItems->t1RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T2:
        Sim::t2Reg = value;
        cpuPaneItems->t2RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T3:
        Sim::t3Reg = value;
        cpuPaneItems->t3RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T4:
        Sim::t4Reg = value;
        cpuPaneItems->t4RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T5:
        Sim::t5Reg = value;
        cpuPaneItems->t5RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T6:
        Sim::t6Reg = value;
        cpuPaneItems->t6RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    default:
        break;
    }
}

void CpuPane::setStatusBit(Enu::EMnemonic bit, bool value)
{
    switch (bit) {
    case Enu::E_N:
        Sim::nBit = value;
        cpuPaneItems->nBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_Z:
        Sim::zBit = value;
        cpuPaneItems->zBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_V:
        Sim::vBit = value;
        cpuPaneItems->vBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_C:
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
    case Enu::E_A:
        return Sim::aReg == value;
        break;
    case Enu::E_X:
        return Sim::xReg == value;
        break;
    case Enu::E_SP:
        return Sim::spReg == value;
        break;
    case Enu::E_PC:
        return Sim::pcReg == value;
        break;
    case Enu::E_IR:
        return Sim::irReg == value;
        break;
    case Enu::E_T1:
        return Sim::t1Reg == value;
        break;
    case Enu::E_T2:
        return Sim::t2Reg == value;
        break;
    case Enu::E_T3:
        return Sim::t3Reg == value;
        break;
    case Enu::E_T4:
        return Sim::t4Reg == value;
        break;
    case Enu::E_T5:
        return Sim::t5Reg == value;
        break;
    case Enu::E_T6:
        return Sim::t6Reg == value;
        break;
    default:
        break;
    }

    return true;
}

bool CpuPane::testStatusPostcondition(Enu::EMnemonic bit, bool value) {
    switch (bit) {
    case Enu::E_N:
        return Sim::nBit == value;
        break;
    case Enu::E_Z:
        return Sim::zBit == value;
        break;
    case Enu::E_V:
        return Sim::vBit == value;
        break;
    case Enu::E_C:
        return Sim::cBit == value;
        break;
    default:
        break;
    }

    return true;
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

    if (!str.startsWith("0x")) {
        lineEdit->setText("0x" + str);
    }
    else {
        str.remove(0, 2);
        str = str.toUpper();
        str.prepend("0x");
        lineEdit->setText(str);
    }

    if (lineEdit == cpuPaneItems->aRegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->xRegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->spRegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->pcRegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->irRegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t1RegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t2RegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t3RegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t4RegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t5RegLineEdit) {

    }
    else if (lineEdit == cpuPaneItems->t6RegLineEdit) {

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
