#ifndef MICROCODE_H
#define MICROCODE_H

#include <QWidget>
#include "pephighlighter.h"
#include "microcodeeditor.h"

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

    void setMicrocode(QString microcode);

    // Highlights the label based on the label window color saved in the UI file
    void highlightOnFocus();

    // Returns if the text edit has focus
    bool hasFocus();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Microcode *ui;

    PepHighlighter *highlighter;
    MicrocodeEditor *editor;


signals:
    void undoAvailable(bool);
    void redoAvailable(bool);

};

#endif // MICROCODE_H
