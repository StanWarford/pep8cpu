#include "mainmemory.h"
#include "ui_mainmemory.h"
#include "pep.h"
#include "sim.h"

#include <QScrollBar>
#include <QResizeEvent>

#include <QDebug>

MainMemory::MainMemory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMemory)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(1);
    QStringList columns;
    columns << "Hex";
    ui->tableWidget->setHorizontalHeaderLabels(columns);

    ui->tableWidget->setRowCount(1);
    oldRowCount = 1;

    rows << QString("0x0000");
    ui->tableWidget->setVerticalHeaderLabels(rows);

    int address = 0x0000;
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("0x" + QString("%1").arg(Sim::readByte(address), 2, 16).toUpper().trimmed()));

    refreshMemory();

    ui->tableWidget->resize(ui->tableWidget->size());
    populateMemoryItems();

    connect(ui->verticalScrollBar, SIGNAL(actionTriggered(int)), this, SLOT(sliderMoved(int)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(scrollToAddress(QString)));

    ui->scrollToLabel->setFont(QFont(ui->scrollToLabel->font().family(), ui->scrollToLabel->font().pointSize() - 2));
    ui->lineEdit->setFont(QFont(ui->lineEdit->font().family(), ui->lineEdit->font().pointSize() - 2));

    ui->tableWidget->setFont(QFont(Pep::labelFont, Pep::labelFontSize));

    ui->tableWidget->viewport()->installEventFilter(this);
}

MainMemory::~MainMemory()
{
    delete ui;
}

void MainMemory::populateMemoryItems()
{
    rows.clear();

//    qDebug() << "scroll value: " << ui->verticalScrollBar->value();

    int scrollBarValue = ui->verticalScrollBar->value();

    for (int i = scrollBarValue; i < scrollBarValue + ui->tableWidget->rowCount(); i++) {
        rows << "0x" + QString("%1").arg(i, 4, 16, QLatin1Char('0')).toUpper();
    }
    ui->tableWidget->setVerticalHeaderLabels(rows);

    refreshMemory();
}

void MainMemory::refreshMemory()
{
    disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));

    bool ok;
    int address;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        address = ui->tableWidget->verticalHeaderItem(i)->text().toInt(&ok, 16);
        if (ok) {
            ui->tableWidget->item(i, 0)->setText("0x" +
                                                 QString("%1").arg(Sim::readByte(address), 2, 16, QLatin1Char('0')).toUpper());
        }
    }

    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
}

void MainMemory::setMemAddress(int memAddress, int value)
{
    if (memAddress > 0xffff || memAddress < 0) {
        qDebug() << "invalid address: " << memAddress;
    }
    if (value > 255) {
        value = value & 255;
        qDebug() << "setMemAddr of num larger than 255: val: " << value << ", addr: " << memAddress;
    }

    Sim::Mem[memAddress] = value;

    int firstAddress = ui->tableWidget->verticalHeaderItem(0)->text().toInt();
    int lastAddress = firstAddress + ui->tableWidget->rowCount();

    if (memAddress < firstAddress || lastAddress < memAddress) {
        return;
    }
    
    int lineAddress;
    for (int i = firstAddress; i < lastAddress; i++) {
        lineAddress = ui->tableWidget->verticalHeaderItem(i)->text().toInt();
        if (lineAddress == memAddress) {
            ui->tableWidget->item(i, 0)->setText("0x" + QString("%1").arg(value, 2, 16, QLatin1Char('0')).toUpper().trimmed());
        }
    }
}

void MainMemory::setMemPrecondition(int memAddress, int value)
{
//    Sim::Mem[memAddress] = value;
    setMemAddress(memAddress, value);
}

bool MainMemory::testMemPostcondition(int memAddress, int value)
{
    return Sim::Mem[memAddress] == value;
}

void MainMemory::clearMemory()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->item(i, 0)->setText("0x00");
    }
    for (int i = 0; i < 65536; i++) {
        Sim::Mem[i] = 0;
    }
}

void MainMemory::showMemEdited(int address)
{
#warning "this could be a lot cooler, and show via color which cell was edited, but this will do for now"
    refreshMemory();
}

void MainMemory::highlightOnFocus()
{
    if (ui->tableWidget->hasFocus()) {
        ui->label->setAutoFillBackground(true);
    }
    else {
        ui->label->setAutoFillBackground(false);
    }
}

bool MainMemory::hasFocus()
{
    return ui->tableWidget->hasFocus();
}

