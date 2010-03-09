#include "cpupanegraphicsitems.h"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QGraphicsScene>
#include <QPainter>

#include <QDebug>

CpuPaneGraphicsItems::CpuPaneGraphicsItems(QWidget *widgetParent, QGraphicsItem *itemParent, QGraphicsScene *scene)
    : QGraphicsItem(itemParent, scene),
    parent(widgetParent)
{
    loadCk = new QCheckBox("LoadCk");
    loadCk->setPalette(QPalette(Qt::white));
    loadCk->setGeometry(550, 18, 80, 20);
    scene->addWidget(loadCk);

    QRegExp cbaRegExp("^((3[0-1])|([0-2][0-9])|([0-9]))$");
    cLabel = new QLabel("C");
    cLabel->setPalette(QPalette(Qt::white));
    cLabel->setGeometry(579, 41, 20, 21);
    scene->addWidget(cLabel);
    cLineEdit = new QLineEdit(0);
    cLineEdit->setGeometry(550, 39, 25, 21);
    cLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    cLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(cLineEdit);

    bLabel = new QLabel("B");
    bLabel->setGeometry(579, 63, 20, 21);
    bLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(bLabel);
    bLineEdit = new QLineEdit();
    bLineEdit->setGeometry(550, 61, 25, 21);
    bLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    bLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(bLineEdit);

    aLabel = new QLabel("A");
    aLabel->setGeometry(579, 85, 20, 21);
    aLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(aLabel);
    aLineEdit = new QLineEdit();
    aLineEdit->setGeometry(550,83, 25, 21);
    aLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    aLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(aLineEdit);

    MARCk = new QCheckBox("MARCk");
    MARCk->setGeometry(550, 169, 80, 20);
    MARCk->setPalette(QPalette(Qt::white));
    scene->addWidget(MARCk);
    MARALabel = new QLabel("0x00");
    MARALabel->setGeometry(175,202, 69,19);
    MARALabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MARALabel->setAutoFillBackground(false);
    MARALabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MARALabel);
    MARBLabel = new QLabel("0x00");
    MARBLabel->setGeometry(175,132, 69, 19);
    MARBLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MARBLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MARBLabel);

    MDRCk = new QCheckBox("MDRCk");
    MDRCk->setGeometry(550, 225, 80, 20);
    MDRCk->setPalette(QPalette(Qt::white));
    scene->addWidget(MDRCk);

    QRegExp muxRegExp("^[0-1]$");
    aMuxLabel = new QLabel("AMux");
    aMuxLabel->setGeometry(579, 297, 42, 20);
    aMuxLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(aMuxLabel);
    aMuxerDataLabel = new QLabel("AMux");
    aMuxerDataLabel->setGeometry(306,293, 69,19);
    aMuxerDataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    aMuxerDataLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(aMuxerDataLabel);
    aMuxLineEdit = new QLineEdit(); // Holds the value of the AMux select lines
    aMuxLineEdit->setGeometry(550, 295, 25, 21);
    aMuxLineEdit->setValidator(new QRegExpValidator(muxRegExp, 0));
    aMuxLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(aMuxLineEdit);

    MDRMuxLabel = new QLabel("MDRMux");
    MDRMuxLabel->setGeometry(579, 318, 61, 20);
    MDRMuxLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MDRMuxLabel);
    MDRMuxerDataLabel = new QLabel("MDRMux");
    MDRMuxerDataLabel->setGeometry(175,293, 69,19);
    MDRMuxerDataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MDRMuxerDataLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MDRMuxerDataLabel);
    MDRMuxLineEdit = new QLineEdit(); // Hold the value of the MDRMux select lines
    MDRMuxLineEdit->setGeometry(550, 316, 25, 20);
    MDRMuxLineEdit->setValidator(new QRegExpValidator(muxRegExp, 0));
    MDRMuxLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(MDRMuxLineEdit);
    MDRLabel = new QLabel("0x00");
    MDRLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MDRLabel->setGeometry(175,254, 69,19);
    MDRLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MDRLabel);

    cMuxLabel = new QLabel("CMux");
    cMuxLabel->setGeometry(QRect(579, 349, 61, 20));
    cMuxLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(cMuxLabel);
    cMuxerLabel = new QLabel("CMux");
    cMuxerLabel->setGeometry(250, 374, 69, 19);
    cMuxerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    cMuxerLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(cMuxerLabel);
    cMuxLineEdit = new QLineEdit();
    cMuxLineEdit->setGeometry(QRect(550, 347, 25, 20));
    cMuxLineEdit->setValidator(new QRegExpValidator(QRegExp("^[0-1]$"), 0));
    cMuxLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(cMuxLineEdit);

    ALULabel = new QLabel("ALU");
    ALULabel->setGeometry(579, 370, 31, 20);
    ALULabel->setPalette(QPalette(Qt::white));
    scene->addWidget(ALULabel);
    ALULineEdit = new QLineEdit();
    ALULineEdit->setGeometry(550, 368, 25, 20);
    ALULineEdit->setValidator(new QRegExpValidator(QRegExp("^((1[0-5])|(0[0-9])|[0-9])$"), 0));
    ALULineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(ALULineEdit);
    ALUFunctionLabel = new QLabel("fn label");
    ALUFunctionLabel->setGeometry(330, 355, 100, 20);
    ALUFunctionLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ALUFunctionLabel->setPalette(QPalette(Qt::transparent));
    scene->addWidget(ALUFunctionLabel);

    CCkCheckBox = new QCheckBox ("CCk");
    CCkCheckBox->setGeometry(550, 407, 60, 20);
    CCkCheckBox->setPalette(QPalette(Qt::white));
    scene->addWidget(CCkCheckBox);
    cBitLabel = new QLabel("0");
    cBitLabel->setGeometry(476,406, 19, 19);
    cBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    cBitLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(cBitLabel);

    VCkCheckBox = new QCheckBox("VCk");
    VCkCheckBox->setGeometry(550, 444, 60, 20);
    VCkCheckBox->setPalette(QPalette(Qt::white));
    scene->addWidget(VCkCheckBox);
    vBitLabel = new QLabel("0");
    vBitLabel->setGeometry(476,442, 19, 19);
    vBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vBitLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(vBitLabel);

    ANDZLabel = new QLabel("ANDZ");
    ANDZLabel->setGeometry(579, 470, 45, 20);
    ANDZLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(ANDZLabel);
    ANDZLineEdit = new QLineEdit();
    ANDZLineEdit->setGeometry(550, 468, 25, 21);
    ANDZLineEdit->setValidator(new QRegExpValidator(QRegExp("^[0-1]$"), 0));
    ANDZLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(ANDZLineEdit);
    ANDZMuxLabel = new QLabel("ANDZ");
    ANDZMuxLabel->setGeometry(415,495, 41,21);
    ANDZMuxLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ANDZMuxLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(ANDZMuxLabel);

    ZCkCheckBox = new QCheckBox("ZCk");
    ZCkCheckBox->setGeometry(550, 499, 60, 20);
    ZCkCheckBox->setPalette(QPalette(Qt::white));
    scene->addWidget(ZCkCheckBox);
    zBitLabel = new QLabel("0");
    zBitLabel->setGeometry(476, 498, 19, 19);
    zBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    zBitLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(zBitLabel);

    NCkCheckBox = new QCheckBox ("NCk");
    NCkCheckBox->setGeometry(550, 550, 60, 20);
    NCkCheckBox->setPalette(QPalette(Qt::white));
    scene->addWidget(NCkCheckBox);
    nBitLabel = new QLabel("0");
    nBitLabel->setGeometry(476,549, 19, 19);
    nBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    nBitLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(nBitLabel);

    QRegExp memRWRegExp("^[1]$");
    MemReadLabel = new QLabel("MemRead");
    MemReadLabel->setGeometry(579, 577, 80, 20);
    MemReadLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MemReadLabel);
    MemReadLineEdit = new QLineEdit();
    MemReadLineEdit->setGeometry(550, 575, 25, 20);
    MemReadLineEdit->setValidator(new QRegExpValidator(memRWRegExp, 0));
    MemReadLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(MemReadLineEdit);

    MemWriteLabel = new QLabel("MemWrite");
    MemWriteLabel->setGeometry(579, 598, 80, 20);
    MemWriteLabel->setPalette(QPalette(Qt::white));
    scene->addWidget(MemWriteLabel);
    MemWriteLineEdit = new QLineEdit();
    MemWriteLineEdit->setGeometry(550, 596, 25, 20);
    MemWriteLineEdit->setValidator(new QRegExpValidator(memRWRegExp, 0));
    MemWriteLineEdit->setPalette(QPalette(Qt::white));
    scene->addWidget(MemWriteLineEdit);

    // Registers
    QGraphicsRectItem *rectItem;
    scene->addRect(5, 5, 491, 113, QPen(QBrush(Qt::lightGray, Qt::SolidPattern), 2, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));

    // MARA & MARB
    scene->addRect(175, 132, 69, 19);
    scene->addRect(175, 202, 69, 19);

    // MAR bus
    QPolygon poly;
    poly << QPoint(205,151) << QPoint(205,167) << QPoint(173-70,167) << QPoint(173-70,162)
            << QPoint(158-70,177) << QPoint(173-70,192) << QPoint(173-70,187) << QPoint(205,187)
            << QPoint(205,202) << QPoint(215,202) << QPoint(215,151);

    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(Qt::yellow));
    QGraphicsLineItem *lineItem = scene->addLine(173-70, 177, 215, 177);
    lineItem->setZValue(1); // make sure this line appears above the bus

    // MDR
    rectItem = scene->addRect(175, 254, 69, 19);

    // MDR Bus
    scene->addRect(244,258, 36,10, QPen(Qt::black), QBrush(Qt::yellow));
    poly.clear();
    poly << QPoint(290,258) << QPoint(326,258) << QPoint(326,280) << QPoint(331,280)
            << QPoint(321,290) << QPoint(311,280) << QPoint(316,280) << QPoint(316,268) << QPoint(290,268);
    scene->addPolygon(poly, QPen(Qt::black), QBrush(Qt::yellow));
    poly.clear();
    poly << QPoint(175,258) << QPoint(168-70,258) << QPoint(168-70,253) << QPoint(158-70,263)
            << QPoint(168-70,273) << QPoint(168-70,268) << QPoint(175,268);
    scene->addPolygon(poly, QPen(Qt::black), QBrush(Qt::yellow));

    // MDRMux
    scene->addRect(175, 293, 69, 19);

    // AMux
    scene->addRect(306,293, 69,19);

    // CMux
    scene->addRect(250,374, 69,19);

    // ANDZ
    scene->addRect(415,495, 41,21);

    // ALU
    poly.clear();
    poly << QPoint(314,342) << QPoint(366,342) << QPoint(370,353) << QPoint(390,353) << QPoint(394,342)
            << QPoint(447,342) << QPoint(421,394) << QPoint(340,394);
    QGraphicsPolygonItem *polyItem = scene->addPolygon(poly, QPen(QBrush(Qt::black), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin), QBrush(QColor(Qt::blue).lighter(190)));
    polyItem->setZValue(-1);

    // Status Bits
    scene->addRect(476,406, 19,19);
    scene->addRect(476,442, 19,19);
    scene->addRect(476,498, 19,19);
    scene->addRect(476,549, 19,19);

    poly.clear();
    poly << QPoint(310,513) << QPoint(269,513) << QPoint(269,407) << QPoint(274,407) << QPoint(264,397)
            << QPoint(254,407) << QPoint(259,407) << QPoint(259,523) << QPoint(310,523);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(Qt::yellow));
    scene->addLine(310, 477, 310, 559);

}

