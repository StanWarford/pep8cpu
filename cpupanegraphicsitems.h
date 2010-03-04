#ifndef CPUPANEGRAPHICSITEMS_H
#define CPUPANEGRAPHICSITEMS_H

#include <QGraphicsItem>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

class CpuPaneGraphicsItems : public QGraphicsItem
{
public:
    CpuPaneGraphicsItems(QGraphicsScene *scene);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void repaintMARCk(QPainter *painter);
    void repaintMDRCk(QPainter *painter);
    void repaintCSelect(QPainter *painter);
    void repaintBSelect(QPainter *painter);
    void repaintASelect(QPainter *painter);
    void repaintCMuxSelect(QPainter *painter);
    void repaintCCk(QPainter *painter);
    void repaintLoadCk(QPainter *painter);
    void repaintVCk(QPainter *painter);
    void repaintZCk(QPainter *painter);
    void repaintNCk(QPainter *painter);
    void repaintMemRead(QPainter *painter);
    void repaintMemWrite(QPainter *painter);
    void repaintAMuxSelect(QPainter *painter);

//    QGraphicsScene *parentScene;

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
    QLabel *cMuxerLabel; // data section

    QLabel *ALULabel;
    QLineEdit *ALULineEdit;
    QLabel *ALUFunctionLabel; // data section

    QCheckBox *CCkCheckBox;
    QLabel *CBitLabel; // data section

    QCheckBox *VCkCheckBox;
    QLabel *vBitLabel; // data section
    QLabel *ANDZLabel;
    QLineEdit *ANDZLineEdit;
    QLabel *ANDZMuxLabel; // data section

    QCheckBox *ZCkCheckBox;
    QLabel *ZBitLabel;

    QCheckBox *NCkCheckBox;
    QLabel *NBitLabel;

    QLabel *MemReadLabel;
    QLineEdit *MemReadLineEdit;

    QLabel *MemWriteLabel;
    QLineEdit *MemWriteLineEdit;


};

#endif // CPUPANEGRAPHICSITEMS_H
