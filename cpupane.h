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
    void setRegisterByte(int reg, quint8 value);
    void setStatusBit(Enu::EMnemonic bit, bool value);

    void setRegPrecondition(Enu::EMnemonic reg, int value);
    void setStatusPrecondition(Enu::EMnemonic bit, bool value);
    bool testRegPostcondition(Enu::EMnemonic reg, int value);
    bool testStatusPostcondition(Enu::EMnemonic bit, bool value);

    void clearCpu();
    void clearCpuControlSignals();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

    QGraphicsScene *scene;

    CpuPaneGraphicsItems *cpuPaneItems;

    //simulation helpers
    void setMainBusState();
    bool aluSetStatusBits(int a, int b, int c, int carry, int bitMask, bool isUnary, QString &errorString);

    // called by the push buttons to simulate a single step; returns true if there were no issues
    bool step(QString& errorString);

private slots:
    void regTextEdited(QString str);

    void zoomFactorChanged(int factor);

    void labelClicked();

    void clockButtonPushed();
    void singleStepButtonPushed();
    void resumeButtonPushed();

    void on_copyToMicrocodePushButton_clicked();

    void ALUTextEdited(QString str);

    bool getALUOut(quint8& out, QString& errorString);
    bool getCMuxOut(quint8& out, QString& errorString);
    bool getAMuxOut(quint8& out, QString& errorString);
    bool getMDRMuxOut(quint8& out, QString& errorString);
    bool getABusOut(quint8& out, QString& errorString);
    bool getBBusOut(quint8& out, QString& errorString);

signals:
    void updateSimulation();
    void simulationFinished();
    void appendMicrocodeLine(QString line);
    void readByte(int address);
    void writeByte(int address);
};

#endif // CPUPANE_H