QRectF CpuPaneGraphicsItems::boundingRect() const
{
    return QRectF(0,0, 650, 620);
}

void CpuPaneGraphicsItems::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon poly;
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::black);

    // select line text
    painter->drawText(528,92, "5");
    painter->drawText(528,70, "5");
    painter->drawText(528,48, "5");
    painter->drawText(528,374, "4");

    painter->drawText(314,531, "0");
    painter->drawText(314,541, "0");
    painter->drawText(314,551, "0");
    painter->drawText(314,561, "0");

    painter->drawText(368,388, "ALU");

    painter->drawText(372,132, "A Bus");
    painter->drawText(433,132, "B Bus");
    painter->drawText(300,132, "C Bus");

    repaintLoadCk(painter);
    repaintCSelect(painter);
    repaintBSelect(painter);
    repaintASelect(painter);
    repaintMARCk(painter);
    repaintMDRCk(painter);
    repaintAMuxSelect(painter);

    repaintCMuxSelect(painter);

    repaintCCk(painter);
    repaintVCk(painter);
    repaintZCk(painter);
    repaintNCk(painter);
    repaintMemRead(painter);
    repaintMemWrite(painter);
    repaintCBitOut(painter);
    repaintVBitOut(painter);
    repaintZBitOut(painter);
    repaintNBitOut(painter);

    repaintANDZSelect(painter);
    repaintALUSelect(painter);
    repaintMDRMuxSelect(painter);

}

