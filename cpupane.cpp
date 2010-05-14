#include "cpupane.h"
#include "ui_cpupane.h"
#include "enu.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QErrorMessage>

#include <QDebug>

#include "cpupanegraphicsitems.h"
#include "tristatelabel.h"
#include "sim.h"
#include "pep.h"
#include "code.h"

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

void CpuPane::setRegPrecondition(Enu::EMnemonic reg, int value)
{
    switch (reg) {
    case Enu::E_A:
        cpuPaneItems->aRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_X:
        cpuPaneItems->xRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_SP:
        cpuPaneItems->spRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_PC:
        cpuPaneItems->pcRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_IR:
        cpuPaneItems->irRegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T1:
        cpuPaneItems->t1RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T2:
        cpuPaneItems->t2RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T3:
        cpuPaneItems->t3RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T4:
        cpuPaneItems->t4RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T5:
        cpuPaneItems->t5RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    case Enu::E_T6:
        cpuPaneItems->t6RegLineEdit->setText(QString("%1").arg(value, 4, 16));
        break;
    default:
        break;
    }
}

void CpuPane::setStatusPrecondition(Enu::EMnemonic bit, bool value)
{
    switch (bit) {
    case Enu::E_N:
        cpuPaneItems->nBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_Z:
        cpuPaneItems->zBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_V:
        cpuPaneItems->vBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    case Enu::E_C:
        cpuPaneItems->cBitLabel->setText(QString("%1").arg(value ? 1 : 0));
        break;
    default:
        break;
    }
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
