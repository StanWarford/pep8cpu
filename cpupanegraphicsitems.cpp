#include "cpupanegraphicsitems.h"

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QGraphicsScene>
#include <QPainter>

CpuPaneGraphicsItems::CpuPaneGraphicsItems(QGraphicsScene *scene)
{
//    parentScene = scene;

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
    //    connect(cLineEdit, SIGNAL(textChanged(QString)), this, SLOT(repaintCSelect()));
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
    vBitLabel = new QLabel("0");
    vBitLabel->setGeometry(476,442, 19, 19);
    vBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(vBitLabel);

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

    scene->addPolygon(poly, QPen(QBrush(Qt::black), 1), QBrush(Qt::yellow));
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

}

QRectF CpuPaneGraphicsItems::boundingRect() const
{

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

    painter->drawText(314,530, "0");
    painter->drawText(314,540, "0");
    painter->drawText(314,550, "0");
    painter->drawText(314,560, "0");

    painter->drawText(368,388, "ALU");

    painter->drawText(372,131, "A Bus");
    painter->drawText(433,131, "B Bus");
    painter->drawText(300,131, "C Bus");

    repaintMARCk(painter);
    repaintMDRCk(painter);
    repaintCSelect(painter);
    repaintBSelect(painter);
    repaintASelect(painter);
}


void CpuPaneGraphicsItems::repaintMARCk(QPainter *painter)
{
    QPolygon poly;
    QColor color;
    if (MARCk->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
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

    if (MDRCk->isChecked()) {
        color = Qt::black;
    } else {
        color = Qt::gray;
    }
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

void CpuPaneGraphicsItems::repaintCMuxSelect(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintCCk(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintLoadCk(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintVCk(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintZCk(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintNCk(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintMemRead(QPainter *painter)
{

}

void CpuPaneGraphicsItems::repaintMemWrite(QPainter *painter)
{

}


void CpuPaneGraphicsItems::repaintAMuxSelect(QPainter *painter)
{

}

