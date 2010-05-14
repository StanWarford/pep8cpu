#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "pephighlighter.h"

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

    QString getExampleText();

    void copy();
    // Post: the text edit that has focus has the copy() operation performed

    bool hasFocus();
    // Returns if the webview or the textedit has focus

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpDialog *ui;

    void selectItem(QString string);

    PepHighlighter *leftHighlighter;

    enum Row {
        eCPU = 0,
        eMICROCODE = 1,
        eEXAMPLES = 2,
        eEXCERCISES = 3,

        eFIG1205 = 0,
        eFIG1205B = 1,
        eFIG1208 = 2,
        eFIG1209 = 3,
        eFIG1210  = 4,
        eFIG1212  = 5,

        eEX1207A = 0,
        eEX1207B = 1,
        eEX1207C = 2,
        eEX1207D = 3,
        eEX1207E = 4,
        eEX1207F = 5,
        eEX1207G = 6,
        eEX1207H = 7,
        eEX1207I = 8,
        eEX1207J = 9,
        eEX1207K = 10,
        eEX1207L = 11,
        eEX1207M = 12,
        eEX1207N = 13,
        eEX1207O = 14,
        eEX1207P = 15,
        eEX1207Q = 16,
        eEX1207R = 17,
        eEX1207S = 18,
        eEX1207T = 19,
        eEX1207U = 20,
        eEX1207V = 21,
        eEX1207W = 22,
        eEX1207X = 23,
    };

private slots:
    void onCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*);

signals:
    void clicked();

};

#endif // HELPDIALOG_H
