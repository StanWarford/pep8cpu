#include "cpupane.h"
#include "ui_cpupane.h"
#include "enu.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QGraphicsItem>

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

    loadCk = new QCheckBox("LoadCk");
    loadCk->setGeometry(550, 18, 80, 20);
    scene->addWidget(loadCk);
//    connect(loadCk, SIGNAL(clicked()), this, SLOT(repaint()));

    QRegExp cbaRegExp("^((3[0-1])|([0-2][0-9])|([0-9]))$");
    cLabel = new QLabel("C");
    cLabel->setGeometry(579, 41, 20, 21);
    scene->addWidget(cLabel);
    cLineEdit = new QLineEdit(0); // Holds the value of the C select lines
    cLineEdit->setGeometry(550, 39, 25, 21);
    cLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(cLineEdit);
    connect(cLineEdit, SIGNAL(textChanged(QString)), this, SLOT(repaintCSelect()));
    // CBus.value = 0;
    // CBus.state = UNDEFINED;

    bLabel = new QLabel("B");
    bLabel->setGeometry(579, 63, 20, 21);
    scene->addWidget(bLabel);
    bLineEdit = new QLineEdit(); // Holds the value of the B select lines
    bLineEdit->setGeometry(550, 61, 25, 21);
    bLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(bLineEdit);
    //    connect(B, SIGNAL (textChanged (const QString &)), this, SLOT (SlotBSelect()));
    //    BBus.value = 0;
    //    BBus.state = UNDEFINED;

    aLabel = new QLabel("A");
    aLabel->setGeometry(579, 85, 20, 21);
    scene->addWidget(aLabel);
    aLineEdit = new QLineEdit(); // Holds the value of the A select lines
    aLineEdit->setGeometry(550,83, 25, 21);
    aLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(aLineEdit);
    //    connect(A, SIGNAL (textChanged (const QString &)), this, SLOT (SlotASelect()));
    //    ABus.value = 0;
    //    ABus.state = UNDEFINED;

    MARCk = new QCheckBox("MARCk");
    MARCk->setGeometry(550, 169, 80, 20);
    scene->addWidget(MARCk);
    //    connect(MARCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    MARALabel = new QLabel("0x00");
    MARALabel->setGeometry(175,202, 69,19);
    MARALabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MARALabel->setAutoFillBackground(false);
    scene->addWidget(MARALabel);
    MARBLabel = new QLabel("0x00");
    MARBLabel->setGeometry(175,132, 69, 19);
    MARBLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(MARBLabel);
    //    MARBus.value = 0;
    //    MARBus.state = UNDEFINED;

    MDRCk = new QCheckBox("MDRCk");
    MDRCk->setGeometry(550, 225, 80, 20);
    scene->addWidget(MDRCk);
    //    connect(MDRCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    //    MDRBus.value = 0;
    //    MDRBus.state = UNDEFINED;

    QRegExp muxRegExp("^[0-1]$");
    aMuxLabel = new QLabel("AMux");
    aMuxLabel->setGeometry(579, 297, 42, 20);
    scene->addWidget(aMuxLabel);
    aMuxerDataLabel = new QLabel("AMux");
    aMuxerDataLabel->setGeometry(306,293, 69,19);
    aMuxerDataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(aMuxerDataLabel);
    aMuxLineEdit = new QLineEdit(); // Holds the value of the AMux select lines
    aMuxLineEdit->setGeometry(550, 295, 25, 21);
    aMuxLineEdit->setValidator(new QRegExpValidator(muxRegExp, 0));
    scene->addWidget(aMuxLineEdit);
    //    connect(AMux, SIGNAL (textChanged (const QString &)), this, SLOT (SlotAMuxSelect()));
    //    AMuxBus.value = 0;
    //    AMuxBus.state = UNDEFINED;

    MDRMuxLabel = new QLabel("MDRMux");
    MDRMuxLabel->setGeometry(579, 318, 61, 20);
    scene->addWidget(MDRMuxLabel);
    MDRMuxerDataLabel = new QLabel("MDRMux");
    MDRMuxerDataLabel->setGeometry(175,293, 69,19);
    MDRMuxerDataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(MDRMuxerDataLabel);
    MDRMuxLineEdit = new QLineEdit(); // Hold the value of the MDRMux select lines
    MDRMuxLineEdit->setGeometry(550, 316, 25, 20);
    MDRMuxLineEdit->setValidator(new QRegExpValidator(muxRegExp, 0));
    scene->addWidget(MDRMuxLineEdit);
    //    connect(MDRMux, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMDRMuxSelect ()));
    //    MDRMuxBus.value = 0;
    //    MDRMuxBus.state = UNDEFINED;

    cMuxLabel = new QLabel("CMux");
    cMuxLabel->setGeometry(QRect(579, 349, 61, 20));
    scene->addWidget(cMuxLabel);
    cMuxerLabel = new QLabel("CMux");
    cMuxerLabel->setGeometry(250, 374, 69, 19);
    cMuxerLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(cMuxerLabel);
    cMuxLineEdit = new QLineEdit();
    cMuxLineEdit->setGeometry(QRect(550, 347, 25, 20));
    cMuxLineEdit->setValidator(new QRegExpValidator(QRegExp("^[0-1]$"), 0));
    scene->addWidget(cMuxLineEdit);
