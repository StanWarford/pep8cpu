#include "microcode.h"
#include "ui_microcode.h"
#include "code.h"

#include <QGridLayout>
#include <QDebug>

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

bool Microcode::microAssemble()
{
    QString sourceLine;
    QString errorString;
    QStringList sourceCodeList;
    Code code;
    int lineNum = 0;

    removeErrorMessages();
    codeList.clear();
    QString sourceCode = editor->toPlainText();
    sourceCodeList = sourceCode.split('\n');
    while (lineNum < sourceCodeList.size()) {
        sourceLine = sourceCodeList[lineNum];
        qDebug() << lineNum << ": " << sourceLine;
        if (!Asm::processSourceLine(sourceLine, lineNum, code, errorString)) {
            appendMessageInSourceCodePaneAt(lineNum, errorString);
            qDebug() << "errorString = " << errorString;
            return false;
        }
        codeList.append(code);
        lineNum++;
    }
    return true;
}

void Microcode::removeErrorMessages()
{
    qDebug() << "removeErrorMessaged called.";
    QTextCursor cursor(editor->document()->find("//ERROR:"));
    while (!cursor.isNull()) {
        qDebug() << "Error found";
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        cursor = editor->document()->find("//ERROR:", cursor);
    }
}

void Microcode::appendMessageInSourceCodePaneAt(int lineNumber, QString message)
{
    QTextCursor cursor(editor->document());
    cursor.setPosition(0);
    for (int i = 0; i < lineNumber; i++) {
        cursor.movePosition(QTextCursor::NextBlock);
    }
    cursor.movePosition(QTextCursor::EndOfBlock);
    cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
    if (cursor.selectedText() == " ") {
        cursor.setPosition(cursor.anchor());
    }
    else {
        cursor.setPosition(cursor.anchor());
        cursor.insertText(" ");
    }
    cursor.insertText(message);
}

void Microcode::setMicrocode(QString microcode)
{
    QStringList sourceCodeList;
    sourceCodeList = microcode.split('\n');
    for (int i = 0; i < sourceCodeList.size(); i++) {
        sourceCodeList[i].remove(QRegExp("^[0-9]+\\.?\\s*"));
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