void MainMemory::sliderMoved(int pos)
{
    (void)pos;
    populateMemoryItems();
}

void MainMemory::cellDataChanged(QTableWidgetItem *item)
{
    // disconnect this signal so that modifying the text of the column next to it doesn't fire this signal; reconnect at the end
    disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));

    int row = item->row();
    QString contents = item->text();
    contents = contents.trimmed();
    QRegExp rx = item->column() == 0 ? QRegExp("(0x)?[0-9a-fA-F]+") : QRegExp("[0-9a-fA-F]+");

    bool addrConvOk;
    bool dataOk;
    int base = contents.startsWith("0x", Qt::CaseInsensitive) ? 16 : 10;
    int address = ui->tableWidget->verticalHeaderItem(row)->text().toInt(&addrConvOk, 16);
    int data = item->text().toInt(&dataOk, base);
    data = data % 256;

    if (contents.contains(rx) && dataOk && addrConvOk) {
        Sim::writeByte(address, data);
        qDebug() << "Sim::Mem[" << address << "]: " << Sim::readByte(address);
        ui->tableWidget->item(row, 0)->setText("0x" + QString("%1").arg(data, 2, 16, QLatin1Char('0')).toUpper().trimmed());
    }
    else if (addrConvOk && !dataOk) {
        qDebug() << "Conversion from text to int failed. data = " << item->text();
        data = Sim::readByte(address);
        ui->tableWidget->item(row, 0)->setText("0x" + QString("%1").arg(data, 2, 16, QLatin1Char('0')).toUpper().trimmed());
    }
    else if (addrConvOk) { // we have problems, the labels are incorrectly formatted
        populateMemoryItems();
    }

    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
}

void MainMemory::scrollToAddress(QString string)
{
    bool ok;
    int byte;
    if (string.startsWith("0x", Qt::CaseInsensitive)) {
        byte = string.toInt(&ok, 16);
        if (ok) {
            if (byte > 65535) {
                ui->lineEdit->setText("0xFFFF");
            } else {
#warning "fix this whole thing"
//                int min = ui->verticalScrollBar->minimum();
//                int max = ui->verticalScrollBar->maximum();
                ui->verticalScrollBar->setValue(byte);
                sliderMoved(0);
//                ui->verticalScrollBar->setValue(min + static_cast<int>(8 * (byte / 4096 - 8) + ((byte - byte % 8) / 65536.0) * (max - min)));
            }
        }
        else {
            ui->lineEdit->setText("0x");
        }
    }
    else {
        ui->lineEdit->setText("0x");
    }
}

void MainMemory::changeEvent(QEvent *e)
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

void MainMemory::resizeEvent(QResizeEvent *)
{
    int newRowCount = ui->tableWidget->height()/ui->tableWidget->rowHeight(0) - 1;
    // +1 to make it look like we're actually scrolling and not shuffling items

    ui->verticalScrollBar->setMaximum(ui->verticalScrollBar->maximum() - newRowCount);

    if (ui->verticalScrollBar->value() > ui->verticalScrollBar->maximum() - newRowCount) {
        ui->verticalScrollBar->setValue(0xffff - newRowCount);
    }

    if (newRowCount > oldRowCount) {
        ui->tableWidget->setRowCount(newRowCount);

        bool addrConvOk;
        int address;

        for (int i = oldRowCount; i < newRowCount; i++) {
            rows << "0x" + QString("%1").arg(i, 4, 16, QLatin1Char('0')).toUpper();
        }
        ui->tableWidget->setVerticalHeaderLabels(rows);

        disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));

        for (int row = oldRowCount; row < newRowCount; row++) {
            address = ui->tableWidget->verticalHeaderItem(row)->text().toInt(&addrConvOk, 16);
            if (addrConvOk) {
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem("0x" + QString("%1").arg(Sim::readByte(address), 2, 16).toUpper().trimmed()));
            }
            else { // malformed address labels
            }
        }

        connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));

        refreshMemory();
    }
    else if (oldRowCount > newRowCount) {
        ui->tableWidget->setRowCount(newRowCount);
        for (int i = oldRowCount; i > newRowCount; i--) {
            delete ui->tableWidget->item(i, 0);
            rows.removeLast();
        }
        refreshMemory();
    }
}

bool MainMemory::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::Wheel) {
        qApp->sendEvent(ui->verticalScrollBar, e);
        return true;
    }
    return false;
}


