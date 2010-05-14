#include "helpdialog.h"
#include "ui_helpdialog.h"

#include "pep.h"
#include <QClipboard>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    connect(ui->helpTreeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this,
            SLOT(onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
    // Forward the helpCopyToSourceButton_clicked() signal from this to the main window
    connect(ui->helpCopyToMicrocodeButton, SIGNAL(clicked()), this, SIGNAL(clicked()));

    ui->helpSplitter->widget(1)->hide();
    ui->helpTreeWidget->expandAll();

    leftHighlighter = new PepHighlighter(ui->helpTextEdit->document());

    ui->helpTreeWidget->setFont(QFont(Pep::labelFont, Pep::labelFontSize));
    ui->helpTextEdit->setFont(QFont(Pep::codeFont, Pep::codeFontSize));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

QString HelpDialog::getExampleText()
{
    return ui->helpTextEdit->toPlainText();
}

void HelpDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void HelpDialog::selectItem(QString string) {
    QTreeWidgetItemIterator it(ui->helpTreeWidget);
    while (*it) {
        if ((*it)->text(0) == string) {
            (*it)->setSelected(true);
            ui->helpTreeWidget->setCurrentItem((*it));
        } else {
            (*it)->setSelected(false);
        }
        ++it;
    }
}

void HelpDialog::onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*) {
    // Is this a subcategory?
    bool isHelpSubCat = ui->helpTreeWidget->currentIndex().parent().isValid();
    // Parent row (if it has a parent, -1 else)
    int parentRow = ui->helpTreeWidget->currentIndex().parent().row();
    // Row (if it has a parent, this is the child row)
    int row = ui->helpTreeWidget->currentIndex().row();

//    qDebug() << "Selected: " << ui->helpTreeWidget->currentIndex();

    if (!isHelpSubCat && row == eCPU) {
        ui->helpSplitter->widget(1)->hide();
        ui->helpTopWebView->show();
        ui->helpTopWebView->load(QUrl("qrc:/help/cpu.html"));
    }
    else if (!isHelpSubCat && row == eMICROCODE) {  // Writing Trap Handlers
        ui->helpSplitter->widget(1)->hide();
        ui->helpTopWebView->show();
        ui->helpTopWebView->load(QUrl("qrc:/help/microcode.html"));
    }
    else if ((!isHelpSubCat && row == eEXAMPLES) || parentRow == eEXAMPLES) {
        if (!isHelpSubCat) {
            ui->helpSplitter->widget(1)->hide();
            ui->helpTopWebView->show();
            ui->helpTopWebView->load(QUrl("qrc:/help/examples.html"));
        }
        else {
            ui->helpSplitter->widget(0)->hide();
            ui->helpSplitter->widget(1)->show();
            if (row == eFIG1205) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.5</b> The control signals to fetch the instruction specifier and increment PC by 1.");
            }
            else if (row == eFIG1205B) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.5b</b> Combining cycles 1 and 3 of Figure 12.5.");
            }
            else if (row == eFIG1208) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1208.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.8</b> The control signals to implement the store byte instruction with direct addressing.");
            }
            else if (row == eFIG1209) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1209.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.9</b> The control signals to implement the add instruction with immediate addressing.");
            }
            else if (row == eFIG1210) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1210.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.10</b> The control signals to implement the load instruction with indirect addressing.");
            }
            else if (row == eFIG1212) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1212.pepcpu"));
                ui->helpFigureLabel->setText("<b>Figure 12.12</b> The control signals to implement the unary ASRA instruction.");
            }
        }
    }
    else if ((!isHelpSubCat && row == eEXCERCISES) || parentRow == eEXCERCISES) {
        if (!isHelpSubCat) {
            ui->helpSplitter->widget(1)->hide();
            ui->helpTopWebView->show();
            ui->helpTopWebView->load(QUrl("qrc:/help/excercises.html"));
        }
        else {
            ui->helpSplitter->widget(0)->hide();
            ui->helpSplitter->widget(1)->show();
            if (row == eEX1207A) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/exer1207a.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (a)</b> Specification for <code>STBYTEA there,n</code>.");
            }
            else if (row == eEX1207B) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1207b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (b)</b> Specification for <code>STBYTEA there,s</code>.");
            }
            else if (row == eEX1207C) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1207c.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (c)</b> Specification for <code>STBYTEA there,sf</code>.");
            }
            else if (row == eEX1207D) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1207d.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (d)</b> Specification for <code>STBYTEA there,x</code>.");
            }
            else if (row == eEX1207E) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1207e.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (e)</b> Specification for <code>STBYTEA there,sx</code>.");
            }
            else if (row == eEX1207F) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (f)</b> Specification for <code>STBYTEA there,sxf</code>.");
            }
            else if (row == eEX1207G) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (g)</b> Specification for <code>BR there</code>.");
            }
            else if (row == eEX1207H) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (h)</b> Specification for <code>CALL there</code>.");
            }
            else if (row == eEX1207I) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (i)</b> Specification for <code>NOTA</code>.");
            }
            else if (row == eEX1207J) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (j)</b> Specification for <code>NEGA</code>.");
            }
            else if (row == eEX1207K) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (k)</b> Specification for <code>ROLA</code>.");
            }
            else if (row == eEX1207L) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (l)</b> Specification for <code>RORA</code>.");
            }
            else if (row == eEX1207M) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (m)</b> Specification for <code>RET4</code>.");
            }
            else if (row == eEX1207N) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (n)</b> Specification for <code>ADDSP this,i</code>.");
            }
            else if (row == eEX1207O) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (o)</b> Specification for <code>SUBSP this,i</code>.");
            }
            else if (row == eEX1207P) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (p)</b> Specification for <code>SUBA this,i</code>.");
            }
            else if (row == eEX1207Q) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (q)</b> Specification for <code>ANDA this,i</code>.");
            }
            else if (row == eEX1207R) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (r)</b> Specification for <code>ORA this,i</code>.");
            }
            else if (row == eEX1207S) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (s)</b> Specification for <code>CPA this,i</code>.");
            }
            else if (row == eEX1207T) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (t)</b> Specification for <code>LDBYTEA this,i</code>.");
            }
            else if (row == eEX1207U) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (u)</b> Specification for <code>LDBYTEA this,d</code>.");
            }
            else if (row == eEX1207V) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (v)</b> Specification for <code>MOVSPA</code>.");
            }
            else if (row == eEX1207W) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (w)</b> Specification for <code>MOVFLGA</code>.");
            }
            else if (row == eEX1207X) {
                ui->helpTextEdit->setText(Pep::resToString(":/help/figures/fig1205b.pepcpu"));
                ui->helpFigureLabel->setText("<b>Exercise 12.7 (x)</b> Specification for <code>RETTR</code>.");
            }
        }
    }
}

void HelpDialog::copy()
{
    if (ui->helpTextEdit->hasFocus()) {
        ui->helpTextEdit->copy();
    } else if (ui->helpTopWebView->hasFocus()) {
        QApplication::clipboard()->setText(ui->helpTopWebView->selectedText());
    }
}

bool HelpDialog::hasFocus()
{
    return ui->helpTextEdit->hasFocus() || ui->helpTopWebView->hasFocus();
}

