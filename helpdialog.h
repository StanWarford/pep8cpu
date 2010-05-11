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

        eFIG1205 = 0,
        eFIG1205B = 1,
        eFIG1208 = 2,
        eFIG1209 = 3,
        eFIG1210  = 4,
        eFIG1212  = 5,
    };

private slots:
    void onCurrentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*);

signals:
    void clicked();

};

#endif // HELPDIALOG_H
