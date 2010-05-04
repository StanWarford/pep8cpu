#include "microcodepane.h"
#include "ui_microcodepane.h"
#include "code.h"
#include "pep.h"
#include "sim.h"

#include <QGridLayout>
#include <QDebug>

MicrocodePane::MicrocodePane(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MicrocodePane)
{
    ui->setupUi(this);

    editor = new MicrocodeEditor(this);

    editor->setFont(QFont(Pep::codeFont, Pep::codeFontSize));

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

MicrocodePane::~MicrocodePane()
{
    delete ui;
}

bool MicrocodePane::microAssemble()
{
    QString sourceLine;
    QString errorString;
    QStringList sourceCodeList;
    Code code;
    int lineNum = 0;

    removeErrorMessages();
    Sim::codeList.clear();
    QString sourceCode = editor->toPlainText();
    sourceCodeList = sourceCode.split('\n');
    while (lineNum < sourceCodeList.size()) {
        sourceLine = sourceCodeList[lineNum];
        if (!Asm::processSourceLine(sourceLine, code, errorString)) {
            appendMessageInSourceCodePaneAt(lineNum, errorString);
            return false;
        }
        Sim::codeList.append(code);
        lineNum++;
    }

    // we guarantee a /n at the end of our document for single step highlighting
    if (!sourceCode.endsWith("\n")) {
        editor->appendPlainText("\n");
    }
    return true;
}

QString MicrocodePane::codeToString() {
    QString str = "";
    Code code;
    for (int i = 0; i < Sim::codeList.size(); ++i) {
        code = Sim::codeList.at(i);
        if (!code.isCommentOnly() && !code.isEmpty()) {
            str.append(code.cLoadCk == -1 ? "  " : QString("%1").arg(code.cLoadCk, -2));
            str.append(code.cC == -1 ? "   " : QString("%1").arg(code.cC, -3));
            str.append(code.cB == -1 ? "   " : QString("%1").arg(code.cB, -3));
            str.append(code.cA == -1 ? "   " : QString("%1").arg(code.cA, -3));
            str.append(code.cMARCk == -1 ? "  " : QString("%1").arg(code.cMARCk, -2));
            str.append(code.cMDRCk == -1 ? "  " : QString("%1").arg(code.cMDRCk, -2));
            str.append(code.cAMux == -1 ? "  " : QString("%1").arg(code.cAMux, -2));
            str.append(code.cMDRMux == -1 ? "  " : QString("%1").arg(code.cMDRMux, -2));
            str.append(code.cCMux == -1 ? "  " : QString("%1").arg(code.cCMux, -2));
            str.append(code.cALU == -1 ? "   " : QString("%1").arg(code.cALU, -3));
            str.append(code.cCCk == -1 ? "  " : QString("%1").arg(code.cCCk, -2));
            str.append(code.cVCk == -1 ? "  " : QString("%1").arg(code.cVCk, -2));
            str.append(code.cANDZ == -1 ? "  " : QString("%1").arg(code.cANDZ, -2));
            str.append(code.cZCk == -1 ? "  " : QString("%1").arg(code.cZCk, -2));
            str.append(code.cNCk == -1 ? "  " : QString("%1").arg(code.cNCk, -2));
            str.append(code.cMemWrite == -1 ? "  " : QString("%1").arg(code.cMemWrite, -2));
            str.append(code.cMemRead == -1 ? "  " : QString("%1").arg(code.cMemRead, -2));
            str.append("\n");
        }
    }
    return str;
}

void MicrocodePane::removeErrorMessages()
{
    QTextCursor cursor(editor->document()->find("//ERROR:"));
    while (!cursor.isNull()) {
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        cursor = editor->document()->find("//ERROR:", cursor);
    }
}

void MicrocodePane::appendMessageInSourceCodePaneAt(int lineNumber, QString message)
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

void MicrocodePane::setMicrocode(QString microcode)
{
    QStringList sourceCodeList;
    sourceCodeList = microcode.split('\n');
    for (int i = 0; i < sourceCodeList.size(); i++) {
        sourceCodeList[i].remove(QRegExp("^[0-9]+\\.?\\s*"));
    }
    microcode = sourceCodeList.join("\n");
    editor->setPlainText(microcode);
}

void MicrocodePane::highlightOnFocus()
{
    if (editor->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

bool MicrocodePane::hasFocus()
{
    return editor->hasFocus();
}

bool MicrocodePane::isUndoable()
{
    return editor->document()->isUndoAvailable();
}

bool MicrocodePane::isRedoable()
{
    return editor->document()->isRedoAvailable();
}

void MicrocodePane::setReadOnly(bool ro)
{
    editor->setReadOnly(ro);
}

void MicrocodePane::updateSimulationView()
{
    editor->highlightSimulatedLine();
}

void MicrocodePane::clearSimulationView()
{
    editor->extraSelections().clear();
}

void MicrocodePane::changeEvent(QEvent *e)
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

