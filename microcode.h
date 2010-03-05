#ifndef MICROCODE_H
#define MICROCODE_H

#include <QWidget>
#include "pephighlighter.h"
#include "microcodeeditor.h"
#include "asm.h" // For Code in QList<Code> codeList;

#include <QPlainTextEdit>
#include <QObject>

namespace Ui {
    class Microcode;
}

class Microcode : public QWidget {
    Q_OBJECT
public:
    Microcode(QWidget *parent = 0);
    ~Microcode();

    bool microAssemble();
    // Pre: The source code pane contains a Pep/8 microcode program.
    // Post: If the program assembles correctly, true is returned, and codeList is populated
    // with the code structs. Otherwise false is returned and codeList is partially populated.

    void removeErrorMessages();
    // Post: Searces for the string "//ERROR: " on each line and removes the end of the line.

    void appendMessageInSourceCodePaneAt(int lineNumber, QString message);
    // Post: Appends message to the end of line lineNumber.

    void setMicrocode(QString microcode);

    void highlightOnFocus();
    // Highlights the label based on the label window color saved in the UI file

    bool hasFocus();
    // Returns if the text edit has focus

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Microcode *ui;
    QList<Code> codeList;

    PepHighlighter *highlighter;
    MicrocodeEditor *editor;

signals:
    void undoAvailable(bool);
    void redoAvailable(bool);

};

#endif // MICROCODE_H
