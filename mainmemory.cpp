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

    ui->tableWidget->setColumnCount(2);
    QStringList columns;
    columns << "Hex" << "Dec";
    ui->tableWidget->setHorizontalHeaderLabels(columns);

    ui->tableWidget->setRowCount(10);
    rows.clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        rows << QString("0x%1").arg(i, 4, 16, QLatin1Char('0'));
    }
    ui->tableWidget->setVerticalHeaderLabels(rows);

    for (int i = 0; i < 10; i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem("0x0"));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem("0"));
    }

    connect(ui->verticalScrollBar, SIGNAL(actionTriggered(int)), this, SLOT(sliderMoved(int)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
}

MainMemory::~MainMemory()
{
    delete ui;
}

void MainMemory::populateMemoryItems()
{
    rows.clear();
    qDebug() << "scroll value: " << ui->verticalScrollBar->value();
    int scrollBarValue = ui->verticalScrollBar->value();
    for (int i = scrollBarValue; i < scrollBarValue + ui->tableWidget->rowCount(); i++) {
        rows << QString("0x%1").arg(i, 4, 16, QLatin1Char('0'));
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
            ui->tableWidget->item(i, 0)->setText(QString("0x%1").arg(Sim::readByte(address), 2, 16, QLatin1Char('0')));
            ui->tableWidget->item(i, 1)->setText(QString("%1").arg(Sim::readByte(address)));
        }
    }

    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
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

    if (contents.contains(rx) && dataOk && addrConvOk) {
        Sim::writeByte(address, data);
        qDebug() << "Sim::Mem[" << address << "]: " << Sim::readByte(address);
        ui->tableWidget->item(row, 0)->setText(QString("0x") + QString("%1").arg(data, 2, 16).toUpper().trimmed());
        ui->tableWidget->item(row, 1)->setText(QString("%1").arg(data, 10).trimmed());
    }
    else if (addrConvOk && !dataOk) {
        qDebug() << "Conversion from text to int failed. data = " << item->text();
        data = Sim::readByte(address);
        ui->tableWidget->item(row, 0)->setText(QString("0x") + QString("%1").arg(data, 2, 16).toUpper().trimmed());
        ui->tableWidget->item(row, 1)->setText(QString("%1").arg(data, 10).trimmed());
    }
    else if (addrConvOk) { // we have problems, the labels are incorrectly formatted
        populateMemoryItems();
    }

    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));
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

void MainMemory::resizeEvent(QResizeEvent *e)
{

    int newRowCount = ui->tableWidget->height()/ui->tableWidget->rowHeight(0) + 1;
    // +2 to make it look like we're actually scrolling and not shuffling items
    int oldRowCount = ui->tableWidget->rowCount();
    if (newRowCount != oldRowCount) {
        qDebug() << "oldRowCount: " << oldRowCount << ", newRowCount: " << newRowCount;
    }
    if (newRowCount > oldRowCount) {
        ui->tableWidget->setRowCount(newRowCount);

        bool addrConvOk;
        int address;

        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            rows << QString("0x%1").arg(i, 4, 16, QLatin1Char('0'));
        }
        ui->tableWidget->setVerticalHeaderLabels(rows);

        disconnect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(cellDataChanged(QTableWidgetItem*)));

        for (int row = oldRowCount; row < newRowCount; row++) {
            address = ui->tableWidget->verticalHeaderItem(row)->text().toInt(&addrConvOk, 16);
            if (addrConvOk) {
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString("0x") + QString("%1").arg(Sim::readByte(address), 2, 16).toUpper().trimmed()));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString("%1").arg(Sim::readByte(address)).trimmed()));
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
            delete ui->tableWidget->item(i, 1);
            rows.removeLast();
        }
        refreshMemory();
    }
}

