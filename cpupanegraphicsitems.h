#ifndef CPUPANEGRAPHICSITEMS_H
#define CPUPANEGRAPHICSITEMS_H

#include <QGraphicsItem>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>

class CpuPaneGraphicsItems : public QGraphicsItem
{
public:
    CpuPaneGraphicsItems(QWidget *widgetParent, QGraphicsItem *itemParent = 0, QGraphicsScene *scene = 0);
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

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
    QLabel *MDRLabel; // data section

    QLabel *cMuxLabel;
    QLineEdit *cMuxLineEdit;
    QLabel *cMuxerLabel; // data section

    QLabel *ALULabel;
    QLineEdit *ALULineEdit;
    QLabel *ALUFunctionLabel; // data section

    QCheckBox *CCkCheckBox;
    QLabel *cBitLabel; // data section

    QCheckBox *VCkCheckBox;
    QLabel *vBitLabel; // data section
    QLabel *ANDZLabel;
    QLineEdit *ANDZLineEdit;
    QLabel *ANDZMuxLabel; // data section

    QCheckBox *ZCkCheckBox;
    QLabel *zBitLabel;

    QCheckBox *NCkCheckBox;
    QLabel *nBitLabel;

    QLabel *MemReadLabel;
    QLineEdit *MemReadLineEdit;

    QLabel *MemWriteLabel;
    QLineEdit *MemWriteLineEdit;

private:
    QGraphicsScene *parentScene;
    QWidget *parent;

    void repaintLoadCk(QPainter *painter);
    void repaintCSelect(QPainter *painter);
    void repaintBSelect(QPainter *painter);
    void repaintASelect(QPainter *painter);
    void repaintMARCk(QPainter *painter);
    void repaintMDRCk(QPainter *painter);
    void repaintAMuxSelect(QPainter *painter);

    void repaintCMuxSelect(QPainter *painter);

    void repaintCCk(QPainter *painter);
    void repaintVCk(QPainter *painter);
    void repaintZCk(QPainter *painter);
    void repaintNCk(QPainter *painter);
    void repaintMemRead(QPainter *painter);
    void repaintMemWrite(QPainter *painter);
    void repaintCBitOut(QPainter *painter);
    void repaintVBitOut(QPainter *painter);
    void repaintZBitOut(QPainter *painter);
    void repaintNBitOut(QPainter *painter);

    void repaintANDZSelect(QPainter *painter);
    void repaintALUSelect(QPainter *painter);
    void repaintMDRMuxSelect(QPainter *painter);
};

#endif // CPUPANEGRAPHICSITEMS_H