void CpuPaneGraphicsItems::repaintLoadCk(QPainter *painter)
{
    QPolygon poly;
    QColor color;

    color = loadCk->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(543, 27, 499, 27);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(499,27) << QPoint(507,24) << QPoint(507,30);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintCSelect(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;

    cLineEdit->text().toInt(&ok, 10);
    ok ? color = Qt::black : color = Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // Draw select lines
    painter->drawLine(543, 50, 499, 50);
    painter->drawLine(523, 45, 533, 55);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(499, 50) << QPoint(507, 47) << QPoint(507, 53);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintBSelect(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;

    bLineEdit->text().toInt(&ok, 10);

    color = ok ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // Draw select lines
    painter->drawLine(543, 72, 499, 72);
    painter->drawLine(523, 67, 533, 77);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.clear();
    poly << QPoint(499, 72) << QPoint(507, 69) << QPoint(507, 75);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    color = ok ? Qt::red : Qt::white;
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(color);

    painter->drawRect(290, 136, 67, 11);

    // Bbus
    poly.clear();
    poly << QPoint(417, 118) << QPoint(417, 136) << QPoint(366, 136) << QPoint(366, 146)
            << QPoint(417, 146) << QPoint(417, 331) << QPoint(412, 331) << QPoint(422, 341)
            << QPoint(432, 331) << QPoint(427, 331) << QPoint(427, 118);
    painter->drawPolygon(poly);

    poly.clear();
    poly << QPoint(280, 136) << QPoint(258, 136) << QPoint(258, 131) << QPoint(248, 141)
            << QPoint(258, 151)<< QPoint(258, 146) << QPoint(280, 146) << QPoint(280, 136);
    painter->drawPolygon(poly);
}

void CpuPaneGraphicsItems::repaintASelect(QPainter *painter)
{

    bool ok;
    QColor color;
    QPolygon poly;

    aLineEdit->text().toInt(&ok, 10);

    color = ok ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // Draw select lines
    painter->drawLine(543,94, 499,94);
    painter->drawLine(523,89, 533,99);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.clear();
    poly << QPoint(499, 94) << QPoint(507, 91) << QPoint(507, 97);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    color = ok ? Qt::red : Qt::white;
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(color);
    // Abus
    poly.clear();
    poly << QPoint(356,118) << QPoint(356,207) << QPoint(290,207) << QPoint(290,217) << QPoint(356,217) << QPoint(356,280)
            << QPoint(351,280) << QPoint(361,290) << QPoint(371,280) << QPoint(366,280) << QPoint(366,118);
    painter->drawPolygon(poly);
    poly.setPoints(8, 280,207, 258,207, 258,202, 248,212, 258,222, 258,217, 280,217, 280,207);
    painter->drawPolygon(poly);

}

void CpuPaneGraphicsItems::repaintMARCk(QPainter *painter)
{
    QPolygon poly;
    QColor color;

    color = MARCk->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // MARCk
    painter->drawLine(428,177, 543,177);
    painter->drawLine(367,177, 416,177);
    painter->drawLine(291,177, 355,177);
    painter->drawLine(235,177, 279,177);
    painter->drawLine(235,163, 235,191);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(238,163) << QPoint(232,163) << QPoint(235,155);
    painter->drawPolygon(poly);

    poly.clear();
    poly << QPoint(238,191) << QPoint(232,191) << QPoint(235,199);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintMDRCk(QPainter *painter)
{
    QPolygon poly;
    QColor color;

    color = MDRCk->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // MDRCk
    painter->drawLine(210,233, 279,233);
    painter->drawLine(291,233, 355,233);
    painter->drawLine(367,233, 416,233);
    painter->drawLine(428,233, 543,233);
    painter->drawLine(210,233, 210,241);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(213,241) << QPoint(207,241) << QPoint(210,249);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintAMuxSelect(QPainter *painter)
{
    QColor color;
    QPolygon poly;
    bool ok;
    int i = aMuxLineEdit->text().toInt(&ok, 10);

    color = ok ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // AMux Select
    painter->drawLine(388, 303, 416, 303);
    painter->drawLine(428, 303, 543, 303);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 388, 300, 388, 306, 380, 303);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    if (ok) {
        switch (i) {
        case (0):
            color = Qt::yellow;
            break;
        case (1):
            if (aLineEdit->text() == "") { // ABus.state == UNDEFINED
                color = Qt::white;
            } else {
                color = Qt::red;
            }
            break;
        }
    } else {
        color = Qt::white;
    }
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(color);

    // AMux bus
    poly.setPoints(7, 336,312, 336,331, 331,331, 341,341, 351,331, 346,331, 346,312);
    painter->drawPolygon(poly);
}

void CpuPaneGraphicsItems::repaintCMuxSelect(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;

    int i = cMuxLineEdit->text().toInt(&ok, 10);

    color = ok ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    // CMux Select
    painter->drawLine(449,355, 543,355);
    painter->drawLine(315,355, 290,355);
    painter->drawLine(280,355, 260,355);
    painter->drawLine(260,355, 260,365);
//    painter->drawLine(428,350, 543,350);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(257,362) << QPoint(263,362) << QPoint(260,370);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    if (ok) {
        switch (i) {
        case (0):
            color = Qt::yellow;
            break;
        case (1):
#warning "Is this right?"
            if (cLineEdit->text() == "") { // CBus.state == UNDEFINED
                if (cMuxLineEdit->hasFocus())
                    qDebug() << "WARNING: CMux select: There is no ALU output";
                color = Qt::white;
            } else {
                color = Qt::blue;
            }
            break;
        }
    }
    else {
        color = Qt::white;
    }
    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(color);

    // CMuxBus
    poly.clear();
    poly << QPoint(290,374) << QPoint(290,130) << QPoint(295,130) << QPoint(285,120)
            << QPoint(275,130) << QPoint(280,130) << QPoint(280,334) << QPoint(240,334)
            << QPoint(240,326) << QPoint(245,326) << QPoint(235,316) << QPoint(225,326)
            << QPoint(230,326) << QPoint(230,344) << QPoint(280,344) << QPoint(280,374);
    painter->drawPolygon(poly);
}

void CpuPaneGraphicsItems::repaintCCk(QPainter *painter)
{
    QPolygon poly;
    QColor color;

    color = CCkCheckBox->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(510,415, 543,415);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(510,412) << QPoint(510,418) << QPoint(502,415);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

}

void CpuPaneGraphicsItems::repaintVCk(QPainter *painter)
{
    QColor color;
    QPolygon poly;

    color = VCkCheckBox->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(510, 451, 543, 451);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 510, 448, 510, 454, 502, 451);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintZCk(QPainter *painter)
{
    QColor color;
    QPolygon poly;

    color = ZCkCheckBox->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(510, 507, 543, 507);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 510,504, 510,510, 502,507);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

}

void CpuPaneGraphicsItems::repaintNCk(QPainter *painter)
{
    QColor color;
    QPolygon poly;

    color = NCkCheckBox->isChecked() ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(510, 558, 543, 558);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 510,555, 510,561, 502,558);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintMemRead(QPainter *painter)
{
    QPolygon poly;
    QColor color;
    bool ok;
    bool isHigh = MemReadLineEdit->text().toInt(&ok, 10) == 1;

    // Draw memread select line
    if (isHigh) {
        MemWriteLineEdit->setReadOnly(true);
        color = Qt::black;
    } else {
        MemWriteLineEdit->setReadOnly(false);
        color = Qt::gray;
    }
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(166-70, 585, 543, 585);

    painter->setRenderHint(QPainter::Antialiasing);
    poly << QPoint(166-70, 582) << QPoint(166-70, 588) << QPoint(158-70, 585);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    if (MemWriteLineEdit->text().toInt(&ok, 10) == 1)
    {
        // Do not paint main bus if MemWrite is isHigh
        return;
    }

    // Draw main bus
    if (isHigh)
    {
#warning "I think this is wrong. We need a sim function to keep track of this stuff"
        if (MemReadLineEdit->text() != "") { // MEM_READ_ADDR == MainBus.state
            color = Qt::yellow;
        } else if (true) { // MEM_READ_DATA == MainBus.state
            color = QColor("0x109618");
        }
    } else {
        // Only repaint white if MemWrite is not set isHigh
        color = Qt::white;
    }

    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->setBrush(color);

    /* Main Bus */
    poly.clear();
    poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334)
            << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
            << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
            << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
            << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
    painter->drawPolygon(poly);

    if (/*MainBus.state != MEM_READ_DATA*/ true) {
        color = Qt::white;
    }
    painter->setBrush(color);

    // MemOutBus
    poly.clear();
    poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345)
            << QPoint(134-70, 335) << QPoint(134-70, 340) << QPoint(0, 340);
    painter->drawPolygon(poly);
}

