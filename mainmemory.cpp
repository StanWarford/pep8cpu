#include "mainmemory.h"
#include "ui_mainmemory.h"

#include <QScrollBar>
#include "pep.h"

#include <QDebug>

MainMemory::MainMemory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMemory)
{
    ui->setupUi(this);

    populateMemoryItems();

}

MainMemory::~MainMemory()
{
    delete ui;
}

void MainMemory::populateMemoryItems()
{
//    ui->tableWidget->clear();

    ui->tableWidget->setRowCount(65536);
}

void MainMemory::refreshMemory()
{
    for (int i = 0; i < 0xffff; i++) {

    }
}

void MainMemory::showAddress(int address)
{
    Q_ASSERT(0x0000 <= address && address <= 0xffff);

    if (0 > address - currentMemoryOffset || address - currentMemoryOffset >= ui->tableWidget->rowCount()) {
        // Only move the slider when necessary.
        int min = ui->tableWidget->verticalScrollBar()->minimum();
        int max = ui->tableWidget->verticalScrollBar()->maximum();
        // Something like this. Lifted from pep8-1, so the values here may be somewhat different.
        ui->tableWidget->verticalScrollBar()->setValue(min + static_cast<int>(8 * (address / 4096 - 8) + ((address - address % 8) / 65536.0) * (max - min)));
    }

    setHighlight(address);
}

void MainMemory::setValue(int address, int value)
{
    Q_ASSERT(0x0000 <= address && address <= 0xffff);
    Q_ASSERT(0x00 <= value && value <= 0xff);

    QChar character = '0'; // Buh? I don't think he uses this in his code anywhere.

    qDebug("Set Value: Mem[0x%.4x]=0x%.2x",	address, value);

    mem[address] = (char)value;

    // Force the table contents to be refreshed so that the updated value is displayed.
    if (0 <= address - currentMemoryOffset || address - currentMemoryOffset < ui->tableWidget->rowCount()) {
        repositionTable(currentMemoryOffset);
    }
    else {
        repositionTable(address);
    }

    showAddress(address);
}


void MainMemory::loadMemory(const unsigned char **values)
{
#warning Implement
}

QString MainMemory::fillHexValue(int value, int pad, int base)
{
    QString retString = QString("%1").arg(value, 0, base);
    int i = retString.length();
    for (int j = 0; j < pad - i; j++)
    {
        retString = QString("0%1").arg(retString);
    }
    retString = QString("0x%1").arg(retString);
    return retString;
}

void MainMemory::resetHighlight()
{
    QTableWidgetItem *item;

    // Table could have been resized and the index might not be valid.
    if (-1 != highlightedIndex && highlightedIndex < ui->tableWidget->rowCount()) {
//        ui->tableWidget = ui->tableWidget->item(highlightedIndex, 0);
        Q_ASSERT(item);
        if (NULL != item)
        {
            item->setBackground(QBrush(Qt::white));
        }

        item = ui->tableWidget->item(highlightedIndex, 1);
        Q_ASSERT(item);
        if (NULL != item)
        {
            item->setBackground(QBrush(Qt::white));
        }

        item = ui->tableWidget->item(highlightedIndex, 2);
        Q_ASSERT(item);
        if (NULL != item)
        {
            item->setBackground(QBrush(Qt::white));
        }
    }

    highlightedIndex = -1;
}

void MainMemory::setHighlight(int address)
{
    QTableWidgetItem *item;
    Q_ASSERT(0 <= (address - currentMemoryOffset) && (address - currentMemoryOffset) < ui->tableWidget->rowCount());
    resetHighlight();
    highlightedIndex = address - currentMemoryOffset;

    item = ui->tableWidget->item(highlightedIndex, 0);
    Q_ASSERT(item);
    if (NULL != item)
    {
        item->setBackground(QBrush(Qt::yellow));
    }

    item = ui->tableWidget->item(highlightedIndex, 1);
    Q_ASSERT(item);
    if (NULL != item)
    {
        item->setBackground(QBrush(Qt::yellow));
    }

    item = ui->tableWidget->item(highlightedIndex, 2);
    Q_ASSERT(item);
    if (NULL != item)
    {
        item->setBackground(QBrush(Qt::yellow));
    }
}

void MainMemory::repositionTable(int address)
{
    Q_ASSERT(0 <= address && address <= 0x10000);

    QChar character = '0';
    QString hex = "0x%1";
    QString dec = "%1";

    resetHighlight();

    currentMemoryOffset = address > (0x10000 - ui->tableWidget->rowCount()) ? (0x10000 - ui->tableWidget->rowCount()) : address;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        // Set the value of the address cell.
        ui->tableWidget->item(i, 0)->setText(hex.arg(currentMemoryOffset+i, 4, 16, character));
        // Set the value of the hex cell.
        ui->tableWidget->item(i, 1)->setText(hex.arg((int)mem[currentMemoryOffset+i]&0xff, 2, 16, character));
        // Set the value of the dec cell.
        ui->tableWidget->item(i, 2)->setText(dec.arg((int)mem[currentMemoryOffset+i]&0xff));
    }

    ui->tableWidget->verticalScrollBar()->setRange(0, 0x10000-(ui->tableWidget->rowCount()));

    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);
}

// slots:
void MainMemory::slotItemChanged(QTableWidgetItem *item)
{
    qDebug("Memory cell changed: %d,%d", item->row(), item->column());
    QTableWidgetItem *peerItem;
    int value;
    bool ok;
    QChar character = '0';

    if (item->isSelected())
    {
        item->setSelected(false);
        switch(item->column())
        {
        case(1):
            peerItem = ui->tableWidget->item(item->row(), 2);
            value = item->text().toInt(&ok, 16);
            if (ok && 0xff >= value)
            {
                peerItem->setText(QString("%1").arg(value));
                item->setText(QString("0x%1").arg(value, 2, 16, character));
            }
            else
            {
                value = peerItem->text().toInt(&ok, 10);
                item->setText(QString("0x%1").arg(value, 2, 16, character));
            }
            break;
                case(2):
            peerItem = ui->tableWidget->item(item->row(), 1);
            value = item->text().toInt(&ok, 10);
            if (ok & 0xff >= value)
            {
                peerItem->setText(QString("0x%1").arg(value, 2, 16, character));
            }
            else
            {
                value = peerItem->text().toInt(&ok, 16);
                item->setText(QString("%1").arg(value));
            }
            break;
        }
        resetHighlight();

        mem[currentMemoryOffset+item->row()] = (char)value;
    }

    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);
}

void MainMemory::slotSliderChanged(int value)
{
    repositionTable(value);
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
