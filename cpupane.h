#ifndef CPUPANE_H
#define CPUPANE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

#include "enu.h"

#include "cpupanegraphicsitems.h"

namespace Ui {
    class CpuPane;
}

class CpuPane : public QWidget {
    Q_OBJECT
public:
    CpuPane(QWidget *parent = 0);
    ~CpuPane();

    void highlightOnFocus();
    bool hasFocus();

    void startDebugging();
    void stopDebugging();

    void setRegPrecondition(Enu::EMask bit, bool value);
    void setStatusPrecondition(Enu::EMnemonic reg, int value);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

    QGraphicsScene *scene;

    CpuPaneGraphicsItems *cpuPaneItems;

private slots:
    void zoomFactorChanged(int factor);

    void labelClicked();

    void singleStepButtonPushed();
    void resumeButtonPushed();

signals:
    void updateSimulation();
    void simulationFinished();
};

#endif // CPUPANE_H
