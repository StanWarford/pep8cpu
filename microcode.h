#ifndef MICROCODE_H
#define MICROCODE_H

#include <QWidget>

namespace Ui {
    class Microcode;
}

class Microcode : public QWidget {
    Q_OBJECT
public:
    Microcode(QWidget *parent = 0);
    ~Microcode();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Microcode *ui;
};

#endif // MICROCODE_H
