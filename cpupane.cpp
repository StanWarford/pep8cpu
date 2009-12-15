#include "cpupane.h"
#include "ui_cpupane.h"

cpuPane::cpuPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cpuPane)
{
    ui->setupUi(this);
}

cpuPane::~cpuPane()
{
    delete ui;
}

void cpuPane::changeEvent(QEvent *e)
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
