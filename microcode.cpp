#include "microcode.h"
#include "ui_microcode.h"

Microcode::Microcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Microcode)
{
    ui->setupUi(this);

    highlighter = new PepHighlighter(ui->textEdit->document());

    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), this, SIGNAL(undoAvailable(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), this, SIGNAL(redoAvailable(bool)));

}

Microcode::~Microcode()
{
    delete ui;
}

void Microcode::setMicrocode(QString microcode)
{
    ui->textEdit->setText(microcode);
}

void Microcode::highlightOnFocus()
{
    if (ui->textEdit->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

bool Microcode::hasFocus()
{
    return ui->textEdit->hasFocus();
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
