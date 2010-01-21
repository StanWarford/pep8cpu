#ifndef CPUPANE_H
#define CPUPANE_H

#include <QWidget>

namespace Ui {
    class CpuPane;
}

class CpuPane : public QWidget {
    Q_OBJECT
public:
    CpuPane(QWidget *parent = 0);
    ~CpuPane();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

};

#endif // CPUPANE_H
