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
}

void HelpDialog::copy()
{
    if (ui->helpTextEdit->hasFocus()) {
        ui->helpTextEdit->copy();
    } else if (ui->helpTopWebView->hasFocus()) {
        QApplication::clipboard()->setText(ui->helpTopWebView->selectedText());
    }
}
