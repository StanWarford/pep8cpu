#ifndef REGLINEEDIT_H
#define REGLINEEDIT_H

#include <QLineEdit>

class RegLineEdit : public QLineEdit
{
Q_OBJECT
public:
    explicit RegLineEdit(QWidget *parent = 0, int maxInputLength = 4);

private:
    void keyPressEvent(QKeyEvent *e);
    int maxLen;

signals:

public slots:

};

#endif // REGLINEEDIT_H
