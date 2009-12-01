#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "byteconverterdec.h"
#include "byteconverterhex.h"
#include "byteconverterbin.h"
#include "byteconverterchar.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    // Byte converter
    ByteConverterDec *byteConverterDec;
    ByteConverterHex *byteConverterHex;
    ByteConverterBin *byteConverterBin;
    ByteConverterChar *byteConverterChar;

private slots:

    // Byte converter
    void slotByteConverterDecEdited(const QString &);
    void slotByteConverterHexEdited(const QString &);
    void slotByteConverterBinEdited(const QString &);
    void slotByteConverterCharEdited(const QString &);

};

#endif // MAINWINDOW_H
