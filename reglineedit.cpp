#include "reglineedit.h"

#include <QKeyEvent>
#include <QString>

RegLineEdit::RegLineEdit(QWidget *parent, int maxInputLength) :
    QLineEdit(parent)
{
    maxLen = maxInputLength;
}

void RegLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (!text().contains(QString("0x[0-9a-fA-F]{0,%1}").arg(maxLen))) {
        setText("0x");
    }

    if (e->text().contains("[0-9a-fA-F]")) {
        setText(text() + e->text());
    }
    else {
        e->ignore();
    }
}
