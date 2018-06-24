// File: microcodepane.cpp
/*
    Pep8CPU is a CPU simulator for executing microcode sequences to
    implement instructions in the instruction set of the Pep/8 computer.

    Copyright (C) 2010  J. Stanley Warford, Pepperdine University

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "microcodepane.h"
#include "ui_microcodepane.h"
#include "code.h"
#include "pep.h"
#include "sim.h"

#include <QGridLayout>
#include <QDebug>
#include <QFontDialog>

MicrocodePane::MicrocodePane(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::MicrocodePane)
{
    ui->setupUi(this);

    editor = new MicrocodeEditor(this);

    editor->setFont(QFont(Pep::codeFont, Pep::codeFontSize));
    editor->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    editor->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->label);
    layout->addWidget(editor);
    layout->setContentsMargins(0,0,0,0);
    layout->setVerticalSpacing(0);
    this->setLayout(layout);

    highlighter = new PepHighlighter(editor->document());

    connect(editor->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setLabelToModified(bool)));

    connect(editor->document(), SIGNAL(undoAvailable(bool)), this, SIGNAL(undoAvailable(bool)));
    connect(editor->document(), SIGNAL(redoAvailable(bool)), this, SIGNAL(redoAvailable(bool)));

    editor->setFocus();
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
    Code *code;
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
        if (code->isMicrocode()) {
            Sim::cycleCount++;
        }
        lineNum++;
    }
    // we guarantee a \n at the end of our document for single step highlighting
    if (!sourceCode.endsWith("\n")) {
        editor->appendPlainText("\n");
    }
    return true;
}

QString MicrocodePane::codeToString() {
    QString str = "";
    Code *code;
    for (int i = 0; i < Sim::codeList.size(); ++i) {
        code = Sim::codeList.at(i);
        str.append(code->getObjectCode());
    }
    return str;
}

void MicrocodePane::removeErrorMessages()
{
    QTextCursor cursor(editor->document()->find("// ERROR:"));
    while (!cursor.isNull()) {
        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        cursor = editor->document()->find("// ERROR:", cursor);
    }
}

void MicrocodePane::appendMessageInSourceCodePaneAt(int lineNumber, QString message)
{
    QTextCursor cursor(editor->document());
    if (lineNumber == -2) {
        cursor.setPosition(editor->textCursor().position());
        cursor.movePosition(QTextCursor::NextBlock);
        cursor.clearSelection();
        editor->setTextCursor(cursor);
        editor->ensureCursorVisible();
        message.append("\n");
    }
    else if (lineNumber == -1) {
        cursor.setPosition(0);
        cursor.movePosition(QTextCursor::End);
        if (cursor.block().text() == "") {
            cursor.insertText(message);
        }
        else{
            editor->appendPlainText(message);
        }
        return;
    }
    else {
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

    setLabelToModified(true);
}

QString MicrocodePane::getMicrocode()
{
    return editor->toPlainText();
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

void MicrocodePane::cut()
{
    editor->cut();
}

void MicrocodePane::copy()
{
    editor->copy();
}

void MicrocodePane::paste()
{
    editor->paste();
}

void MicrocodePane::undo()
{
    editor->undo();
}

void MicrocodePane::redo()
{
    editor->redo();
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

void MicrocodePane::onFontChanged(QFont font)
{
    editor->setFont(font);
}

bool MicrocodePane::isModified()
{
    return editor->document()->isModified();
}

void MicrocodePane::setModifiedFalse()
{
    editor->document()->setModified(false);
}

void MicrocodePane::updateSimulationView()
{
    editor->highlightSimulatedLine();
}

void MicrocodePane::clearSimulationView()
{
    editor->clearSimulationView();
}

void MicrocodePane::unCommentSelection()
{
    editor->unCommentSelection();
}

void MicrocodePane::setFilename(QString fileName)
{
    if (fileName == "") {
        ui->label->setText("Microcode");
    }
    else {
        ui->label->setText(QString("Microcode - %1").arg(fileName));
    }
}

void MicrocodePane::setLabelToModified(bool modified)
{
    QString temp = ui->label->text();
    if (modified) {
        ui->label->setText(temp.append(temp.endsWith(QChar('*')) ? "" : "*"));
    }
    else if (temp.endsWith(QChar('*'))) {
        temp.chop(1);
        ui->label->setText(temp);
    }
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

