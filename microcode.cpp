#include "microcode.h"
#include "ui_microcode.h"

Microcode::Microcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Microcode)
{
    ui->setupUi(this);

    highlighter = new PepHighlighter(ui->textEdit->document());

}

Microcode::~Microcode()
{
    delete ui;
}

void Microcode::setMicrocode(QString microcode)
{
    ui->textEdit->setText(microcode);
}

void Microcode::changeEvent(QEvent *e)
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
