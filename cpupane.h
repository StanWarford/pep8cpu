#ifndef CPUPANE_H
#define CPUPANE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
    class CpuPane;
}

class CpuPane : public QWidget {
    Q_OBJECT
public:
    CpuPane(QWidget *parent = 0);
    ~CpuPane();

    void highlightOnFocus();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CpuPane *ui;

    QGraphicsScene *scene;

    QCheckBox *loadCk;
    QLabel *cLabel;
    QLineEdit *cLineEdit;
    QLabel *bLabel;
    QLineEdit *bLineEdit;
    QLabel *aLabel;
    QLineEdit *aLineEdit;

    QCheckBox *MARCk;
    QLabel *MARALabel; // data section
    QLabel *MARBLabel; // data section
    QCheckBox *MDRCk;

    QLabel *aMuxLabel;
    QLabel *aMuxerDataLabel; // data section
    QLineEdit *aMuxLineEdit;

    QLabel *MDRMuxLabel;
    QLabel *MDRMuxerDataLabel; // data section
    QLineEdit *MDRMuxLineEdit;

    QLabel *cMuxLabel;
    QLineEdit *cMuxLineEdit;

    QLabel *ALULabel;
    QLineEdit *ALULineEdit;
    QLabel *ALUFunctionLabel; // data section

    QCheckBox *CCkCheckBox;
    QLabel *CBitLabel; // data section

    QCheckBox *VCkCheckBox;
    QLabel *VBitLabel; // data section
    QLabel *ANDZLabel;
    QLineEdit *ANDZLineEdit;
    QLabel *ANDZMuxLabel; // data section

private slots:
    void zoomFactorChanged(int factor);
};

#endif // CPUPANE_H
