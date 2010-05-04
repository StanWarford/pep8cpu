#ifndef OBJECTCODEPANE_H
#define OBJECTCODEPANE_H

#include <QWidget>

#include "objectcodelabel.h"

namespace Ui {
    class ObjectCodePane;
}

class ObjectCodePane : public QWidget {
    Q_OBJECT
public:
    ObjectCodePane(QWidget *parent = 0);
    ~ObjectCodePane();

    void highlightOnFocus();

    void setObjectCode(QString string);

    void highlightCurrentInstruction();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ObjectCodePane *ui;

    ObjectCodeLabel *cpuLabel;
};

#endif // OBJECTCODEPANE_H
