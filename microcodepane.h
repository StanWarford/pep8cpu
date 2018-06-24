// File: microcodepane.h
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
#ifndef MICROCODEPANE_H
#define MICROCODEPANE_H

#include <QWidget>
#include "pephighlighter.h"
#include "microcodeeditor.h"
#include "asm.h" // For Code in QList<Code> codeList;

#include <QPlainTextEdit>
#include <QObject>

namespace Ui {
    class MicrocodePane;
}

class MicrocodePane : public QWidget {
    Q_OBJECT
public:
    MicrocodePane(QWidget *parent = 0);
    ~MicrocodePane();

    bool microAssemble();
    // Pre: The source code pane contains a Pep/8 microcode program.
    // Post: If the program assembles correctly, true is returned, and codeList is populated
    // with the code structs. Otherwise false is returned and codeList is partially populated.

    QString codeToString();

    void removeErrorMessages();
    // Post: Searces for the string "// ERROR: " on each line and removes the end of the line.

    void appendMessageInSourceCodePaneAt(int lineNumber, QString message);
    // Post: Appends message to the end of line lineNumber.

    void setMicrocode(QString microcode);
    // Post: Set

    QString getMicrocode();
    // Post: returns the text of the editor

    void highlightOnFocus();
    // Highlights the label based on the label window color saved in the UI file

    bool hasFocus();
    // Returns if the text edit has focus

    void cut();
    void copy();
    void paste();
    void undo();
    void redo();

    bool isUndoable();
    bool isRedoable();

    void setReadOnly(bool ro);

    bool isModified();
    void setModifiedFalse();

    void updateSimulationView();
    void clearSimulationView();

    void unCommentSelection();

    void setFilename(QString fileName);
public slots:
    void onFontChanged(QFont font);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::MicrocodePane *ui;

    PepHighlighter *highlighter;
    MicrocodeEditor *editor;

private slots:
    void setLabelToModified(bool modified);

signals:
    void undoAvailable(bool);
    void redoAvailable(bool);

};

#endif // MICROCODEPANE_H
