#include "mainmemory.h"
#include "ui_mainmemory.h"

#include <QScrollBar>
#include "pep.h"

MainMemory::MainMemory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMemory)
{
    ui->setupUi(this);
}

MainMemory::~MainMemory()
{
    delete ui;
}

void MainMemory::ShowAddress(int nAddress)
{
    Q_ASSERT(0x0000 <= nAddress && nAddress <= 0xffff);

    if (0 > nAddress - m_nCurrentMemoryOffset || nAddress - m_nCurrentMemoryOffset >= ui->tableWidget->rowCount()) {
        // Only move the slider when necessary.
        int min = ui->tableWidget->verticalScrollBar()->minimum();
        int max = ui->tableWidget->verticalScrollBar()->maximum();
        // Something like this. Lifted from pep8-1, so the values here may be somewhat different.
        ui->tableWidget->verticalScrollBar()->setValue(min + static_cast<int>(8 * (nAddress / 4096 - 8) + ((nAddress - nAddress % 8) / 65536.0) * (max - min)));
    }

    SetHighlight(nAddress);
}


void MainMemory::SetValue(int nAddress, int nValue)
{
    Q_ASSERT(0x0000 <= nAddress && nAddress <= 0xffff);
    Q_ASSERT(0x00 <= nValue && nValue <= 0xff);

    QChar xChar = '0';

    qDebug("Set Value: Mem[0x%.4x]=0x%.2x",	nAddress, nValue);

    m_chMem[nAddress] = (char)nValue;

    // Force the table contents to be refreshed so that the updated value is displayed.
    if (0 <= nAddress - m_nCurrentMemoryOffset || nAddress - m_nCurrentMemoryOffset < ui->tableWidget->rowCount()) {
        RepositionTable(m_nCurrentMemoryOffset);
    }
    else {
        RepositionTable(nAddress);
    }

    ShowAddress(nAddress);
}


void MainMemory::LoadMemory(const unsigned char **ppchValues)
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

void MainMemory::ResetHighlight()
{
    QTableWidgetItem *pxItem;

    // Table could have been resized and the index might not be valid.
    if (-1 != m_nHighlightedIndex && m_nHighlightedIndex < ui->tableWidget->rowCount()) {
//        ui->tableWidget = ui->tableWidget->item(m_nHighlightedIndex, 0);
        Q_ASSERT(pxItem);
        if (NULL != pxItem)
        {
            pxItem->setBackground(QBrush(Qt::white));
        }

        pxItem = ui->tableWidget->item(m_nHighlightedIndex, 1);
        Q_ASSERT(pxItem);
        if (NULL != pxItem)
        {
            pxItem->setBackground(QBrush(Qt::white));
        }

        pxItem = ui->tableWidget->item(m_nHighlightedIndex, 2);
        Q_ASSERT(pxItem);
        if (NULL != pxItem)
        {
            pxItem->setBackground(QBrush(Qt::white));
        }
    }

    m_nHighlightedIndex = -1;
}

void MainMemory::SetHighlight(int nAddress)
{
    QTableWidgetItem *pxItem;
    Q_ASSERT(0 <= (nAddress - m_nCurrentMemoryOffset) && (nAddress - m_nCurrentMemoryOffset) < ui->tableWidget->rowCount());
    ResetHighlight();
    m_nHighlightedIndex = nAddress - m_nCurrentMemoryOffset;

    pxItem = ui->tableWidget->item(m_nHighlightedIndex, 0);
    Q_ASSERT(pxItem);
    if (NULL != pxItem)
    {
        pxItem->setBackground(QBrush(Qt::yellow));
    }

    pxItem = ui->tableWidget->item(m_nHighlightedIndex, 1);
    Q_ASSERT(pxItem);
    if (NULL != pxItem)
    {
        pxItem->setBackground(QBrush(Qt::yellow));
    }

    pxItem = ui->tableWidget->item(m_nHighlightedIndex, 2);
    Q_ASSERT(pxItem);
    if (NULL != pxItem)
    {
        pxItem->setBackground(QBrush(Qt::yellow));
    }
}

void MainMemory::RepositionTable(int nAddress)
{
    Q_ASSERT(0 <= nAddress && nAddress <= 0x10000);

    QChar cxChar = '0';
    QString cxHex = "0x%1";
    QString cxDec = "%1";

    ResetHighlight();

    m_nCurrentMemoryOffset = nAddress > (0x10000 - ui->tableWidget->rowCount()) ? (0x10000 - ui->tableWidget->rowCount()) : nAddress;

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        // Set the value of the address cell.
        ui->tableWidget->item(i, 0)->setText(cxHex.arg(m_nCurrentMemoryOffset+i, 4, 16, cxChar));
        // Set the value of the hex cell.
        ui->tableWidget->item(i, 1)->setText(cxHex.arg((int)m_chMem[m_nCurrentMemoryOffset+i]&0xff, 2, 16, cxChar));
        // Set the value of the dec cell.
        ui->tableWidget->item(i, 2)->setText(cxDec.arg((int)m_chMem[m_nCurrentMemoryOffset+i]&0xff));
    }

    ui->tableWidget->verticalScrollBar()->setRange(0, 0x10000-(ui->tableWidget->rowCount()));

    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);
}

// slots:
void MainMemory::SlotItemChanged(QTableWidgetItem *pxItem)
{
    qDebug("Memory cell changed: %d,%d", pxItem->row(), pxItem->column());
    QTableWidgetItem *pxPeerItem;
    int nValue;
    bool bOk;
    QChar xChar = '0';

    if (pxItem->isSelected())
    {
        pxItem->setSelected(false);
        switch(pxItem->column())
        {
        case(1):
            pxPeerItem = ui->tableWidget->item(pxItem->row(), 2);
            nValue = pxItem->text().toInt(&bOk, 16);
            if (bOk && 0xff >= nValue)
            {
                pxPeerItem->setText(QString("%1").arg(nValue));
                pxItem->setText(QString("0x%1").arg(nValue, 2, 16, xChar));
            }
            else
            {
                nValue = pxPeerItem->text().toInt(&bOk, 10);
                pxItem->setText(QString("0x%1").arg(nValue, 2, 16, xChar));
            }
            break;
                case(2):
            pxPeerItem = ui->tableWidget->item(pxItem->row(), 1);
            nValue = pxItem->text().toInt(&bOk, 10);
            if (bOk & 0xff >= nValue)
            {
                pxPeerItem->setText(QString("0x%1").arg(nValue, 2, 16, xChar));
            }
            else
            {
                nValue = pxPeerItem->text().toInt(&bOk, 16);
                pxItem->setText(QString("%1").arg(nValue));
            }
            break;
        }
        ResetHighlight();

        m_chMem[m_nCurrentMemoryOffset+pxItem->row()] = (char)nValue;
    }

    ui->tableWidget->resizeColumnToContents(0);
    ui->tableWidget->resizeColumnToContents(1);
    ui->tableWidget->resizeColumnToContents(2);
}

void MainMemory::SlotSliderChanged(int nValue)
{
    RepositionTable(nValue);
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
