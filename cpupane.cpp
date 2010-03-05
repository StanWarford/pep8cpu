#include "cpupane.h"
#include "ui_cpupane.h"
#include "enu.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QErrorMessage>

#include <QDebug>

#include "cpupanegraphicsitems.h"

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

    CpuPaneGraphicsItems *cpuPaneItems = new CpuPaneGraphicsItems(ui->graphicsView, 0, scene);
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
}
