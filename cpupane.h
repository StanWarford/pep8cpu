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

    void setRegister(Enu::EMnemonic reg, int value);
    void setStatusBit(Enu::EMnemonic bit, bool value);

    void setRegPrecondition(Enu::EMnemonic reg, int value);
    void setStatusPrecondition(Enu::EMnemonic bit, bool value);
    bool testRegPostcondition(Enu::EMnemonic reg, int value);
    bool testStatusPostcondition(Enu::EMnemonic bit, bool value);

    void clearCpu();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

    QGraphicsScene *scene;

    CpuPaneGraphicsItems *cpuPaneItems;

private slots:
    void regTextEdited(QString str);

    void zoomFactorChanged(int factor);

    void labelClicked();

    void singleStepButtonPushed();
    void resumeButtonPushed();

    void on_copyToMicrocodePushButton_clicked();

signals:
    void updateSimulation();
    void simulationFinished();
    void appendMicrocodeLine(QString line);
};

#endif // CPUPANE_H
