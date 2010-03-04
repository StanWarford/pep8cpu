#include "cpupane.h"
#include "ui_cpupane.h"
#include "enu.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QErrorMessage>

#include <QDebug>

#include "cpupanegraphicsitems.h"

using namespace Enu;

struct Bus
{
    int value;
    enum BusState state;
};

struct MainBus
{
    int addr;
    int data;
    enum MainBusState state;
    enum MainBusState prevState;
};

CpuPane::CpuPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CpuPane)
{
    ui->setupUi(this);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(zoomFactorChanged(int)));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    CpuPaneGraphicsItems *cpuPaneItems = new CpuPaneGraphicsItems(scene);
    scene->addItem(cpuPaneItems);
}

CpuPane::~CpuPane()
{
    delete ui;
}

//void CpuPane::repaintCMuxSelect()
//{
//    bool ok;
//    QPolygon poly;
//    QColor color;
//    int i = cMuxLineEdit->text().toInt(&ok, 10);
//
//    if (ok) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//
//    // CMux Select
//    scene->addLine(449,355, 543,355);
//    scene->addLine(315,355, 290,355);
//    scene->addLine(280,355, 260,355);
//    scene->addLine(260,355, 260,365);
//    scene->addLine(428,350, 543,350);
//    poly << QPoint(257,362) << QPoint(263,362) << QPoint(260,370);
//    scene->addPolygon(poly);
//
//    if (ok) {
//        switch (i) {
//        case (0):
//            color = Qt::yellow;
//            break;
//        case (1):
//            if (/*CBus.state == UNDEFINED*/ true) {
//                if (cMuxLineEdit->hasFocus())
//                    qDebug() << "WARNING: CMux select: There is no ALU output";
//                color = Qt::white;
//            } else {
//                color = Qt::blue;
//            }
//            break;
//        }
//    }
//    else {
//        color = Qt::white;
//    }
//
//    // CMuxBus
//    poly.clear();
//    poly << QPoint(290,374) << QPoint(290,130) << QPoint(295,130) << QPoint(285,120)
//            << QPoint(275,130) << QPoint(280,130) << QPoint(280,334) << QPoint(240,334)
//            << QPoint(240,326) << QPoint(245,326) << QPoint(235,316) << QPoint(225,326)
//            << QPoint(230,326) << QPoint(230,344) << QPoint(280,344) << QPoint(280,374);
//    scene->addPolygon(poly);
//}
//
//void CpuPane::repaintCCk()
//{
//    QPolygon poly;
//    QColor color;
//    if (CCkCheckBox->isChecked()) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//
//    /* CCk */
//    scene->addLine(510,415, 543,415);
//
//    poly << QPoint(510,412) << QPoint(510,418) << QPoint(502,415);
//    scene->addPolygon(poly);
//}
//
//void CpuPane::repaintLoadCk()
//{
//    QPolygon poly;
//    QColor color;
//
//    if (loadCk->isChecked())
//    {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//
////    scene->addLine(543, 27, 499, 27, QPen(color));
////    poly << QPoint(499,27) << QPoint(507,24) << QPoint(507,30);
////    scene->addPolygon(poly, QPen(QBrush(color), 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin), QBrush(color));
//    ThinArrowGraphicsItem *item = new ThinArrowGraphicsItem(543, 27, 499, 27, color);
//    scene->addItem(item);
//}
//
//void CpuPane::repaintVCk()
//{
//    QColor color;
//    QPolygon poly;
//    if (VCkCheckBox->isChecked()) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//    scene->addLine(510, 451, 543, 451, QPen(color));
//    poly.setPoints(3, 510, 448, 510, 454, 502, 451);
//    scene->addPolygon(poly, QPen(color));
//}
//
//void CpuPane::repaintZCk()
//{
//    QColor color;
//    QPolygon poly;
//    if (ZCkCheckBox->isChecked()) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//    scene->addLine(510, 507, 543, 507, QPen(color));
//    poly.setPoints(3, 510,504, 510,510, 502,507);
//    scene->addPolygon(poly, QPen(color));
//}
//
//void CpuPane::repaintNCk()
//{
//    QColor color;
//    QPolygon poly;
//    if (NCkCheckBox->isChecked()) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//    scene->addLine(510, 558, 543, 558, QPen(color));
//    poly.setPoints(3, 510,555, 510,561, 502,558);
//    scene->addPolygon(poly, QPen(color));
//}
//
//void CpuPane::repaintMemRead()
//{
//    QPolygon poly;
//    QColor color;
//    bool ok;
//    bool isHigh = MemReadLineEdit->text().toInt(&ok, 10) == 1;
//
//    // Draw memread select line
//    if (isHigh) {
//        MemWriteLineEdit->setReadOnly(true);
//        color = Qt::black;
//    } else {
//        MemWriteLineEdit->setReadOnly(false);
//        color = Qt::gray;
//    }
//    scene->addLine(166-70, 585, 543, 585, QPen(color));
//    poly << QPoint(166-70, 582) << QPoint(166-70, 588) << QPoint(158-70, 585);
//    scene->addPolygon(poly, QPen(color));
//
//    if (MemWriteLineEdit->text().toInt(&ok, 10) == 1)
//    {
//        // Do not paint main bus if MemWrite is isHigh
//        return;
//    }
//
//    // Draw main bus
//    if (isHigh)
//    {
//        if (/*MEM_READ_ADDR == MainBus.state*/ true) {
//            color = Qt::yellow;
//        } else if (/*MEM_READ_DATA == MainBus.state*/ true) {
//            color = QColor("0x109618");
//        }
//    } else {
//        // Only repaint white if MemWrite is not set isHigh
//        color = Qt::white;
//    }
//
//    /* Main Bus */
//    poly.clear();
//    poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334)
//            << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
//            << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
//            << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
//            << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
//    scene->addPolygon(poly);
//
//    if (/*MainBus.state != MEM_READ_DATA*/ true) {
//        color = Qt::white;
//    }
//
//    // MemOutBus
//    poly.clear();
//    poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345)
//            << QPoint(134-70, 335) << QPoint(134-70, 340) << QPoint(0, 340);
//    scene->addPolygon(poly);
//}
//
//void CpuPane::repaintMemWrite()
//{
//    QPolygon poly;
//    QColor color;
//    bool ok;
//    bool isHigh = MemWriteLineEdit->text().toInt(&ok, 10) == 1;
//
//    // Draw memwrite select line
//    if (isHigh) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//
//    scene->addLine(166-70, 605, 543, 605);
//    poly << QPoint(166-70, 602) << QPoint(166-70, 608) << QPoint(158-70, 605);
//    scene->addPolygon(poly);
//
//    if (MemReadLineEdit->text().toInt(&ok, 10) == 1) {
//        // Do not paint main bus if MemRead is high
//        return;
//    }
//
//    // Draw main bus
//    if (isHigh)
//    {
//        if (/*MEM_WRITE_ADDR == MainBus.state*/ true) {
//            color = Qt::yellow;
//        } else {
//            color = QColor("0x109618");
//        }
//    } else {
//        color = Qt::white;
//    }
//
//    // Main Bus
//    poly.clear();
//    poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334);
//    poly << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
//            << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
//            << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
//            << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
//    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
//
//    color = Qt::white;
//
//    // MemOutBus
//    poly.clear();
//    poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345) << QPoint(134-70, 335)
//            << QPoint(134-70, 340) << QPoint(0, 340);
//    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
//}
//
//void CpuPane::repaintAMuxSelect()
//{
//    QColor color;
//    QPolygon poly;
//    bool ok;
//    int i = aMuxLineEdit->text().toInt(&ok, 10);
//    if (ok) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }
//    // AMux Select
//    scene->addLine(388, 303, 416, 303);
//    scene->addLine(428, 303, 543, 303);
//    poly.setPoints(3, 388, 300, 388, 306, 380, 303);
//    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
//    if (ok) {
//        switch (i) {
//        case (0):
//            color = Qt::yellow;
//            break;
//        case (1):
//            if (/*ABus.state == UNDEFINED*/ true) {
//                color = Qt::white;
//            } else {
//                color = Qt::red;
//            }
//            break;
//        }
//    } else {
//        color = Qt::white;
//    }
//    // AMux bus
//    poly.setPoints(7, 336,312, 336,331, 331,331, 341,341, 351,331, 346,331, 346,312);
//    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
//}

void CpuPane::highlightOnFocus()
{
    if (ui->graphicsView->hasFocus() || ui->spinBox->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

void CpuPane::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CpuPane::zoomFactorChanged(int factor)
{
    QMatrix matrix;
    matrix.scale(factor * .01, factor * .01);
    ui->graphicsView->setMatrix(matrix);
}
