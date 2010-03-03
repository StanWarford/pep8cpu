#include "microcode.h"
#include "ui_microcode.h"

#include <QGridLayout>

Microcode::Microcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Microcode)
{
    ui->setupUi(this);

    editor = new MicrocodeEditor(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->label);
    layout->addWidget(editor);
    layout->setContentsMargins(0,0,0,0);
    layout->setVerticalSpacing(0);
    this->setLayout(layout);

    highlighter = new PepHighlighter(editor->document());

    connect(editor->document(), SIGNAL(undoAvailable(bool)), this, SIGNAL(undoAvailable(bool)));
    connect(editor->document(), SIGNAL(redoAvailable(bool)), this, SIGNAL(redoAvailable(bool)));

}

Microcode::~Microcode()
{
    delete ui;
}

void Microcode::setMicrocode(QString microcode)
{
    QStringList sourceCodeList;
    sourceCodeList = microcode.split('\n');
    for (int i = 0; i < sourceCodeList.size(); i++) {
        sourceCodeList[i].remove(QRegExp("^[0-9]+\.?\\s*"));
    }
    microcode = sourceCodeList.join("\n");
    editor->setPlainText(microcode);
}

void Microcode::highlightOnFocus()
{
    if (editor->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

bool Microcode::hasFocus()
{
    return editor->hasFocus();
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

