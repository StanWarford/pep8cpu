#ifndef CPUPANE_H
#define CPUPANE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

#include "code.h"

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

    void startDebugging();
    void stopDebugging();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

    QGraphicsScene *scene;

    CpuPaneGraphicsItems *cpuPaneItems;

    void setCpuLabels(Code code);

private slots:
    void zoomFactorChanged(int factor);

    void labelClicked();

    void singleStepButtonPushed();
    void resumeButtonPushed();

signals:
    void updateSimulation();
};

#endif // CPUPANE_H
