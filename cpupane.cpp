#include "cpupane.h"
#include "ui_cpupane.h"
#include "enu.h"

using namespace Enu;

CpuPane::CpuPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuPane)
{
    ui->setupUi(this);
}

CpuPane::~CpuPane()
{
    delete ui;
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