//    QObject::connect(CMux, SIGNAL (textChanged (const QString &)), this, SLOT (SlotCMuxSelect()));
//    CMuxBus.value = 0;
//    CMuxBus.state = UNDEFINED;

    ALULabel = new QLabel("ALU");
    ALULabel->setGeometry(579, 370, 31, 20);
    scene->addWidget(ALULabel);
    ALULineEdit = new QLineEdit();
    ALULineEdit->setGeometry(550, 368, 25, 20);
    ALULineEdit->setValidator(new QRegExpValidator(QRegExp("^((1[0-5])|(0[0-9])|[0-9])$"), 0));
    scene->addWidget(ALULineEdit);
    //    connect(ALU, SIGNAL (textChanged (const QString &)), this, SLOT (SlotALUSelect()));
    ALUFunctionLabel = new QLabel("fn label");
    ALUFunctionLabel->setGeometry(330, 355, 100, 20);
    ALUFunctionLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ALUFunctionLabel);

    CCkCheckBox = new QCheckBox ("CCk");
    CCkCheckBox->setGeometry(550, 407, 60, 20);
    scene->addWidget(CCkCheckBox);
    //    connect(CCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    CBitLabel = new QLabel("0");
    CBitLabel->setGeometry(476,406, 19, 19);
    CBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(CBitLabel);

    VCkCheckBox = new QCheckBox("VCk");
    VCkCheckBox->setGeometry(550, 444, 60, 20);
    scene->addWidget(VCkCheckBox);
    //    connect(VCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    VBitLabel = new QLabel("0");
    VBitLabel->setGeometry(476,442, 19, 19);
    VBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(VBitLabel);

    ANDZLabel = new QLabel("ANDZ");
    ANDZLabel->setGeometry(579, 470, 45, 20);
    scene->addWidget(ANDZLabel);
    ANDZLineEdit = new QLineEdit();
    ANDZLineEdit->setGeometry(550, 468, 25, 21);
    ANDZLineEdit->setValidator(new QRegExpValidator(QRegExp("^[0-1]$"), 0));
    scene->addWidget(ANDZLineEdit);
    //    connect(ANDZ, SIGNAL (textChanged (const QString &)), this, SLOT (SlotANDZSelect()));
    ANDZMuxLabel = new QLabel("ANDZ");
    ANDZMuxLabel->setGeometry(415,495, 41,21);
    ANDZMuxLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ANDZMuxLabel);

    ZCkCheckBox = new QCheckBox("ZCk");
    ZCkCheckBox->setGeometry(550, 499, 60, 20);
    scene->addWidget(ZCkCheckBox);
    //    connect(ZCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    ZBitLabel = new QLabel("0");
    ZBitLabel->setGeometry(476, 498, 19, 19);
    ZBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ZBitLabel);

    NCkCheckBox = new QCheckBox ("NCk");
    NCkCheckBox->setGeometry(550, 550, 60, 20);
    scene->addWidget(NCkCheckBox);
    //    connect(NCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    NBitLabel = new QLabel("0");
    NBitLabel->setGeometry(476,549, 19, 19);
    NBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    scene->addWidget(NBitLabel);

    QRegExp memRWRegExp("^[1]$");
    MemReadLabel = new QLabel("MemRead");
    MemReadLabel->setGeometry(579, 577, 80, 20);
    scene->addWidget(MemReadLabel);

    MemReadLineEdit = new QLineEdit();
    MemReadLineEdit->setGeometry(550, 575, 25, 20);
    MemReadLineEdit->setValidator(new QRegExpValidator(memRWRegExp, 0));
    scene->addWidget(MemReadLineEdit);
    //    connect(MemRead, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMemRead()));

    MemWriteLabel = new QLabel("MemWrite");
    MemWriteLabel->setGeometry(579, 598, 80, 20);
    scene->addWidget(MemWriteLabel);

    MemWriteLineEdit = new QLineEdit();
    MemWriteLineEdit->setGeometry(550, 596, 25, 20);
    MemWriteLineEdit->setValidator(new QRegExpValidator(memRWRegExp, 0));
    scene->addWidget(MemWriteLineEdit);
    //    connect(MemWrite, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMemWrite()));

    // C B A bits
    QGraphicsTextItem *textItem = scene->addText("5");
    textItem->setPos(528, 92);
    textItem = scene->addText("5");
    textItem->setPos(528, 70);
    textItem = scene->addText("5");
    textItem->setPos(528, 48);

    // ALU
    textItem = scene->addText("4");
    textItem->setPos(528, 374);

    // Registers
    QGraphicsRectItem *rectItem;
    rectItem = scene->addRect(5, 5, 491, 113, QPen(QBrush(Qt::lightGray, Qt::SolidPattern), 2, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));

    // MARA & MARB
    rectItem = scene->addRect(175, 132, 69, 19);
    rectItem = scene->addRect(175, 202, 69, 19);

    // MAR bus
    QPolygon poly;
    poly << QPoint(205,151) << QPoint(205,167) << QPoint(173-70,167) << QPoint(173-70,162)
            << QPoint(158-70,177) << QPoint(173-70,192) << QPoint(173-70,187) << QPoint(205,187)
            << QPoint(205,202) << QPoint(215,202) << QPoint(215,151);

    QGraphicsPolygonItem *polyItem = scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(Qt::yellow));
    scene->addLine(170-70, 177, 215, 177);

    // MDR
    rectItem = scene->addRect(175, 254, 69, 19);

    // MDR Bus
    scene->addRect(244,258, 36,10);
    poly.clear();
    poly << QPoint(290,258) << QPoint(326,258) << QPoint(326,280) << QPoint(331,280)
            << QPoint(321,290) << QPoint(311,280) << QPoint(316,280) << QPoint(316,268) << QPoint(290,268);
    scene->addPolygon(poly);
    poly.clear();
    poly << QPoint(175,258) << QPoint(168-70,258) << QPoint(168-70,253) << QPoint(158-70,263)
            << QPoint(168-70,273) << QPoint(168-70,268) << QPoint(175,268);
    scene->addPolygon(poly);

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
    poly << QPoint(314,342) << QPoint(366,342) << QPoint(370,353) << QPoint(390,353) << QPoint(395,342)
            << QPoint(447,342) << QPoint(421,394) << QPoint(340,394);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(Qt::blue));

    poly.clear();
    poly << QPoint(318,344) << QPoint(364,344) << QPoint(368,355) << QPoint(392,355) << QPoint(397,344)
            << QPoint(443,344) << QPoint(419,392) << QPoint(342,392);
    scene->addPolygon(poly, QPen(QBrush(Qt::white), 1), QBrush(Qt::lightGray));
    textItem = scene->addText("ALU");
    textItem->setPos(368, 388);

    // Status Bits
    scene->addRect(476,406, 19,19);
    scene->addRect(476,442, 19,19);
    scene->addRect(476,498, 19,19);
    scene->addRect(476,549, 19,19);

    poly.clear();
    poly << QPoint(310,513) << QPoint(269,513) << QPoint(269,407) << QPoint(274,407) << QPoint(264,397)
            << QPoint(254,407) << QPoint(259,407) << QPoint(259,523) << QPoint(310,523);
    scene->addPolygon(poly);
    scene->addLine(310, 477, 310, 559);

    // filler zeros for status bus
    textItem = scene->addText("0");
    textItem->setPos(314, 530);
    textItem = scene->addText("0");
    textItem->setPos(314, 540);
    textItem = scene->addText("0");
    textItem->setPos(314, 550);
    textItem = scene->addText("0");
    textItem->setPos(314, 560);

    textItem = scene->addText("A Bus");
    textItem->setPos(372, 131);
    textItem = scene->addText("B Bus");
    textItem->setPos(433, 131);
    textItem = scene->addText("C Bus");
    textItem->setPos(300, 131);

    repaintMARCk();
    repaintMDRCk();
    repaintCSelect();
    repaintBSelect();
    repaintCMuxSelect();
    repaintCCk();
    repaintLoadCk();
    repaintVCk();
    repaintZCk();
    repaintNCk();
    repaintMemRead();
    repaintMemWrite();
    repaintASelect();
    repaintAMuxSelect();
}

