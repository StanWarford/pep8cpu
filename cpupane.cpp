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
    // connect(loadCk, SIGNAL(toggled(bool)), this, SLOT(Repaint()));

    QRegExp cbaRegExp("^((3[0-1])|([0-2][0-9])|([0-9]))$");
    cLabel = new QLabel("C");
    cLabel->setGeometry(579, 41, 20, 21);
    scene->addWidget(cLabel);
    cLineEdit = new QLineEdit(0); // Holds the value of the C select lines
    cLineEdit->setGeometry(550, 39, 25, 21);
    cLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(cLineEdit);
    // QObject::connect(C, SIGNAL (textChanged (const QString &)), this, SLOT (Repaint()));
    // CBus.value = 0;
    // CBus.state = UNDEFINED;

    bLabel = new QLabel("B");
    bLabel->setGeometry(579, 63, 20, 21);
    scene->addWidget(bLabel);
    bLineEdit = new QLineEdit(); // Holds the value of the B select lines
    bLineEdit->setGeometry(550, 61, 25, 21);
    bLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(bLineEdit);
    //    QObject::connect(B, SIGNAL (textChanged (const QString &)), this, SLOT (SlotBSelect()));
    //    BBus.value = 0;
    //    BBus.state = UNDEFINED;

    aLabel = new QLabel("A");
    aLabel->setGeometry(579, 85, 20, 21);
    scene->addWidget(aLabel);
    aLineEdit = new QLineEdit(); // Holds the value of the A select lines
    aLineEdit->setGeometry(550,83, 25, 21);
    aLineEdit->setValidator(new QRegExpValidator(cbaRegExp, 0));
    scene->addWidget(aLineEdit);
    //    QObject::connect(A, SIGNAL (textChanged (const QString &)), this, SLOT (SlotASelect()));
    //    ABus.value = 0;
    //    ABus.state = UNDEFINED;

    MARCk = new QCheckBox("MARCk");
    MARCk->setGeometry(550, 169, 80, 20);
    scene->addWidget(MARCk);
    //    connect(MARCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    MARALabel = new QLabel("0x00");
    MARALabel->setGeometry(175,202, 69,19);
    MARALabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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
    //    QObject::connect(MDRCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
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
    //    QObject::connect(AMux, SIGNAL (textChanged (const QString &)), this, SLOT (SlotAMuxSelect()));
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
    //    QObject::connect(MDRMux, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMDRMuxSelect ()));
    //    MDRMuxBus.value = 0;
    //    MDRMuxBus.state = UNDEFINED;

    ALULabel = new QLabel("ALU");
    ALULabel->setGeometry(579, 370, 31, 20);
    scene->addWidget(ALULabel);
    ALULineEdit = new QLineEdit();
    ALULineEdit->setGeometry(550, 368, 25, 20);
    ALULineEdit->setValidator(new QRegExpValidator(QRegExp("^((1[0-5])|(0[0-9])|[0-9])$"), 0));
    scene->addWidget(ALULineEdit);
    //    QObject::connect(ALU, SIGNAL (textChanged (const QString &)), this, SLOT (SlotALUSelect()));
    ALUFunctionLabel = new QLabel("fn label");
    ALUFunctionLabel->setGeometry(330, 355, 100, 20);
    ALUFunctionLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ALUFunctionLabel);

    CCkCheckBox = new QCheckBox ("CCk");
    CCkCheckBox->setGeometry(550, 407, 60, 20);
    scene->addWidget(CCkCheckBox);
    //    QObject::connect(CCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    CBitLabel = new QLabel("0");
    CBitLabel->setGeometry(476,406, 19, 19);
    CBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    scene->addWidget(CBitLabel);

    VCkCheckBox = new QCheckBox("VCk");
    VCkCheckBox->setGeometry(550, 444, 60, 20);
    scene->addWidget(VCkCheckBox);
    //    QObject::connect(VCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
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
    //    QObject::connect(ANDZ, SIGNAL (textChanged (const QString &)), this, SLOT (SlotANDZSelect()));
    ANDZMuxLabel = new QLabel("ANDZ");
    ANDZMuxLabel->setGeometry(415,495, 41,21);
    ANDZMuxLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ANDZMuxLabel);

    ZCkCheckBox = new QCheckBox("ZCk");
    ZCkCheckBox->setGeometry(550, 499, 60, 20);
    scene->addWidget(ZCkCheckBox);
    //    QObject::connect(ZCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
    ZBitLabel = new QLabel("0");
    ZBitLabel->setGeometry(476, 498, 19, 19);
    ZBitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    scene->addWidget(ZBitLabel);

    NCkCheckBox = new QCheckBox ("NCk");
    NCkCheckBox->setGeometry(550, 550, 60, 20);
    scene->addWidget(NCkCheckBox);
    //    QObject::connect(NCk, SIGNAL (toggled (bool)), this, SLOT (Repaint()));
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
    //    QObject::connect(MemRead, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMemRead()));

    MemWriteLabel = new QLabel("MemWrite");
    MemWriteLabel->setGeometry(579, 598, 80, 20);
    scene->addWidget(MemWriteLabel);

    MemWriteLineEdit = new QLineEdit();
    MemWriteLineEdit->setGeometry(550, 596, 25, 20);
    MemWriteLineEdit->setValidator(new QRegExpValidator(memRWRegExp, 0));
    scene->addWidget(MemWriteLineEdit);
    //    QObject::connect(MemWrite, SIGNAL (textChanged (const QString &)), this, SLOT (SlotMemWrite()));

//    pxPainter->drawText(528,92, "5");
//    pxPainter->drawText(528,70, "5");
//    pxPainter->drawText(528,48, "5");
//    pxPainter->drawText(528,374, "4");
//
//    /* registers */
//    pxPainter->drawRect(5,5, 491,113);
//    pxPainter->fillRect(6,6, 490,112, Qt::red);
//    pxPainter->fillRect(7,7, 488,110, Qt::gray);
//
//    /* MARA & MARB */
//    pxPainter->drawRect(175,132 , 69,19);
//    pxPainter->fillRect(176,133 , 68,18, Qt::yellow);
//    pxPainter->fillRect(177,134 , 66,16, Qt::gray);
//    pxPainter->drawRect(175,202 , 69,19);
//    pxPainter->fillRect(176,203 , 68,18, Qt::yellow);
//    pxPainter->fillRect(177,204 , 66,16, Qt::gray);

}

CpuPane::~CpuPane()
{
    delete ui;
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
