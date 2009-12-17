#ifndef MICROCODE_H
#define MICROCODE_H

#include <QWidget>
#include "pephighlighter.h"

namespace Ui {
    class Microcode;
}

class Microcode : public QWidget {
    Q_OBJECT
public:
    Microcode(QWidget *parent = 0);
    ~Microcode();

    void setMicrocode(QString microcode);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Microcode *ui;

    PepHighlighter *highlighter;
};

#endif // MICROCODE_H
