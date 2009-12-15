#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
    class HelpDialog;
}

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::HelpDialog *ui;

    void selectItem(QString string);

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
