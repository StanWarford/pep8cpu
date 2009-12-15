#ifndef CPUPANE_H
#define CPUPANE_H

#include <QWidget>

namespace Ui {
    class cpuPane;
}

class cpuPane : public QWidget {
    Q_OBJECT
public:
    cpuPane(QWidget *parent = 0);
    ~cpuPane();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::cpuPane *ui;
};

#endif // CPUPANE_H