CpuPane::~CpuPane()
{
    delete ui;
}

void CpuPane::repaintMARCk()
{
#warning "this should not be adding items, need to store the pollys to repaint them later"
    QPolygon poly;
    QColor color;
    if (MARCk->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }

    scene->addLine(428, 177, 543, 177, QPen(color));
    scene->addLine(367, 177, 416, 177, QPen(color));
    scene->addLine(291, 177, 355, 177, QPen(color));
    scene->addLine(235, 177, 279, 177, QPen(color));
    scene->addLine(235, 163, 235, 191, QPen(color));

    poly << QPoint(238, 163) << QPoint(232, 163) << QPoint(235, 155);
    scene->addPolygon(poly, QPen(color));
    poly.clear();
    poly << QPoint(238, 191) << QPoint(232, 191) << QPoint(235, 199);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintMDRCk()
{
    QPolygon poly;
    QColor color;
    if (MDRCk->isChecked()) {
        color = Qt::black;
    }
    else {
        color = Qt::gray;
    }

    scene->addLine(210, 233, 279, 233, QPen(color));
    scene->addLine(291, 233, 355, 233, QPen(color));
    scene->addLine(367, 233, 416, 233, QPen(color));
    scene->addLine(428, 233, 543, 233, QPen(color));
    scene->addLine(210, 233, 210, 241, QPen(color));

    poly << QPoint(213,241) << QPoint(207,241) << QPoint(210,249);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintCSelect()
{
    bool ok;
    QPolygon poly;
    QColor color;
    cLineEdit->text().toInt(&ok, 10);
    if (ok) {
        color = Qt::black;
    }
    else {
        color = Qt::gray;
    }
    // Draw select lines
    scene->addLine(543, 50, 499, 50, QPen(color));
    scene->addLine(523, 45, 533, 55, QPen(color));

    poly << QPoint(499, 50) << QPoint(507, 47) << QPoint(507, 53);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintBSelect()
{
    bool ok;
    QPolygon poly;
    QColor color;
    bLineEdit->text().toInt(&ok, 10);

    if (ok) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }

    // Draw select lines
    scene->addLine(543, 72, 499, 72, QPen(color));
    scene->addLine(523, 67, 533, 77, QPen(color));

    poly << QPoint(499, 72) << QPoint(507, 69) << QPoint(507, 75);
    scene->addPolygon(poly, QPen(color));

    color = Qt::red;
    if (!ok)
        color = Qt::white;

    // Bbus
    poly.clear();
    poly << QPoint(417, 118) << QPoint(417, 136) << QPoint(366, 136) << QPoint(366, 146)
            << QPoint(417, 146) << QPoint(417, 331) << QPoint(412, 331) << QPoint(422, 341)
            << QPoint(432, 331) << QPoint(427, 331) << QPoint(427, 118);
    scene->addPolygon(poly);

    scene->addRect(290, 136, 67, 11, QPen(QBrush(Qt::black), 1), QBrush(color));

    poly.clear();
    poly << QPoint(280, 136) << QPoint(258, 136) << QPoint(258, 131) << QPoint(248, 141)
            << QPoint(258, 151)<< QPoint(258, 146) << QPoint(280, 146) << QPoint(280, 136);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
}

void CpuPane::repaintCMuxSelect()
{
    bool ok;
    QPolygon poly;
    QColor color;
//    int i = cMuxLineEdit->text().toInt(&ok, 10);
//
//    if (ok) {
//        color = Qt::black;
//    } else {
//        color = Qt::gray;
//    }

    // CMux Select
    scene->addLine(449,355, 543,355);
    scene->addLine(315,355, 290,355);
    scene->addLine(280,355, 260,355);
    scene->addLine(260,355, 260,365);
    scene->addLine(428,350, 543,350);
    poly << QPoint(257,362) << QPoint(263,362) << QPoint(260,370);
    scene->addPolygon(poly);

//    if (ok) {
//        switch (i) {
//        case (0):
//            color = Qt::yellow;
//            break;
//        case (1):
////            if (CBus.state == UNDEFINED) {
////                if (CMux-hasFocus())
////                    DisplayMessage("WARNING: CMux select: There is no ALU output", 5000);
////                color = Qt::white;
////            } else {
////                color = Qt::blue;
////            }
//            break;
//        }
//    }
//    else {
//        color = Qt::white;
//    }

    // CMuxBus
    poly.clear();
    poly << QPoint(290,374) << QPoint(290,130) << QPoint(295,130) << QPoint(285,120)
            << QPoint(275,130) << QPoint(280,130) << QPoint(280,334) << QPoint(240,334)
            << QPoint(240,326) << QPoint(245,326) << QPoint(235,316) << QPoint(225,326)
            << QPoint(230,326) << QPoint(230,344) << QPoint(280,344) << QPoint(280,374);
    scene->addPolygon(poly);
}

void CpuPane::repaintCCk()
{
    QPolygon poly;
    QColor color;
    if (CCkCheckBox->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }

    /* CCk */
    scene->addLine(510,415, 543,415);

    poly << QPoint(510,412) << QPoint(510,418) << QPoint(502,415);
    scene->addPolygon(poly);
}

void CpuPane::repaintLoadCk()
{
    QPolygon poly;
    QColor color;

    if (loadCk->isChecked())
    {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }

    scene->addLine(543, 27, 499, 27, QPen(color));
    poly << QPoint(499,27) << QPoint(507,24) << QPoint(507,30);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintVCk()
{
    QColor color;
    QPolygon poly;
    if (VCkCheckBox->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    scene->addLine(510, 451, 543, 451, QPen(color));
    poly.setPoints(3, 510, 448, 510, 454, 502, 451);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintZCk()
{
    QColor color;
    QPolygon poly;
    if (ZCkCheckBox->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    scene->addLine(510, 507, 543, 507, QPen(color));
    poly.setPoints(3, 510,504, 510,510, 502,507);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintNCk()
{
    QColor color;
    QPolygon poly;
    if (NCkCheckBox->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    scene->addLine(510, 558, 543, 558, QPen(color));
    poly.setPoints(3, 510,555, 510,561, 502,558);
    scene->addPolygon(poly, QPen(color));
}

void CpuPane::repaintMemRead()
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
    scene->addLine(166-70, 585, 543, 585, QPen(color));
    poly << QPoint(166-70, 582) << QPoint(166-70, 588) << QPoint(158-70, 585);
    scene->addPolygon(poly, QPen(color));

    if (MemWriteLineEdit->text().toInt(&ok, 10) == 1)
    {
        // Do not paint main bus if MemWrite is isHigh
        return;
    }

    // Draw main bus
    if (isHigh)
    {
//        if (MEM_READ_ADDR == MainBus.state)
//        {
//            pxPainter->setBrush (Qt::yellow);
//        }
//        else if (MEM_READ_DATA == MainBus.state)
//        {
//            pxPainter->setBrush (QBrush(0x109618));
//        }
    }
    else
    {
        // Only repaint white if MemWrite is not set isHigh
        color = Qt::white;
    }

    /* Main Bus */
    poly.clear();
    poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334)
            << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
            << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
            << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
            << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
    scene->addPolygon(poly);

//    if (!(MainBus.state == MEM_READ_DATA))
//        pxPainter->setBrush (Qt::white);

    /* MemOutBus */
    poly.clear();
    poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345)
            << QPoint(134-70, 335) << QPoint(134-70, 340) << QPoint(0, 340);
    scene->addPolygon(poly);
}

void CpuPane::repaintMemWrite()
{
    QPolygon poly;
    QColor color;
    bool ok;
    bool high = MemWriteLineEdit->text().toInt(&ok, 10) == 1;

    // Draw memwrite select line
    if (high) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }

    scene->addLine(166-70, 605, 543, 605);
    poly << QPoint(166-70, 602) << QPoint(166-70, 608) << QPoint(158-70, 605);
    scene->addPolygon(poly);

    if (MemReadLineEdit->text().toInt(&ok, 10) == 1) {
        // Do not paint main bus if MemRead is high
        return;
    }

    // Draw main bus
    if (high)
    {
//        if (MEM_WRITE_ADDR == MainBus.state)
//        {
//            pxPainter->setBrush(Qt::yellow);
//        }
//        else
//        {
//            pxPainter->setBrush(QBrush(0x109618));
//        }
    } else {
        color = Qt::white;
    }

    // Main Bus
    poly.clear();
    poly << QPoint(145-70, 132) << QPoint(155-70, 132) << QPoint(155-70, 334) << QPoint(180, 334);
    poly << QPoint(180, 326) << QPoint(175, 326) << QPoint(185, 316) << QPoint(195, 326) << QPoint(190, 326)
            << QPoint(190, 344) << QPoint(155-70, 344) << QPoint(155-70, 608) << QPoint(145-70, 608)
            << QPoint(145-70, 375) << QPoint(136-123, 375) << QPoint(136-123, 380) << QPoint(126-123, 370)
            << QPoint(136-123, 360) << QPoint(136-123, 365) << QPoint(145-70, 365);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));

    color = Qt::white;

    // MemOutBus
    poly.clear();
    poly << QPoint(0, 350) << QPoint(134-70, 350) << QPoint(134-70, 355) << QPoint(144-70, 345) << QPoint(134-70, 335)
            << QPoint(134-70, 340) << QPoint(0, 340);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
}

void CpuPane::repaintASelect() {
    bool ok;
    QColor color;
    aLineEdit->text().toInt(&ok, 10);
    if (ok) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    QPolygon poly;
    // Draw select lines
    scene->addLine(543,94, 499,94);
    scene->addLine(523,89, 533,99);
    poly.setPoints(3, 499,94, 507,91, 507,97);
    scene->addPolygon(poly, QPen(color));

    color = Qt::red;
    if (!ok)
        color = Qt::white;
    // Abus
    poly.setPoints(11, 356,118, 356,207, 290,207, 290,217, 356,217, 356,280,
                   351,280, 361,290, 371,280, 366,280, 366,118);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
    poly.setPoints(8, 280,207, 258,207, 258,202, 248,212, 258,222, 258,217, 280,217, 280,207);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
}

void CpuPane::repaintAMuxSelect()
{
    QColor color;
    QPolygon poly;
    bool ok;
    int i = aMuxLineEdit->text().toInt(&ok, 10);
    if (ok) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
    // AMux Select
    scene->addLine(388, 303, 416, 303);
    scene->addLine(428, 303, 543, 303);
    poly.setPoints(3, 388, 300, 388, 306, 380, 303);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
//    if (ok) {
//        switch (i) {
//        case (0):
//            color = Qt::yellow;
//            break;
//        case (1):
//            if (ABus.state == UNDEFINED) {
//                color = Qt::white;
//            } else {
//                color = Qt::red;
//            }
//            break;
//        }
//    } else {
//        color = Qt::white;
//    }
    // AMux bus
    poly.setPoints(7, 336,312, 336,331, 331,331, 341,341, 351,331,
                   346,331, 346,312);
    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(color));
}

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
