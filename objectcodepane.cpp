#include "objectcodepane.h"
#include "ui_objectcodepane.h"

#include "sim.h"
#include "pep.h"
#include <QPainter>
#include <QDebug>

ObjectCodePane::ObjectCodePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectCodePane)
{
    ui->setupUi(this);

    QFont font(Pep::codeFont);
    font.setPointSize(Pep::codeFontSize);
    font.setStyleHint(QFont::TypeWriter);

    ui->plainTextEdit->setFont(font);

    cpuLabel = new ObjectCodeLabel(this);
    ui->verticalLayout->insertWidget(1, cpuLabel);
    cpuLabel->setFont(QFont(Pep::codeFont, Pep::codeFontSize));
    cpuLabel->setMinimumHeight(QFontMetrics(cpuLabel->font()).averageCharWidth() * 8 + 3); // +3 for padding
}

ObjectCodePane::~ObjectCodePane()
{
    delete ui;
}

void ObjectCodePane::setObjectCode(QString string)
{
    ui->plainTextEdit->setPlainText(string);
}

void ObjectCodePane::highlightCurrentInstruction()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;

    selection.format.setBackground(QColor(56, 117, 215)); // dark blue
    selection.format.setForeground(Qt::white);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    QTextCursor cursor = QTextCursor(ui->plainTextEdit->document());
    cursor.setPosition(0);
    for (int i = 0; i < Sim::microProgramCounter; i++) {
        cursor.movePosition(QTextCursor::NextBlock);
    }

    // this chunk moves the cursor down and scrolls the text edit to it:
    ui->plainTextEdit->setTextCursor(cursor);
    ui->plainTextEdit->ensureCursorVisible();

    selection.cursor = cursor;
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    ui->plainTextEdit->setExtraSelections(extraSelections);
}

void ObjectCodePane::clearSimulationView()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    ui->plainTextEdit->setExtraSelections(extraSelections);
}

void ObjectCodePane::copy()
{
    ui->plainTextEdit->copy();
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