void CpuPaneGraphicsItems::repaintMemWrite(QPainter *painter)
{
        QPolygon poly;
        QColor color;
        bool ok;
        bool isHigh = MemWriteLineEdit->text().toInt(&ok, 10) == 1;

        // Draw memwrite select line
        color = isHigh ? Qt::black : Qt::gray;
        painter->setPen(QPen(QBrush(color), 1));
        painter->setBrush(color);

        painter->drawLine(166-70, 605, 543, 605);

        painter->setRenderHint(QPainter::Antialiasing);
        poly << QPoint(166-70, 602) << QPoint(166-70, 608) << QPoint(158-70, 605);
        painter->drawPolygon(poly);
        painter->setRenderHint(QPainter::Antialiasing, false);

        if (MemReadLineEdit->text().toInt(&ok, 10) == 1) {
            // Do not paint main bus if MemRead is high
            return;
        }

        // Draw main bus
        if (isHigh)
        {
            if (MemWriteLineEdit->text() != "") { // MEM_WRITE_ADDR == MainBus.state
                color = Qt::yellow;
            } else {
                color = QColor("0x109618");
            }
        } else {
            color = Qt::white;
        }
        painter->setPen(QPen(QBrush(Qt::black), 1));
        painter->setBrush(color);

        // Main Bus
        poly.clear();
        poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334);
        poly << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
                << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
                << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
                << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
        painter->drawPolygon(poly);

        painter->setBrush(Qt::white);

        // MemOutBus
        poly.clear();
        poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345) << QPoint(134-70, 335)
                << QPoint(134-70, 340) << QPoint(0, 340);
        painter->drawPolygon(poly);
}

