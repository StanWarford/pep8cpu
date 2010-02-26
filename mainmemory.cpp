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

    int newRowCount = ui->tableWidget->height()/ui->tableWidget->rowHeight(0);
    // +2 to make it look like we're actually scrolling and not shuffling items
    int oldRowCount = ui->tableWidget->rowCount();
    if (newRowCount > oldRowCount) {
        qDebug() << "Resize Event: " << newRowCount - oldRowCount << " new rows";
        // Need new items
        for (int i = oldRowCount + 1; i <= newRowCount; i++) {
            QTableWidgetItem *newHexItem = new QTableWidgetItem("0x0");
            newHexItem->setText("0x00");
            ui->tableWidget->setItem(i, 0, newHexItem);
            QTableWidgetItem *newDecItem = new QTableWidgetItem("00");
            ui->tableWidget->setItem(i, 1, newDecItem);
        }
        ui->tableWidget->setRowCount(newRowCount);
        populateMemoryItems();
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
    QStringList list;

    qDebug() << "scroll value: " << ui->verticalScrollBar->value();
    int scrollBarValue = ui->verticalScrollBar->value();
    for (int i = scrollBarValue; i < scrollBarValue + ui->tableWidget->rowCount(); i++) {
        list.append(QString("0x%1").arg(i, 4, 16, QLatin1Char('0')));
    }
    ui->tableWidget->setVerticalHeaderLabels(list);

    refreshMemory();
}

void MainMemory::refreshMemory()
{
    qDebug() << "rowCount: " << ui->tableWidget->rowCount();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->item(i, 0)) {
            ui->tableWidget->item(i, 0)->setText(QString("0x0"));
            ui->tableWidget->item(i, 1)->setText(QString("0"));
        }
        else {
//            qDebug() << "Line " << i << " has no items";
        }
    }
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
    bool ok;
    int address = ui->tableWidget->verticalHeaderItem(row)->text().toInt(&ok, 16);
    int data = item->text().toInt(&ok, item->column() == 0 ? 16 : 10);

    if (ok) {
        Sim::writeByte(address, item->text().toInt());
        qDebug() << "Sim::Mem[" << address << "]: " << Sim::readByte(address);
        ui->tableWidget->item(row, 1)->setText(QString("%1").arg(data, 10).trimmed());
        ui->tableWidget->item(row, 0)->setText(QString("0x") + QString("%1").arg(data, 2, 16).trimmed());
    }
    else {
        qDebug() << "Conversion from text to int failed.";
        if (item->column() == 0) {
            data = ui->tableWidget->item(row, 1)->text().toInt(&ok, 10);
            ui->tableWidget->item(row, 0)->setText(QString("0x") + QString("%1").arg(data, 2, 16).trimmed());
        }
        else if (item->column() == 1) {

        }
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

    int newRowCount = ui->tableWidget->height()/ui->tableWidget->rowHeight(0) + 2;
    // +2 to make it look like we're actually scrolling and not shuffling items
    int oldRowCount = ui->tableWidget->rowCount();
    if (newRowCount > oldRowCount) {
        qDebug() << "Resize Event: " << newRowCount - oldRowCount << " new rows";
        // Need new items
        for (int i = oldRowCount + 1; i <= newRowCount; i++) {
            QTableWidgetItem *newHexItem = new QTableWidgetItem("0x0");
            newHexItem->setText("0x00");
            ui->tableWidget->setItem(i, 0, newHexItem);
            QTableWidgetItem *newDecItem = new QTableWidgetItem("00");
            ui->tableWidget->setItem(i, 1, newDecItem);
        }
        ui->tableWidget->setRowCount(newRowCount);
        populateMemoryItems();
    }
    else if (oldRowCount > newRowCount) {
        qDebug() << "Resize Event: " << oldRowCount - newRowCount << " deleted rows";
        // We have excess items and should delete them
        for (int i = oldRowCount; i > newRowCount; i--) {
            delete ui->tableWidget->item(i, 0);
            delete ui->tableWidget->item(i, 1);
        }
        ui->tableWidget->setRowCount(newRowCount);
        populateMemoryItems();
    }
}

