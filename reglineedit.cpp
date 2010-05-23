#include "reglineedit.h"

#include <QKeyEvent>
#include <QString>

RegLineEdit::RegLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void RegLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->text().contains("[0-9a-fA-F]")) {

    }
}
