#include "objectcodepane.h"
#include "ui_objectcodepane.h"

#include "pep.h"
#include <QPainter>

ObjectCodePane::ObjectCodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectCodePane)
{
    ui->setupUi(this);

    ui->plainTextEdit->setFont(QFont(Pep::codeFont, Pep::codeFontSize));

    cpuLabel = new ObjectCodeLabel(this);
    ui->verticalLayout->insertWidget(1, cpuLabel);
    cpuLabel->setFont(QFont(Pep::codeFont, Pep::codeFontSize));
    cpuLabel->setMinimumHeight(QFontMetrics(cpuLabel->font()).averageCharWidth() * 8 + 3); // +3 for padding`
}

ObjectCodePane::~ObjectCodePane()
{
    delete ui;
}

void ObjectCodePane::changeEvent(QEvent *e)
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

void ObjectCodePane::highlightOnFocus()
{
    if (ui->plainTextEdit->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}