void CpuPaneGraphicsItems::repaintCBitOut(QPainter *painter)
{
    bool ok;
    QColor color;
    QPolygon poly;

    if (cBitLabel->text().toInt(&ok, 10) == 1) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(487,426, 487,430);
    painter->drawLine(487,430, 330,430);
    painter->drawLine(330,430, 330,486);
    painter->drawLine(330,486, 322,486);

    painter->drawLine(487,404, 487,389);
    painter->drawLine(487,389, 443,389);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 322,483, 322,489, 314,486);
    painter->drawPolygon(poly);
    poly.setPoints(3, 443,386, 443,392, 435,389);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintVBitOut(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;

    if (vBitLabel->text().toInt(&ok, 10) == 1) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    /* V out */
    painter->drawLine(487,462, 487,466);
    painter->drawLine(487,466, 345,466);
    painter->drawLine(345,466, 345,496);
    painter->drawLine(345,496, 322,496);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 322,493, 322,499, 314,496);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintZBitOut(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;
    if (zBitLabel->text().toInt(&ok, 10) == 1) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(487,518, 487,537);
    painter->drawLine(487,537, 345,537);
    painter->drawLine(345,537, 345,506);
    painter->drawLine(345,506, 322,506);

    painter->drawLine(437,537, 437,529);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 322,503, 322,509, 314,506);
    painter->drawPolygon(poly);
    poly.setPoints(3, 434,529, 440,529, 437,521);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintNBitOut(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;
    if (nBitLabel->text().toInt(&ok, 10) == 1) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    painter->drawLine(487,569, 487,573);
    painter->drawLine(487,573, 330,573);
    painter->drawLine(330,573, 330,517);
    painter->drawLine(330,517, 322,517);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 322,514, 322,520, 314,517);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintANDZSelect(QPainter *painter)
{
    bool ok, output = false;
    QPolygon poly;

    int i = ANDZLineEdit->text().toInt(&ok, 10);

    painter->setPen(ok ? Qt::black : Qt::gray);
    painter->setBrush(ok ? Qt::black : Qt::gray);
    if (ok)
    {
        if (i == 1) {
            if (/*zBitLabel->text().toInt(&ok, 10) == 1 && iZ*/ true) {
                output = true;
            }
        } else {
//            output = iZ == 1; // what is this?
        }
    }

    painter->drawLine(437,484, 437,476);
    painter->drawLine(437,476, 543,476);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 434,484, 440,484, 437,493);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(output ? Qt::black : Qt::gray);
    painter->setBrush(output ? Qt::black : Qt::gray);

    // ANDZ out
    painter->drawLine(458,507, 465,507);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 465,504, 465,510, 473,507);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintALUSelect(QPainter *painter)
{
    QPolygon poly;
    QColor color;

    bool ok;
    ALULineEdit->text().toInt(&ok, 10);

    color = ok ? Qt::black : Qt::gray;
    painter->setPen(QPen(QBrush(color), 1));
    painter->setBrush(color);

    /* ALU Select Coordinates */
    painter->drawLine(449,376, 543,376);
    painter->drawLine(523,371, 533,381);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 449,373, 449,379, 441,376);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(Qt::black);

    if (/*LOADED == CBus.state*/ false) {
        painter->setBrush(Qt::blue);
    } else {
        painter->setBrush(Qt::white);
    }

    /* Cbus */
    poly.setPoints(11, 346,394, 346,414, 314,414, 314,407,
                   319,407, 309,397, 299,407, 304,407, 304,424,
                   356,424, 356,394);
    painter->drawPolygon(poly);

    /* Draw status bit lines */
    painter->setPen(/*iN == 1*/ false ? Qt::black : Qt::gray);
    painter->setBrush(/*iN == 1*/ false ? Qt::black : Qt::gray);
    // N
    painter->drawLine(371,395, 371,558);
    painter->drawLine(371,558, 465,558);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 465,555, 465,561, 473,558);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(/*iZ == 1*/ false ? Qt::black : Qt::gray);
    painter->setBrush(/*iZ == 1*/ false ? Qt::black : Qt::gray);
    // Z
    painter->drawLine(386,395, 386,507);
    painter->drawLine(386,507, 404,507);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 404,504, 404,510, 412,507);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(/*iV == 1*/ false ? Qt::black : Qt::gray);
    painter->setBrush(/*iV == 1*/ false ? Qt::black : Qt::gray);
    // V
    painter->drawLine(401,395, 401,451);
    painter->drawLine(401,451, 466,451);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 466,448, 466,454, 474,451);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);

    painter->setPen(/*iC == 1*/ false ? Qt::black : Qt::gray);
    painter->setBrush(/*iC == 1*/ false ? Qt::black : Qt::gray);
    // C
    painter->drawLine(416,395, 416,415);
    painter->drawLine(416,415, 465,415);

    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 465,412, 465,418, 473,415);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void CpuPaneGraphicsItems::repaintMDRMuxSelect(QPainter *painter)
{
    bool ok;
    QPolygon poly;
    QColor color;
    int i = MDRMuxLineEdit->text().toInt(&ok, 10);
    painter->setPen(ok ? Qt::black : Qt::gray);
    painter->setBrush(ok ? Qt::black : Qt::gray);

    /* MDRMux Select */
    painter->drawLine(257,303, 265,303); painter->drawLine(265,303, 265,324);
    painter->drawLine(265,324, 279,324); painter->drawLine(291,324, 335,324);
    painter->drawLine(347,324, 416,324); painter->drawLine(428,324, 543,324);
    //painter->drawLine(523,319, 533,329);
    painter->setRenderHint(QPainter::Antialiasing);
    poly.setPoints(3, 257,300, 257,306, 249,303);
    painter->drawPolygon(poly);
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::black);

    if (ok)
    {
        switch (i)
        {
        case(0):
            if (MemWriteLineEdit->text().toInt() == 1) { // MainBus.state != MEM_READ_DATA
                painter->setBrush(Qt::white);
            } else {
                painter->setBrush(QBrush(0x109618)); // blue
            }
            break;
        case(1):
            if (cMuxLineEdit->text() == "") { // CMuxBus.state == UNDEFINED
                painter->setBrush(Qt::white);
            } else {
                if (cMuxLineEdit->text() == "0") {
                    painter->setBrush(Qt::yellow);
                } else {
                    painter->setBrush(Qt::blue);
                }
            }
            break;
        }
    } else {
        painter->setBrush(Qt::white);
    }

    /* MDRMux Bus */
    poly.setPoints(7, 205,293, 205,286, 200,286, 210,276, 220,286,
                215,286, 215,293);
    painter->drawPolygon(poly);
}

